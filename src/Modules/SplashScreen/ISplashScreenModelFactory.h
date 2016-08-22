// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>
#include "SplashScreenModel.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            class ISplashScreenModelFactory
            {
            public:
                virtual ~ISplashScreenModelFactory() {};

                virtual SplashScreenModel* CreateSplashScreenModel(const std::string& assetPath,
                                                                   const Eegeo::dv3& position,
                                                                   float absoluteHeadingDegrees) = 0;
            };
            
        }
    }
}
