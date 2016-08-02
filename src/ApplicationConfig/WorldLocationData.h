// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"
#include "Types.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        class WorldLocationData
        {
        private:
            std::string m_location;
            int m_locID;
            int m_iconID;
            Eegeo::Space::LatLongAltitude m_lla;
            float m_orientation;

        public:
            WorldLocationData();
            WorldLocationData(const std::string& location, int locID, int iconID, const Eegeo::Space::LatLongAltitude& lla, float orientation);

            const std::string& GetLocation() const;

            int GetLocationID() const;

            int GetIconID() const;

            const Eegeo::Space::LatLongAltitude& GetLocationCameraPosition() const;

            float GetOrientation() const;
        };
    }
}
