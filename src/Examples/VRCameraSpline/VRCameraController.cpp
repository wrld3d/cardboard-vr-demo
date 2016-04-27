//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCameraController.h"
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
    namespace VR
    {
        const float GravityAcceleration = 15.0f;
        const float TerminalVelocity = 500.f;
        
        Eegeo::dv3 VRCameraController::GetEcefInterestPoint() const
        {
            
            dv3 ecefPosition = m_ecefPosition;
            return ecefPosition.Normalise() * Eegeo::Space::EarthConstants::Radius;
        }
        
        double VRCameraController::GetAltitudeAboveSeaLevel() const
        {
            return Space::SpaceHelpers::GetAltitude(m_renderCamera.GetEcefLocation());
        }
        
        void VRCameraController::SetProjectionMatrix(Eegeo::m44& projection)
        {
            m_renderCamera.SetProjectionMatrix(projection);
        }
        
        Camera::CameraState VRCameraController::GetCameraState() const
        {
            return Camera::CameraState(m_renderCamera.GetEcefLocation(),
                                       GetEcefInterestPoint(),
                                       m_renderCamera.GetViewMatrix(),
                                       m_renderCamera.GetProjectionMatrix());
        }
        
        void VRCameraController::UpdateFromPose(const Eegeo::m33& orientation, const Eegeo::v3& eyeOffset, float eyeDistance)
        {
            m33 orientationMatrix;
            m33::Mul(orientationMatrix, m_orientation, orientation);
            
            v3 eyeOffsetModified = dv3::ToSingle(m_ecefPosition.Norm()*eyeDistance);
            v3 rotatedEyeOffset = v3::Mul(eyeOffsetModified, orientationMatrix);
            
            v3 rA = m_orientation.GetRow(0);
            v3 rB = orientationMatrix.GetRow(0);
            
            v3 uA = m_orientation.GetRow(1);
            v3 uB = orientationMatrix.GetRow(1);
            
            v3 fA = m_orientation.GetRow(2) * -1;
            v3 fB = orientationMatrix.GetRow(2) * -1;
            
            float rAngle = Math::Rad2Deg(Math::ACos(v3::Dot(rA, rB) / (rA.Length() * rB.Length())));
            float uAngle = Math::Rad2Deg(Math::ACos(v3::Dot(uA, uB) / (uA.Length() * uB.Length())));
            float fAngle = Math::Rad2Deg(Math::ACos(v3::Dot(fA, fB) / (fA.Length() * fB.Length())));
            
            float lookDownFactor = 1.0f;
            
//            if(fAngle>85.f)
//                lookDownFactor = fAngle/175.f;
            
            float factor = 1.0f;
            if(uAngle<100.f && fAngle<100.f){
                factor = 1.f - (uAngle/90.f + fAngle/90.f)/2.f;
            }else{
                factor = rAngle / 90.f;
                if(factor > 0.9f)
                    factor = 0.9f;
            }
            
            float near, far;
            GetNearFarPlaneDistances(near,far);
            if(!std::isnan(factor)){
                m_VRCameraPositionSpline.setSlowDownFactor(1.f - factor);
                m_renderCamera.SetOrientationMatrix(orientationMatrix);
                m_renderCamera.SetEcefLocation(dv3(m_ecefPosition.x + rotatedEyeOffset.x, m_ecefPosition.y + rotatedEyeOffset.y, m_ecefPosition.z + rotatedEyeOffset.z));
                
                m_renderCamera.SetProjection(0.7f, near*0.1f, far);
            }
            
        }
        
        void VRCameraController::SetEcefPosition(const Eegeo::dv3& ecef)
        {
            m_ecefPosition = ecef;
            m_renderCamera.SetEcefLocation(m_ecefPosition);
        }
        
        void VRCameraController::SetStartLatLongAltitude(const Eegeo::Space::LatLongAltitude& eyePos)
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
        
        void VRCameraController::Update(float dt)
        {
            
            m_time += dt;
            
            if(IsFalling())
            {
                Fall(dt);
            }
            else if (IsFollowingSpline())
            {
                m_VRCameraPositionSpline.Update(dt);
                m_VRCameraPositionSpline.GetCurrentCameraPosition(m_ecefPosition, m_orientation);
                
                if (!IsFollowingSpline())
                {
                    m_VRCameraPositionSpline.NextSpline();
                    m_VRCameraPositionSpline.Start();
                }
            }
            else
            {
                Move(dt);
            }
        }
        
        bool VRCameraController::CanAcceptUserInput() const
        {
            return (!(IsFalling() || IsFollowingSpline()));
        }
        
        void VRCameraController::MoveStart(MoveDirection::Values direction)
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
        
        void VRCameraController::MoveEnd()
        {
            if(m_moving)
            {
                m_moving = false;
            }
        }
        
        void VRCameraController::Move(float dt)
        {
            if (m_moving)
            {
                const float mutliplier = MovementAltitudeMutlipler();
                const float& mutliplierRef = mutliplier;
                m_ecefPosition += m_moveDirection * mutliplierRef * dt;
                m_renderCamera.SetEcefLocation(m_ecefPosition);
            }
        }
        
        void VRCameraController::RotateHorizontal(float angle)
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

        void VRCameraController::GetNearFarPlaneDistances(float& out_near, float& out_far)
        {
            double cameraAltitude = GetAltitudeAboveSeaLevel();
            double approxTerrainAltitude = 100;
            double approxTerrainAltitudeDelta = approxTerrainAltitude -100;
            
            const double ClipPlaneThresholdAltitude = 15000.0;
            //             * \param The altitude in meters of the camera
            //             * \param The approximate altitude of the highest terrain in the scene
            //             * \param The difference between the highest and lowest terrain in the scene
            //             * \param Altitude at which the method for scaling the near/far bounds changes (Default 15000m)
            //             * \param out_nearDistance [out] resultant recommended Near value based on the provided altitudes
            //             * \param out_farDistance [out] resultant reecommended Far value based on the provided altitudes
            Camera::CameraHelpers::GetAltitudeInterpolatedNearFar(cameraAltitude, approxTerrainAltitude, approxTerrainAltitudeDelta, ClipPlaneThresholdAltitude, out_near, out_far);
  
            
        }
        
        float VRCameraController::MovementAltitudeMutlipler() const
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
        
        void VRCameraController::StartFall()
        {
            if(!m_falling)
            {
                m_falling = true;
                m_currentFallSpeed = 0.0f;
            }
        }
        
        void VRCameraController::StopFall()
        {
            if(m_falling)
            {
                m_falling = false;
            }
        }
        
        void VRCameraController::Fall(float dt)
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
