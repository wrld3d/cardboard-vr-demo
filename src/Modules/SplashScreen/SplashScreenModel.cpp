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
                                                 TMaterialResources& materialResources,
                                                 const Eegeo::dv3& position,
                                                 float absoluteHeadingDegrees)
            : m_pModel(pModel)
            , m_materialResources(materialResources)
            , m_position(position)
            , m_absoluteHeadingDegrees(absoluteHeadingDegrees)
            , m_shouldDisplay(true)
            , m_modelAlpha(0.f)
            , m_fadeTransitionSpeed(1.f)
            {
                Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel, m_position, m_absoluteHeadingDegrees);
                UpdateMaterials();
            }

            SplashScreenModel::~SplashScreenModel()
            {
                Eegeo_DELETE m_pModel;

                for (TMaterialResources::iterator it = m_materialResources.begin(); it != m_materialResources.end(); ++it)
                {
                    if((*it) != NULL)
                    {
                        (*it)->DecrementReferenceCount();
                    }
                }
            }

            void SplashScreenModel::Update(float dt)
            {
                const bool shouldFadeIn = m_shouldDisplay && m_modelAlpha < 1.f;
                const bool shouldFadeOut = !m_shouldDisplay && m_modelAlpha > 0.f;

                if (shouldFadeIn)
                {
                    m_modelAlpha += (dt * m_fadeTransitionSpeed);
                }
                else if (shouldFadeOut)
                {
                    m_modelAlpha -= (dt * m_fadeTransitionSpeed);
                }

                UpdateMaterials();
            }

            void SplashScreenModel::UpdateMaterials()
            {
                for (TMaterialResources::iterator it = m_materialResources.begin(); it != m_materialResources.end(); ++it)
                {
                    if((*it) != NULL)
                    {
                        (*it)->GetMaterial()->SetAlpha(m_modelAlpha);
                    }
                }
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

            float SplashScreenModel::GetAbsoluteHeadingDegrees() const
            {
                return m_absoluteHeadingDegrees;
            }

            void SplashScreenModel::SetAbsoluteHeadingDegrees(float absoluteHeadingDegrees)
            {
                m_absoluteHeadingDegrees = absoluteHeadingDegrees;
                Eegeo::Rendering::SceneModels::SceneModelTransformHelpers::PositionOnEarthSurface(*m_pModel, m_position, m_absoluteHeadingDegrees);
            }

            Rendering::SceneModels::SceneModel& SplashScreenModel::GetSceneModel() const
            {
                return *m_pModel;
            }

            bool SplashScreenModel::GetShouldDisplay() const
            {
                return m_shouldDisplay;
            }

            void SplashScreenModel::SetShouldDisplay(bool shouldDisplay)
            {
                m_shouldDisplay = shouldDisplay;
            }

            void SplashScreenModel::SetFadeTransitionSpeed(float speed)
            {
                m_fadeTransitionSpeed = speed;
            }
        }
    }
}
