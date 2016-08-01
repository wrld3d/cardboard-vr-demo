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
            WorldMenuLoaderModel::WorldMenuLoaderModel(Eegeo::UI::WorldMenu::WorldMenuItemRepository& menuItemRepository,
                                                       Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransisionModel)
            : m_menuItemRepository(menuItemRepository)
            , m_worldMenuItemGazeCallback(this, &WorldMenuLoaderModel::OnWorldMenuItemGazed)
            , m_screenVisibilityChanged(this, &WorldMenuLoaderModel::OnScreenVisiblityChanged)
            {
                m_pScreenFader = Eegeo_NEW(WorldMenuScreenFader)(screenTransisionModel, SCREEN_FADE_TRANSITION_TIME);
                m_pScreenFader->RegisterVisibilityChangedCallback(m_screenVisibilityChanged);

                m_pMenuItem =  Eegeo_NEW(Eegeo::UI::WorldMenu::WorldMenuItem)(10, 8, m_worldMenuItemGazeCallback);
                m_menuItemRepository.AddWorldMenuItem(m_pMenuItem);
            }

            WorldMenuLoaderModel::~WorldMenuLoaderModel()
            {
                m_menuItemRepository.RemoveWorldMenuItem(m_pMenuItem);
                Eegeo_DELETE m_pMenuItem;

                m_pScreenFader->UnregisterVisibilityChangedCallback(m_screenVisibilityChanged);
                Eegeo_DELETE m_pScreenFader;
            }

            void WorldMenuLoaderModel::Update(float dt)
            {
                m_pScreenFader->Update(dt);
            }

            void WorldMenuLoaderModel::OnWorldMenuItemGazed(Eegeo::UI::WorldMenu::WorldMenuItem &menuItem)
            {
                m_pScreenFader->SetShouldFadeToBlack(true);
            }

            void WorldMenuLoaderModel::OnScreenVisiblityChanged(WorldMenuScreenFader::VisibilityState &visbilityState)
            {
                if (visbilityState == WorldMenuScreenFader::VisibilityState::FullyFaded)
                {
                    m_pScreenFader->SetShouldFadeToBlack(false);
                }
            }
        }
    }
}
