// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <string>
#include <map>
#include <vector>
#include "ApplicationConfig.h"
#include "LatLongAltitude.h"
#include "JumpPointConfigData.h"
#include "WorldLocationData.h"

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

            const std::string m_coverageTreeManifestURL;
            const std::string m_themeManifestURL;

            const std::string m_gazePointTexturePath;
            const std::string m_gazeLoaderTexturePath;
            const int m_gazeLoaderNumberOfTilesAlong1Axis;
            const float m_gazeLoaderFrameRate;

            const std::string m_productVersion;
            const std::string m_buildNumber;
            const std::string m_combinedVersionString;

            const std::string m_sfWelcomeNotePath;
            const std::string m_ukWelcomeNotePath;
            const std::string m_nyWelcomeNotePath;

            const std::string m_jumpPointsSpriteSheet;
            const int m_jumpPointsSpriteSheetSize;

            const TExteriorJumpPoints m_exteriorJumpPoints;
            const TInteriorJumpPoints m_interiorJumpPoints;
            const TWorldLocations m_worldLocations;
        public:

            ApplicationConfiguration(const std::string& name,
                                     const std::string& eegeoApiKey,
                                     const Eegeo::Space::LatLongAltitude& interestLocation,
                                     float orientationDegrees,
                                     const std::string& coverageTreeManifestURL,
                                     const std::string& themeManifestURL,
                                     const std::string& gazePointTexture,
                                     const std::string& gazeLoaderTexture,
                                     int gazeLoaderNumberOfTilesAlong1Axis,
                                     float gazeLoaderFrameRate,
                                     const std::string& productVersion,
                                     const std::string& buildNumber,
                                     const std::string& combinedVersionString,
                                     const std::string& sfWelcomeNote,
                                     const std::string& ukWelcomeNote,
                                     const std::string& nyWelcomeNote,
                                     const std::string& jumpPointsSpriteSheet,
                                     const int jumpPointsSpriteSheetSize,
                                     const TWorldLocations& worldLocations,
                                     const TExteriorJumpPoints& exteriorJumpPoints,
                                     const TInteriorJumpPoints& interiorJumpPoints
                                     );

            const std::string& Name() const;

            const std::string& EegeoApiKey() const;

            const Eegeo::Space::LatLongAltitude& InterestLocation() const;

            float OrientationDegrees() const;

            const std::string& CoverageTreeManifestURL() const;

            const std::string& ThemeManifestURL() const;

            const std::string& GazePointTexturePath() const;

            const std::string& GazeLoaderTexturePath() const;

            int GazeLoaderNumberOfTilesAlong1Axis() const;

            float GazeLoaderFrameRate() const;

            const std::string& ProductVersion() const;

            const std::string& BuildNumber() const;

            const std::string& CombinedVersionString() const;

            const std::string& SFWelcomeNotePath() const;

            const std::string& UKWelcomeNotePath() const;

            const std::string& NYWelcomeNotePath() const;

            const std::string& JumpPointsSpriteSheet() const;

            const int JumpPointsSpriteSheetSize() const;

            const TWorldLocations& GetLocations() const;

            const TExteriorJumpPoints& GetExteriorJumpPoints() const;

            const TInteriorJumpPoints& GetInteriorJumpPoints() const;
        };
    }
}
