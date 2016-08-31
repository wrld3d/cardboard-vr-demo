// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <vector>

namespace Examples
{
    namespace ApplicationConfig
    {
        class WorldLocationData;
        class JumpPointConfigData;
        class ApplicationConfiguration;

        typedef std::vector<JumpPointConfigData> TJumpPointVector;
        typedef std::map<std::string,TJumpPointVector> TExteriorJumpPoints;
        typedef std::map<int,TJumpPointVector> TInteriorFloorJumpPoints;
        typedef std::map<std::string,TInteriorFloorJumpPoints> TInteriorJumpPoints;
        typedef std::map<std::string, WorldLocationData> TWorldLocations;
        
        namespace SdkModel
        {
            class IApplicationConfigurationBuilder;
            class IApplicationConfigurationModule;
            class IApplicationConfigurationReader;
            class IApplicationConfigurationParser;
            class IApplicationConfigurationService;
        }
    }
}
