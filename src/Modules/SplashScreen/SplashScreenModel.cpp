// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SplashScreenModel.h"
#include "SceneModelTransformHelpers.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            SplashScreenModel::SplashScreenModel(Rendering::SceneModels::SceneModel* pModel,
                                                 const Eegeo::dv3& position,
                                                 float absoluteHeadingDegrees)
            : m_pModel(pModel)
            , m_position(position)
            , m_absoluteHeadingDegrees(absoluteHeadingDegrees)
            {
                Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel, m_position, m_absoluteHeadingDegrees);
            }

            SplashScreenModel::~SplashScreenModel()
            {
                Eegeo_DELETE m_pModel;
            }

            const dv3& SplashScreenModel::GetEcefPosition() const
            {
                return m_pModel->GetEcefPosition();
            }

            void SplashScreenModel::SetEcefPosition(const dv3& ecefPosition)
            {
                m_pModel->SetEcefPosition(ecefPosition);
            }

            void SplashScreenModel::SetScale(float scale)
            {
                Eegeo::m44 scaleMatrix;
                scaleMatrix.Scale(scale);

                Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel, m_position, m_absoluteHeadingDegrees, scaleMatrix);
            }

            Rendering::SceneModels::SceneModel& SplashScreenModel::GetSceneModel()
            {
                return *m_pModel;
            }
        }
    }
}
