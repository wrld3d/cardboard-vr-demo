// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include <vector>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"
#include "JumpPointConfigData.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        class ApplicationConfiguration
        {
        private:
            std::string m_name;
            const std::string m_eegeoApiKey;
            Eegeo::Space::LatLongAltitude m_interestLocation;
            float m_orientationDegrees;

            const std::string m_productVersion;
            const std::string m_buildNumber;
            const std::string m_combinedVersionString;

            const std::vector<std::string> m_exteriorLocations;
            const TExteriorJumpPoints m_exteriorJumpPoints;
            const TInteriorJumpPoints m_interiorJumpPoints;
        public:

            ApplicationConfiguration(const std::string& name,
                                     const std::string& eegeoApiKey,
                                     const Eegeo::Space::LatLongAltitude& interestLocation,
                                     float orientationDegrees,
                                     const std::string& productVersion,
                                     const std::string& buildNumber,
                                     const std::string& combinedVersionString,
                                     const std::vector<std::string>& exteriorLocations,
                                     const TExteriorJumpPoints& exteriorJumpPoints,
                                     const TInteriorJumpPoints& interiorJumpPoints
                                     );

            const std::string& Name() const;

            const std::string& EegeoApiKey() const;

            const Eegeo::Space::LatLongAltitude& InterestLocation() const;

            float OrientationDegrees() const;

            const std::string& ProductVersion() const;

            const std::string& BuildNumber() const;

            const std::string& CombinedVersionString() const;

            const std::vector<std::string>& GetLocations() const;

            const TExteriorJumpPoints& GetExteriorJumpPoints() const;

            const TInteriorJumpPoints& GetInteriorJumpPoints() const;
        };
    }
}
