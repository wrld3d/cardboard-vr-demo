//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "OVREegeoCameraController.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "SpaceHelpers.h"
#include "EcefTangentBasis.h"
#include "Quaternion.h"
#include "EarthConstants.h"
#include "MathFunc.h"
#include "Logger.h"

namespace Eegeo
{
    namespace OVR
    {
        const float GravityAcceleration = 15.0f;
        const float TerminalVelocity = 500.f;
        
        Eegeo::dv3 OVREegeoCameraController::GetEcefInterestPoint() const
        {
            
            dv3 ecefPosition = m_ecefPosition;
            return ecefPosition.Normalise() * Eegeo::Space::EarthConstants::Radius;
        }
        
        double OVREegeoCameraController::GetAltitudeAboveSeaLevel() const
        {
            return Space::SpaceHelpers::GetAltitude(m_renderCamera.GetEcefLocation());
        }
        
        void OVREegeoCameraController::SetProjectionMatrix(Eegeo::m44& projection)
        {
            m_renderCamera.SetProjectionMatrix(projection);
        }
        
        Camera::CameraState OVREegeoCameraController::GetCameraState() const
        {
            return Camera::CameraState(m_renderCamera.GetEcefLocation(),
                                       GetEcefInterestPoint(),
                                       m_renderCamera.GetViewMatrix(),
                                       m_renderCamera.GetProjectionMatrix());
        }
        
        void OVREegeoCameraController::UpdateFromPose(const Eegeo::m33& orientation, const Eegeo::v3& eyeOffset)
        {
            m33 orientationMatrix;
            m33::Mul(orientationMatrix, m_orientation, orientation);
            
            v3 eyeOffsetModified = eyeOffset;
            v3 rotatedEyeOffset = v3::Mul(eyeOffsetModified, orientationMatrix);
            
            float near, far;
            GetNearFarPlaneDistances(near,far);
            m_renderCamera.SetProjection(0.75f, near, far);
            
            m_renderCamera.SetOrientationMatrix(orientationMatrix);
            m_renderCamera.SetEcefLocation(dv3(m_ecefPosition.x + rotatedEyeOffset.x, m_ecefPosition.y + rotatedEyeOffset.y, m_ecefPosition.z + rotatedEyeOffset.z));

        }
        
        void OVREegeoCameraController::SetEcefPosition(const Eegeo::dv3& ecef)
        {
            m_ecefPosition = ecef;
            m_renderCamera.SetEcefLocation(m_ecefPosition);
        }
        
        void OVREegeoCameraController::SetStartLatLongAltitude(const Eegeo::Space::LatLongAltitude& eyePos)
        {
            m_ecefPosition = eyePos.ToECEF();
            
            Space::EcefTangentBasis tangentBasis;
            Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_ecefPosition, 0.f, tangentBasis);
            
            m_orientation.SetRow(0, tangentBasis.GetRight());
            m_orientation.SetRow(1, tangentBasis.GetUp());
            m_orientation.SetRow(2, -tangentBasis.GetForward());
            
            m_renderCamera.SetOrientationMatrix(m_orientation);
            m_renderCamera.SetEcefLocation(m_ecefPosition);
        }
        
        void OVREegeoCameraController::Update(float dt)
        {
            
            float near = 0.1f;
            float far = 4000.0f;
            GetNearFarPlaneDistances(near, far);
            m_renderCamera.SetProjection(m_renderCamera.GetFOV(), near, far);
            
            if(IsFalling())
            {
                Eegeo_TTY("Update Fall : %.2f",dt);
                Fall(dt);
            }
            else if (IsFollowingSpline())
            {
                m_OVRCameraPositionSpline.Update(dt);
                m_OVRCameraPositionSpline.GetCurrentCameraPosition(m_ecefPosition, m_orientation);
                
//                m_orientation.Identity();
                
                if (!IsFollowingSpline())
                {
                    m_OVRCameraPositionSpline.NextSpline();
                    m_OVRCameraPositionSpline.Start();
                }
            }
            else
            {
                Move(dt);
            }
        }
        
