// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SplashScreenModelFactory.h"
#include "SceneModel.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            SplashScreenModelFactory::SplashScreenModelFactory(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader)
            : m_sceneModelLoader(sceneModelLoader)
            {
            }

            SplashScreenModel* SplashScreenModelFactory::CreateSplashScreenModel(const std::string& assetPath,
                                                                                 const Eegeo::dv3& position,
                                                                                 float absoluteHeadingDegrees)
            {
                Rendering::SceneModels::SceneModel* pModel = m_sceneModelLoader.LoadPOD(assetPath);

                return Eegeo_NEW(SplashScreenModel)(pModel, position, absoluteHeadingDegrees);
            }
        }
    }
}
