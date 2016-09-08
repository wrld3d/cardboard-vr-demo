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
                std::string m_coverageTreeManifestURL;
                std::string m_themeManifestURL;
                std::string m_gazePointTexturePath;
                std::string m_gazeLoaderTexturePath;
                int m_gazeLoaderNumberOfTilesAlong1Axis;
                float m_gazeLoaderFrameRate;
                std::string m_productVersion;
                std::string m_buildNumber;
                std::string m_combinedVersionString;

                std::string m_sfWelcomeNotePath;
                std::string m_ukWelcomeNotePath;
                std::string m_nyWelcomeNotePath;
                std::string m_sfSplineWelcomeNotePath;
                std::string m_ukSplineWelcomeNotePath;
                std::string m_nySplineWelcomeNotePath;

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

                IApplicationConfigurationBuilder& SetCoverageTreeManifestURL(const std::string& coverageTreeManifestUrl);

                IApplicationConfigurationBuilder& SetThemeManifestURL(const std::string& themesManifestUrl);

                IApplicationConfigurationBuilder& SetGazePointTexturePath(const std::string& gazePointTexture);

                IApplicationConfigurationBuilder& SetGazeLoaderTexturePath(const std::string& gazeLoaderTexture);

                IApplicationConfigurationBuilder& SetGazeLoaderNumberOfTilesAlong1Axis(int gazeLoaderNumberOfTilesAlong1Axis);

                IApplicationConfigurationBuilder& SetGazeLoaderFrameRate(double gazeLoaderFrameRate);

                IApplicationConfigurationBuilder& SetProductVersion(const std::string& productVersion);

                IApplicationConfigurationBuilder& SetBuildNumber(const std::string& buildNumber);

                IApplicationConfigurationBuilder& SetCombinedVersionString(const std::string& combinedVersionString);

                IApplicationConfigurationBuilder& SetSFWelcomeNotePath(const std::string& sfWelcomeNote);

                IApplicationConfigurationBuilder& SetUKWelcomeNotePath(const std::string& ukWelcomeNote);

                IApplicationConfigurationBuilder& SetNYWelcomeNotePath(const std::string& nyWelcomeNote);

                IApplicationConfigurationBuilder& SetSFSplineWelcomeNotePath(const std::string& sfWelcomeNote);

                IApplicationConfigurationBuilder& SetUKSplineWelcomeNotePath(const std::string& ukWelcomeNote);

                IApplicationConfigurationBuilder& SetNYSplineWelcomeNotePath(const std::string& nyWelcomeNote);

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
