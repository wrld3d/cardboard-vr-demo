// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <string>

#include "SceneModelLoader.h"
#include "SceneModelFactory.h"
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
                Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& m_sceneModelMaterials;

                Eegeo::Rendering::SceneModels::SceneModelMaterialResource* LoadAlphaMaterial(const std::string& materialName);
            public:
                SplashScreenModelFactory(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                         Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& sceneModelMaterials);

                virtual SplashScreenModel* CreateSplashScreenModel(const std::string& assetPath,
                                                                   const TMaterialNames& materialNames,
                                                                   const Eegeo::dv3& position,
                                                                   float absoluteHeadingDegrees);
            };
            
        }
    }
}
