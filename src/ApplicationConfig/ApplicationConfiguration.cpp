// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfiguration.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        ApplicationConfiguration::ApplicationConfiguration(const std::string& name,
                                                           const std::string& eegeoApiKey,
                                                           const Eegeo::Space::LatLongAltitude& interestLocation,
                                                           float orientationDegrees,
                                                           const std::string& productVersion,
                                                           const std::string& buildNumber,
                                                           const std::string& combinedVersionString,
                                                           const std::vector<std::string>& exteriorLocations,
                                                           const TExteriorJumpPoints& exteriorJumpPoints,
                                                           const TInteriorJumpPoints& interiorJumpPoints
                                                           )
        : m_name(name)
        , m_eegeoApiKey(eegeoApiKey)
        , m_interestLocation(interestLocation)
        , m_orientationDegrees(orientationDegrees)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        , m_exteriorLocations(exteriorLocations)
        , m_exteriorJumpPoints(exteriorJumpPoints)
        , m_interiorJumpPoints(interiorJumpPoints)
        {
            
        }
        
        const std::string& ApplicationConfiguration::Name() const
        {
            return m_name;
        }
        
        const std::string& ApplicationConfiguration::EegeoApiKey() const
        {
            return m_eegeoApiKey;
        }
        
        const Eegeo::Space::LatLongAltitude& ApplicationConfiguration::InterestLocation() const
        {
            return m_interestLocation;
        }
        
        float ApplicationConfiguration::OrientationDegrees() const
        {
            return m_orientationDegrees;
        }
        
        const std::string& ApplicationConfiguration::ProductVersion() const
        {
            return m_productVersion;
        }
        
        const std::string& ApplicationConfiguration::BuildNumber() const
        {
            return m_buildNumber;
        }
        
        const std::string& ApplicationConfiguration::CombinedVersionString() const
        {
            return m_combinedVersionString;
        }

        const std::vector<std::string>& ApplicationConfiguration::GetLocations() const
        {
            return m_exteriorLocations;
        }

        const TExteriorJumpPoints& ApplicationConfiguration::GetExteriorJumpPoints() const
        {
            return m_exteriorJumpPoints;
        }

        const TInteriorJumpPoints& ApplicationConfiguration::GetInteriorJumpPoints() const
        {
            return m_interiorJumpPoints;
        }
    }
}
