// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>

#include "Types.h"
#include "SceneModel.h"
#include "SceneModelFactory.h"
#include "SceneModelMaterialResource.h"
#include "SceneModelRenderableFilter.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            typedef std::vector<Eegeo::Rendering::SceneModels::SceneModelMaterialResource*> TMaterialResources;

            class SplashScreenModel : protected Eegeo::NonCopyable
            {
            private:
                Eegeo::Rendering::Filters::SceneModelRenderableFilter& m_sceneModelRenderableFilter;
                Rendering::SceneModels::SceneModel* m_pModel;
                Eegeo::dv3 m_position;
                float m_absoluteHeadingDegrees;
                bool m_shouldDisplay;
                float m_modelAlpha;
                float m_fadeTransitionSpeed;
                bool m_isRendering;

                TMaterialResources m_materialResources;

                void UpdateMaterials();

            public:
                SplashScreenModel(Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter,
                                  Rendering::SceneModels::SceneModel* pModel,
                                  TMaterialResources& materialResources,
                                  const Eegeo::dv3& position,
                                  float absoluteHeadingDegrees);

                ~SplashScreenModel();

                void Update(float dt);

                const dv3& GetEcefPosition() const;

                void SetEcefPosition(const dv3& ecefPosition);

                void SetScale(float scale);

                float GetAbsoluteHeadingDegrees() const;

                void SetAbsoluteHeadingDegrees(float absoluteHeadingDegrees);

                Rendering::SceneModels::SceneModel& GetSceneModel() const;

                bool GetShouldDisplay() const;

                void SetShouldDisplay(bool shouldDisplay);

                void SetFadeTransitionSpeed(float speed);
            };
            
        }
    }
}
