// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        class JumpPointConfigData
        {
        private:
            int m_jumpPointID;
            Eegeo::Space::LatLongAltitude m_jumpPointLocation;
            int m_iconID;
            double m_size;
            TJumpPointVector m_childJumpPoints;
            
        public:
            JumpPointConfigData(int jumpPointID, Eegeo::Space::LatLongAltitude lla, int iconID, double size);

            int GetID() const;

            const Eegeo::Space::LatLongAltitude& GetJumpPointLocation() const;

            int GetIconID() const;

            double GetSize() const;

            void SetChildJumpPoints(const TJumpPointVector& childJumpPoints);
            
            const TJumpPointVector& GetChildJumpPoints() const;
        };
    }
}
