// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <map>
#include <vector>

namespace Examples
{
    namespace ApplicationConfig
    {
        class JumpPointConfigData;
        class ApplicationConfiguration;

        typedef std::vector<JumpPointConfigData> TJumpPointVector;
        typedef std::map<std::string,TJumpPointVector> TExteriorJumpPoints;
        typedef std::map<int,TJumpPointVector> TInteriorFloorJumpPoints;
        typedef std::map<std::string,TInteriorFloorJumpPoints> TInteriorJumpPoints;
        
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
