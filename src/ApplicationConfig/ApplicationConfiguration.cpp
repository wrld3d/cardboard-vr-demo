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
                                                           const std::string& sfSplineWelcomeNote,
                                                           const std::string& ukSplineWelcomeNote,
                                                           const std::string& nySplineWelcomeNote,
                                                           const std::string& jumpPointsSpriteSheet,
                                                           const int jumpPointsSpriteSheetSize,
                                                           const TWorldLocations& worldLocations,
                                                           const TExteriorJumpPoints& exteriorJumpPoints,
                                                           const TInteriorJumpPoints& interiorJumpPoints
                                                           )
        : m_name(name)
        , m_eegeoApiKey(eegeoApiKey)
        , m_interestLocation(interestLocation)
        , m_orientationDegrees(orientationDegrees)
        , m_coverageTreeManifestURL(coverageTreeManifestURL)
        , m_themeManifestURL(themeManifestURL)
        , m_gazePointTexturePath(gazePointTexture)
        , m_gazeLoaderTexturePath(gazeLoaderTexture)
        , m_gazeLoaderNumberOfTilesAlong1Axis(gazeLoaderNumberOfTilesAlong1Axis)
        , m_gazeLoaderFrameRate(gazeLoaderFrameRate)
        , m_productVersion(productVersion)
        , m_buildNumber(buildNumber)
        , m_combinedVersionString(combinedVersionString)
        , m_sfWelcomeNotePath(sfWelcomeNote)
        , m_ukWelcomeNotePath(ukWelcomeNote)
        , m_nyWelcomeNotePath(nyWelcomeNote)
        , m_sfSplineWelcomeNotePath(sfSplineWelcomeNote)
        , m_ukSplineWelcomeNotePath(ukSplineWelcomeNote)
        , m_nySplineWelcomeNotePath(nySplineWelcomeNote)
        , m_jumpPointsSpriteSheet(jumpPointsSpriteSheet)
        , m_jumpPointsSpriteSheetSize(jumpPointsSpriteSheetSize)
        , m_worldLocations(worldLocations)
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

        const std::string& ApplicationConfiguration::CoverageTreeManifestURL() const
        {
            return m_coverageTreeManifestURL;
        }

        const std::string& ApplicationConfiguration::ThemeManifestURL() const
        {
            return m_themeManifestURL;
        }
        
        const std::string& ApplicationConfiguration::GazePointTexturePath() const
        {
            return m_gazePointTexturePath;
        }

        const std::string& ApplicationConfiguration::GazeLoaderTexturePath() const
        {
            return m_gazeLoaderTexturePath;
        }

        int ApplicationConfiguration::GazeLoaderNumberOfTilesAlong1Axis() const
        {
            return m_gazeLoaderNumberOfTilesAlong1Axis;
        }

        float ApplicationConfiguration::GazeLoaderFrameRate() const
        {
            return m_gazeLoaderFrameRate;
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

        const std::string& ApplicationConfiguration::SFWelcomeNotePath() const
        {
            return m_sfWelcomeNotePath;
        }

        const std::string& ApplicationConfiguration::UKWelcomeNotePath() const
        {
            return m_ukWelcomeNotePath;
        }

        const std::string& ApplicationConfiguration::NYWelcomeNotePath() const
        {
            return m_nyWelcomeNotePath;
        }

        const std::string& ApplicationConfiguration::SFSplineWelcomeNotePath() const
        {
            return m_sfSplineWelcomeNotePath;
        }

        const std::string& ApplicationConfiguration::UKSplineWelcomeNotePath() const
        {
            return m_ukSplineWelcomeNotePath;
        }

        const std::string& ApplicationConfiguration::NYSplineWelcomeNotePath() const
        {
            return m_nySplineWelcomeNotePath;
        }

        const std::string& ApplicationConfiguration::JumpPointsSpriteSheet() const
        {
            return m_jumpPointsSpriteSheet;
        }

        const int ApplicationConfiguration::JumpPointsSpriteSheetSize() const
        {
            return m_jumpPointsSpriteSheetSize;
        }

        const TWorldLocations& ApplicationConfiguration::GetLocations() const
        {
            return m_worldLocations;
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