        m44 OVREegeoCameraController::CreateProjection( bool rightHanded, float tanHalfFov,
                                  float zNear /*= 0.01f*/, float zFar /*= 10000.0f*/ )
        {
            // A projection matrix is very like a scaling from NDC, so we can start with that.
            ScaleAndOffset2D scaleAndOffset = CreateNDCScaleAndOffsetFromFov ( tanHalfFov );
            
            float handednessScale = 1.0f;
            if ( rightHanded )
            {
                handednessScale = -1.0f;
            }
            
            float M[4][4];
            m44 projection;
            // Produces X result, mapping clip edges to [-w,+w]
            M[0][0] = scaleAndOffset.Scale.x;
            M[0][1] = 0.0f;
            M[0][2] = handednessScale * scaleAndOffset.Offset.x;
            M[0][3] = 0.0f;
            
            // Produces Y result, mapping clip edges to [-w,+w]
            // Hey - why is that YOffset negated?
            // It's because a projection matrix transforms from world coords with Y=up,
            // whereas this is derived from an NDC scaling, which is Y=down.
            M[1][0] = 0.0f;
            M[1][1] = scaleAndOffset.Scale.y;
            M[1][2] = handednessScale * -scaleAndOffset.Offset.y;
            M[1][3] = 0.0f;
            
            // Produces Z-buffer result - app needs to fill this in with whatever Z range it wants.
            // We'll just use some defaults for now.
            M[2][0] = 0.0f;
            M[2][1] = 0.0f;
            M[2][2] = -handednessScale * zFar / (zNear - zFar);
            M[2][3] = (zFar * zNear) / (zNear - zFar);
            
            // Produces W result (= Z in)
            M[3][0] = 0.0f;
            M[3][1] = 0.0f;
            M[3][2] = handednessScale;
            M[3][3] = 0.0f;
            
            for(int lop=0; lop<4; lop++)
                projection.SetRow(lop, Eegeo::v4(M[0][lop],M[1][lop],M[2][lop],M[3][lop]));
            
            return projection;
        }
        
        
        ScaleAndOffset2D OVREegeoCameraController::CreateNDCScaleAndOffsetFromFov ( FovPort tanHalfFov )
        {
            float projXScale = 2.0f / ( tanHalfFov.LeftTan + tanHalfFov.RightTan );
            float projXOffset = ( tanHalfFov.LeftTan - tanHalfFov.RightTan ) * projXScale * 0.5f;
            float projYScale = 2.0f / ( tanHalfFov.UpTan + tanHalfFov.DownTan );
            float projYOffset = ( tanHalfFov.UpTan - tanHalfFov.DownTan ) * projYScale * 0.5f;
            
            ScaleAndOffset2D result;
            result.Scale    = Eegeo::v2(projXScale, projYScale);
            result.Offset   = Eegeo::v2(projXOffset, projYOffset);
            // Hey - why is that Y.Offset negated?
            // It's because a projection matrix transforms from world coords with Y=up,
            // whereas this is from NDC which is Y=down.
            
            return result;
        }
        
        bool OVREegeoCameraController::CanAcceptUserInput() const
        {
            return (!(IsFalling() || IsFollowingSpline()));
        }
        
