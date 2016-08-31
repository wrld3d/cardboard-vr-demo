// Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once

#include "Types.h"
#include "CatmullRomSpline.h"
#include "VectorMathDecl.h"
#include "ICallback.h"
#include "CallbackCollection.h"

namespace Eegeo
{
    namespace VR
    {
        class VRCameraPositionSpline : protected Eegeo::NonCopyable
        {
        public:
            VRCameraPositionSpline()
            : m_playbackSpeed(0.03)
            , m_playing(false)
            , m_time(0.0)
            , m_slowDownFactor(0.0f)
            , m_currentSpline(0)
            , m_currentSplineHasWelcomeNote(false)
            {
                SetSpline(m_currentSpline);
            }
            
            void setSlowDownFactor(float slowDownFactor);
            
            void AddPoint(const dv3& ecefEyePosition, const m33& orientation);
            void Update(float dt);
            
            void Start();
            void Stop();
            
            double GetPlaybackSpeed() const { return m_playbackSpeed; }
            void SetPlaybackSpeed(double speed) { m_playbackSpeed = speed; }
            
            double GetCurrentSplineTime() const { return m_time; }
            int GetCurrentSplineID() const { return m_currentSpline; }
            
            const bool IsPlaying() const { return m_playing; }
            const bool IsStopPoint() const { return m_positionSpline.GetPoints().size()<=2; }
            const bool IsInteriorSpline() const {
                return (GetCurrentSplineTime()>0.3f && m_currentSpline==4) || m_currentSpline==5 || m_currentSpline==6;
            }
            
            void Spew();
            void Clear();
            
            void NextSpline();
            void SetSpline(int splineId);
            void GetCurrentCameraPosition(dv3& interpolatedPositionEcef, m33& interpolatedOrientation) const;

            bool GetCurrentSplineHasWelcomeNote() const;
            const std::string& GetCurrentSplineWelcomeNote() const;

        private:
            Geometry::CatmullRomSpline m_positionSpline;
            Geometry::CatmullRomSpline m_forwardSpline;
            Geometry::CatmullRomSpline m_upSpline;
            Geometry::CatmullRomSpline m_rightSpline;
            double m_playbackSpeed;
            double m_time;
            bool m_playing;
            int m_currentSpline;
            
            float m_slowDownFactor;
            float m_currentPlaybackSpeed;

            bool m_currentSplineHasWelcomeNote;
            std::string m_welcomeNote;
        };
    }
}
