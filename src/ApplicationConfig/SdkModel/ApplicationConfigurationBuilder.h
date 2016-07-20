// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationBuilder.h"
#include "Types.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            class ApplicationConfigurationBuilder : public IApplicationConfigurationBuilder, private Eegeo::NonCopyable
            {
            private:
                std::string m_name;
                std::string m_eegeoApiKey;
                Eegeo::Space::LatLongAltitude m_interestLocation;
                float m_distanceToInterestMetres;
                float m_orientationDegrees;
                std::string m_productVersion;
                std::string m_buildNumber;
                std::string m_combinedVersionString;
                
                
            public:
                ApplicationConfigurationBuilder();
                
                IApplicationConfigurationBuilder& SetApplicationName(const std::string& name);
                
                IApplicationConfigurationBuilder& SetEegeoApiKey(const std::string& eegeoApiKey);
                
                IApplicationConfigurationBuilder& SetStartInterestPointLocation(const Eegeo::Space::LatLongAltitude& location);
                
                IApplicationConfigurationBuilder& SetStartDistanceFromInterestPoint(float distanceMetres);
                
                IApplicationConfigurationBuilder& SetStartOrientationAboutInterestPoint(float degrees);
                
                IApplicationConfigurationBuilder& SetProductVersion(const std::string& productVersion);
                
                IApplicationConfigurationBuilder& SetBuildNumber(const std::string& buildNumber);
                
                IApplicationConfigurationBuilder& SetCombinedVersionString(const std::string& combinedVersionString);
                
                ApplicationConfiguration Build();
            };
        }
    }
}
