// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

#include "SceneModelLoader.h"

#include "SplashScreenModel.h"
#include "ISplashScreenModelFactory.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            class SplashScreenModelFactory : public ISplashScreenModelFactory
            {
            private:
                Eegeo::Rendering::SceneModels::SceneModelLoader& m_sceneModelLoader;

            public:
                SplashScreenModelFactory(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader);

                virtual SplashScreenModel* CreateSplashScreenModel(const std::string& assetPath,
                                                                   const Eegeo::dv3& position,
                                                                   float absoluteHeadingDegrees);
            };
            
        }
    }
}
