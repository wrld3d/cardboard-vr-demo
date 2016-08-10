// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "ApplicationConfig.h"
#include "IApplicationConfigurationBuilder.h"
#include "Types.h"
#include <map>
#include <vector>

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
                float m_orientationDegrees;
                std::string m_productVersion;
                std::string m_buildNumber;
                std::string m_combinedVersionString;

                std::string m_jumpPointsSpriteSheet;
                int m_jumpPointsSpriteSheetSize;

                TWorldLocations m_exteriorLocations;
                TExteriorJumpPoints m_exteriorJumpPoints;
                TInteriorJumpPoints m_interiorJumpPoints;

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

                IApplicationConfigurationBuilder& SetJumpPointSpriteSheet(const std::string& spriteSheet);

                IApplicationConfigurationBuilder& SetJumpPointSpriteSheetSize(const int spriteSheetSize);

                IApplicationConfigurationBuilder& SetExteriorLocations(const TWorldLocations& exteriorLocations);

                IApplicationConfigurationBuilder& AddExteriorJumpPoints(const std::string& locationName, const TJumpPointVector& jumpPoints);

                IApplicationConfigurationBuilder& AddInteriorJumpPoints(const std::string& locationName, const TInteriorFloorJumpPoints& jumpPoints);

                ApplicationConfiguration Build();
            };
        }
    }
}
