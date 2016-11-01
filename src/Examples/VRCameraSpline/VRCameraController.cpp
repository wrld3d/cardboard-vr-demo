//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCameraController.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "SpaceHelpers.h"
#include "EcefTangentBasis.h"
#include "Quaternion.h"
#include "EarthConstants.h"
#include "MathFunc.h"
#include "IVRHeadTracker.h"
#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        const float GravityAcceleration = 15.0f;
        const float TerminalVelocity = 500.f;
        
        void VRCameraController::Update(float dt)
        {
            m_time += dt;
            
            if(m_vrCameraPositionSpline.IsStopPoint())
            {
                m_stopTimeElapsed += dt;
                if(m_stopTimeElapsed>=m_stopTime && m_isPlaying)
                {
                    m_isPlaying = false;
                    m_splineEndedCallbacks.ExecuteCallbacks();

                }
            }
            else if (!IsFollowingSpline())
            {
                m_splineEndPauseTimeElapsed += dt;
                if(m_splineEndPauseTimeElapsed > m_splineEndPauseTime || m_vrCameraPositionSpline.GetCurrentSplineID()!=2)
                {
                    if (m_isPlaying)
                    {
                        m_isPlaying = false;
                        m_splineEndedCallbacks.ExecuteCallbacks();
                    }
                }
            }

            m_vrCameraPositionSpline.Update(dt);

            dv3 splinePosition;
            m33 orientationMatrix;
            m_vrCameraPositionSpline.GetCurrentCameraPosition(splinePosition, orientationMatrix);
            SetEcefPosition(splinePosition);
            m_orientation = orientationMatrix;
        }
        
        void VRCameraController::PlaySpline(int splineID)
        {
            m_pHeadTracker.ResetTracker();
            m_vrCameraPositionSpline.SetSpline(splineID);
            m_vrCameraPositionSpline.Start();
            m_splineEndPauseTimeElapsed = 0.0f;
        }

        void VRCameraController::PlayNextSpline()
        {
            m_pHeadTracker.ResetTracker();
            m_stopTimeElapsed = 0.0f;
            m_splineEndPauseTimeElapsed = 0.0f;
            m_vrCameraPositionSpline.NextSpline();
            m_vrCameraPositionSpline.Start();
            m_isPlaying = true;
        }

        void VRCameraController::RegisterSplineFinishedCallback(Helpers::ICallback0 &callback)
        {
            m_splineEndedCallbacks.AddCallback(callback);
        }

        void VRCameraController::UnregisterSplineFinishedCallback(Helpers::ICallback0 &callback)
        {
            m_splineEndedCallbacks.RemoveCallback(callback);
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
                SetEcefPosition(m_ecefPosition);
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
