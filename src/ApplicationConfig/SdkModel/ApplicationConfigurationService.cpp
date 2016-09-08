// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationService.h"
#include "IApplicationConfigurationParser.h"
#include "IApplicationConfigurationReader.h"

namespace Examples
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            ApplicationConfigurationService::ApplicationConfigurationService(IApplicationConfigurationParser& parser,
                                                                             IApplicationConfigurationReader& reader,
                                                                             const std::string& productVersion,
                                                                             const std::string& buildNumber)
            : m_parser(parser)
            , m_reader(reader)
            , m_productVersion(productVersion)
            , m_buildNumber(buildNumber)
            {
                
            }
            
            ApplicationConfiguration ApplicationConfigurationService::LoadConfiguration(const std::string& path)
            {
                std::string serialized(m_reader.ReadApplicationConfiguration(path));
                const ApplicationConfiguration& parsedConfig = m_parser.ParseConfiguration(serialized);
                
                const std::string combinedVersionString = m_productVersion + "." + m_buildNumber;
                
                return ApplicationConfiguration(parsedConfig.Name(),
                								parsedConfig.EegeoApiKey(),
                                                parsedConfig.InterestLocation(),
                                                parsedConfig.OrientationDegrees(),
                                                parsedConfig.CoverageTreeManifestURL(),
                                                parsedConfig.ThemeManifestURL(),
                                                parsedConfig.GazePointTexturePath(),
                                                parsedConfig.GazeLoaderTexturePath(),
                                                parsedConfig.GazeLoaderNumberOfTilesAlong1Axis(),
                                                parsedConfig.GazeLoaderFrameRate(),
                                                m_productVersion,
                                                m_buildNumber,
                                                combinedVersionString,
                                                parsedConfig.SFWelcomeNotePath(),
                                                parsedConfig.UKWelcomeNotePath(),
                                                parsedConfig.NYWelcomeNotePath(),
                                                parsedConfig.JumpPointsSpriteSheet(),
                                                parsedConfig.JumpPointsSpriteSheetSize(),
                                                parsedConfig.GetLocations(),
                                                parsedConfig.GetExteriorJumpPoints(),
                                                parsedConfig.GetInteriorJumpPoints()
                                                );
            }
        }
    }
}
