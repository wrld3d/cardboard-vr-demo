// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "JumpPointConfigData.h"

namespace Examples
{
    namespace ApplicationConfig
    {

        JumpPointConfigData::JumpPointConfigData(int jumpPointID, Eegeo::Space::LatLongAltitude lla, int iconID, double size)
        : m_jumpPointID(jumpPointID)
        , m_jumpPointLocation(lla)
        , m_iconID(iconID)
        , m_size(size)
        {
        }

        int JumpPointConfigData::GetID() const
        {
            return m_jumpPointID;
        }

        const Eegeo::Space::LatLongAltitude& JumpPointConfigData::GetJumpPointLocation() const
        {
            return m_jumpPointLocation;
        }

        int JumpPointConfigData::GetIconID() const
        {
            return m_iconID;
        }

        double JumpPointConfigData::GetSize() const
        {
            return m_size;
        }

        void JumpPointConfigData::SetChildJumpPoints(const TJumpPointVector& childJumpPoints)
        {
            m_childJumpPoints = childJumpPoints;
        }

        const TJumpPointVector& JumpPointConfigData::GetChildJumpPoints() const
        {
            return m_childJumpPoints;
        }
    }
}
