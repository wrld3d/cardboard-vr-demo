//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once
#include "Types.h"
#include "VRRenderCamera.h"
#include "VectorMathDecl.h"
#include "Space.h"
#include "IInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "VRCameraPositionSpline.h"
#include "CameraState.h"
#include "IVRHeadTracker.h"

namespace Eegeo
{
    namespace VR
    {
       
        namespace MoveDirection
        {
            enum Values
            {
                Forward,
                Backwards,
                Left,
                Right,
                Up,
                Down
            };
        }
        
        
        
        class VRCameraController : public VRCamera::VRRenderCamera
        {
            
        public:
            VRCameraController(float screenWidth,
                               float screenHeight,
                               float eyeDistance,
                               Examples::IVRHeadTracker& headTracker,
                               const std::string& welcomeNoteUK,
                               const std::string& welcomeNoteSF,
                               const std::string& welcomeNoteNY,
                               const std::string& welcomeNoteUKSpline,
                               const std::string& welcomeNoteSFSpline,
                               const std::string& welcomeNoteNYSpline)
            : VRCamera::VRRenderCamera(screenWidth, screenHeight, eyeDistance)
            , m_moving(false)
            , m_moveDirection(0.f, 0.f, 0.f)
            , m_falling(false)
            , m_time(0.0f)
            , m_stopTime(10.0f)
            , m_stopTimeElapsed(0.0f)
            , m_splineEndPauseTime(10.0f)
            , m_splineEndPauseTimeElapsed(0.0f)
            , m_pHeadTracker(headTracker)
            , m_isPlaying(true)
            , m_vrCameraPositionSpline(welcomeNoteUK, welcomeNoteSF, welcomeNoteNY, welcomeNoteUKSpline, welcomeNoteSFSpline, welcomeNoteNYSpline)
            {
            }

            const bool IsMoving() const { return m_moving; }
            const bool IsFalling() const { return m_falling; }
            const bool IsFollowingSpline() const { return m_vrCameraPositionSpline.IsPlaying(); }
            
            VRCameraPositionSpline& GetVRCameraPositionSpline() { return m_vrCameraPositionSpline; }
                        
            virtual void Update(float dt);
            
            void MoveStart(MoveDirection::Values direction);
            void MoveEnd();
            
            void StartFall();
            void StopFall();
            
            void RotateHorizontal(float angle);
            
            void SetShiftDown(bool down) { m_shiftDown = down; }
            
            void PlaySpline(int splineID);

            void PlayNextSpline();

            void RegisterSplineFinishedCallback(Helpers::ICallback0 &callback);
            void UnregisterSplineFinishedCallback(Helpers::ICallback0 &callback);
            
        private:
            bool CanAcceptUserInput() const;
            
            float MovementAltitudeMutlipler() const;
            
            void Move(float dt);
            void Fall(float dt);
            
            Examples::IVRHeadTracker& m_pHeadTracker;
            bool m_moving;
            v3 m_moveDirection;
            
            float m_currentFallSpeed;
            bool m_falling;
            
            float m_time;
            float m_stopTime;
            float m_stopTimeElapsed;
            float m_splineEndPauseTime;
            float m_splineEndPauseTimeElapsed;
            
            VRCameraPositionSpline m_vrCameraPositionSpline;

            Helpers::CallbackCollection0 m_splineEndedCallbacks;
            bool m_isPlaying;
            bool m_shiftDown;
        };
    }
}
