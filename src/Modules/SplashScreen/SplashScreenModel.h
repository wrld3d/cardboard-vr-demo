// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "SceneModel.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            class SplashScreenModel : protected Eegeo::NonCopyable
            {
            private:
                Rendering::SceneModels::SceneModel* m_pModel;
                Eegeo::dv3 m_position;
                float m_absoluteHeadingDegrees;

            public:
                SplashScreenModel(Rendering::SceneModels::SceneModel* pModel,
                                  const Eegeo::dv3& position,
                                  float absoluteHeadingDegrees);

                ~SplashScreenModel();

                const dv3& GetEcefPosition() const;

                void SetEcefPosition(const dv3& ecefPosition);

                void SetScale(float scale);

                Rendering::SceneModels::SceneModel& GetSceneModel();
            };
            
        }
    }
}
