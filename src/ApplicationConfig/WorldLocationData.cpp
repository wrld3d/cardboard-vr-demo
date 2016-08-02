// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldLocationData.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        WorldLocationData::WorldLocationData()
        : m_location("")
        , m_locID(0)
        , m_iconID(0)
        , m_lla(Eegeo::Space::LatLongAltitude::FromDegrees(0, 0, 0))
        , m_orientation(0.f)
        {
        }

        WorldLocationData::WorldLocationData(const std::string& location, int locID, int iconID, const Eegeo::Space::LatLongAltitude& lla, float orientation)
        : m_location(location)
        , m_locID(locID)
        , m_iconID(iconID)
        , m_lla(lla)
        , m_orientation(orientation)
        {
        }

        const std::string& WorldLocationData::GetLocation() const
        {
            return m_location;
        }

        int WorldLocationData::GetLocationID() const
        {
            return m_locID;
        }

        int WorldLocationData::GetIconID() const
        {
            return m_iconID;
        }

        const Eegeo::Space::LatLongAltitude& WorldLocationData::GetLocationCameraPosition() const
        {
            return m_lla;
        }

        float WorldLocationData::GetOrientation() const
        {
            return m_orientation;
        }
    }
}
