// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "WorldMenuLoaderModel.h"
#include "Logger.h"

#define SCREEN_FADE_TRANSITION_TIME 1.0f

namespace Examples
{
    namespace WorldMenuLoader
    {
        namespace SdkModel
        {
            WorldMenuLoaderModel::WorldMenuLoaderModel( Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransisionModel,
                                                        Eegeo::Helpers::ICallback0& onBlackOutCallback)
            : m_screenVisibilityChanged(this, &WorldMenuLoaderModel::OnScreenVisiblityChanged)
            , m_onBlackOutCallback(onBlackOutCallback)
            {
                m_pScreenFader = Eegeo_NEW(WorldMenuScreenFader)(screenTransisionModel, SCREEN_FADE_TRANSITION_TIME);
                m_pScreenFader->RegisterVisibilityChangedCallback(m_screenVisibilityChanged);
            }

            WorldMenuLoaderModel::~WorldMenuLoaderModel()
            {

                m_pScreenFader->UnregisterVisibilityChangedCallback(m_screenVisibilityChanged);
                Eegeo_DELETE m_pScreenFader;
            }

            void WorldMenuLoaderModel::Update(float dt)
            {
                m_pScreenFader->Update(dt);
            }

            void WorldMenuLoaderModel::FadeIn()
            {
                m_pScreenFader->SetShouldFadeToBlack(true);
            }

            void WorldMenuLoaderModel::OnScreenVisiblityChanged(WorldMenuScreenFader::VisibilityState &visbilityState)
            {
                if (visbilityState == WorldMenuScreenFader::VisibilityState::FullyFaded)
                {
                    m_onBlackOutCallback();
                    m_pScreenFader->SetShouldFadeToBlack(false);
                }
            }
        }
    }
}
