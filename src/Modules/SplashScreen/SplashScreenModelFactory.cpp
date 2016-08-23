// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SplashScreenModelFactory.h"
#include "SceneModel.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            SplashScreenModelFactory::SplashScreenModelFactory(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                                               Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& sceneModelMaterials)
            : m_sceneModelLoader(sceneModelLoader)
            , m_sceneModelMaterials(sceneModelMaterials)
            {
            }

            SplashScreenModel* SplashScreenModelFactory::CreateSplashScreenModel(const std::string& assetPath,
                                                                                 const TMaterialNames& materialNames,
                                                                                 const Eegeo::dv3& position,
                                                                                 float absoluteHeadingDegrees)
            {
                Rendering::SceneModels::SceneModel* pModel = m_sceneModelLoader.LoadPOD(assetPath);

                TMaterialResources materials;

                for (TMaterialNames::const_iterator it = materialNames.begin(); it != materialNames.end(); ++it)
                {
                    materials.push_back(LoadAlphaMaterial(*it));
                }

                return Eegeo_NEW(SplashScreenModel)(pModel, materials, position, absoluteHeadingDegrees);
            }

            Eegeo::Rendering::SceneModels::SceneModelMaterialResource* SplashScreenModelFactory::LoadAlphaMaterial(const std::string& materialId)
            {
                if(!m_sceneModelMaterials.HasResource(materialId))
                {
                    Eegeo_TTY("Failed to find material.\n");
                }
                else
                {
                    return &m_sceneModelMaterials.UseResource(materialId);
                }

                return NULL;
            }
        }
    }
}