        void OVREegeoCameraController::MoveStart(MoveDirection::Values direction)
        {
            if(!CanAcceptUserInput())
            {
                return;
            }
            if (!m_moving)
            {
                switch (direction)
                {
                    case MoveDirection::Forward:
                    {
                        const v3 forwardDirection = -GetForward();
                        m_moveDirection = forwardDirection;
                        break;
                    }
                    case MoveDirection::Backwards:
                    {
                        const v3 backwardsDirection = GetForward();
                        m_moveDirection = backwardsDirection;
                        break;
                    }
                    case MoveDirection::Left:
                    {
                        const v3 leftDirection = -GetRight();
                        m_moveDirection = leftDirection;
                        break;
                    }
                    case MoveDirection::Right:
                    {
                        const v3 rightDirection = GetRight();
                        m_moveDirection = rightDirection;
                        break;
                    }
                    case MoveDirection::Up:
                    {
                        const v3 upDirection = GetUp();
                        m_moveDirection = upDirection;
                        break;
                    }
                    case MoveDirection::Down:
                    {
                        const v3 downDirection = -GetUp();
                        m_moveDirection = downDirection;
                        break;
                    }
                }
                m_moving = true;
            }
        }
        
        void OVREegeoCameraController::MoveEnd()
        {
            if(m_moving)
            {
                m_moving = false;
            }
        }
        
        void OVREegeoCameraController::Move(float dt)
        {
            if (m_moving)
            {
                const float mutliplier = MovementAltitudeMutlipler();
                const float& mutliplierRef = mutliplier;
                m_ecefPosition += m_moveDirection * mutliplierRef * dt;
                m_renderCamera.SetEcefLocation(m_ecefPosition);
            }
        }
        
        void OVREegeoCameraController::RotateHorizontal(float angle)
        {
            if(!CanAcceptUserInput())
            {
                return;
            }
            dv3 up = m_ecefPosition.Norm();
            
            m33 rotation;
            rotation.Rotate(up.ToSingle(),-angle);
            m33::Mul(m_orientation, rotation, m_orientation);
            if(m_moving)
            {
                m_moveDirection = v3::Mul(m_moveDirection, rotation);
            }
        }

        void OVREegeoCameraController::GetNearFarPlaneDistances(float& out_near, float& out_far)
        {
            double cameraAltitude = GetAltitudeAboveSeaLevel();
            double approxTerrainAltitude = 100;
            double approxTerrainAltitudeDelta = approxTerrainAltitude - 100;
            
            const double ClipPlaneThresholdAltitude = 15000.0;
            Camera::CameraHelpers::GetAltitudeInterpolatedNearFar(cameraAltitude, approxTerrainAltitude, approxTerrainAltitudeDelta, ClipPlaneThresholdAltitude, out_near, out_far);
        }
        
        float OVREegeoCameraController::MovementAltitudeMutlipler() const
        {
            const double minAltitude = 300.0;
            const double maxAltitude = 8000.0;
            
            const double minMultiplier = 60.f;
            const double maxMultiplier = 10000.f;
            
            double clampedAltitude = Math::Clamp(GetAltitudeAboveSeaLevel(), minAltitude, maxAltitude);
            double altitudeT = (clampedAltitude - minAltitude) / (maxAltitude - minAltitude);
            
            float multiplier = minMultiplier + ((maxMultiplier - minMultiplier) * altitudeT);
            return m_shiftDown ? multiplier * 0.2f : multiplier;
        }
        
        void OVREegeoCameraController::StartFall()
        {
            if(!m_falling)
            {
                m_falling = true;
                m_currentFallSpeed = 0.0f;
            }
        }
        
        void OVREegeoCameraController::StopFall()
        {
            if(m_falling)
            {
                m_falling = false;
            }
        }
        
        void OVREegeoCameraController::Fall(float dt)
        {
            m_currentFallSpeed = Eegeo::Min(TerminalVelocity, m_currentFallSpeed + GravityAcceleration * dt);
            
            dv3 downVector = -m_ecefPosition.Norm();
            
            dv3 newEcefPosition = m_ecefPosition + (m_currentFallSpeed * dt * downVector);
            float terrainHeight;
            if(m_pTerrainHeightProvider->TryGetHeight(m_ecefPosition, 11, terrainHeight))
            {
                if((terrainHeight + 5) > (newEcefPosition.Length() - Space::EarthConstants::Radius))
                {
                    StopFall();
                    return;
                }
            }
            m_ecefPosition = newEcefPosition;
        }
    }
}
