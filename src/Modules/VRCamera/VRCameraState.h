// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace Eegeo
{
    namespace VRCamera
    {
        class VRCameraState
        {
            dv3 m_locationEcef;
            Camera::CameraState m_leftCameraState;
            Camera::CameraState m_rightCameraState;
            Eegeo::m33 m_currentCameraOrientation;
            Eegeo::m33 m_baseOrientation;
            Eegeo::m33 m_headTrackerOrientation;
            
        public:
            VRCameraState(const dv3& locationEcef,
                          const Camera::CameraState& leftCameraState,
                          const Camera::CameraState& rightCameraState,
                          const Eegeo::m33& currentCameraOrientation,
                          const Eegeo::m33& baseOrientation,
                          const Eegeo::m33& headTrackerOrientation)
            : m_locationEcef(locationEcef)
            , m_leftCameraState(leftCameraState)
            , m_rightCameraState(rightCameraState)
            , m_currentCameraOrientation(currentCameraOrientation)
            , m_baseOrientation(baseOrientation)
            , m_headTrackerOrientation(headTrackerOrientation)
            {
                
            }
            
            const dv3& LocationEcef() const { return m_locationEcef; }

            const Camera::CameraState& LeftCameraState() const { return m_leftCameraState; }

            const Camera::CameraState& RightCameraState() const { return m_rightCameraState; }

            const Eegeo::m33& CurrentCameraOrientation() const { return m_currentCameraOrientation; }

            const Eegeo::m33& BaseOrientation() const { return m_baseOrientation; }

            const Eegeo::m33& HeadTrackerOrientation() const { return m_headTrackerOrientation; }

        };
    }
}
