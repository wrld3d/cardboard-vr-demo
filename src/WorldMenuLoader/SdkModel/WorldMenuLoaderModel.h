// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IVRDistortionTransitionModel.h"
#include "ICallback.h"
#include "WorldMenuScreenFader.h"
#include "WorldMenuItemRepository.h"

namespace Examples
{
    namespace WorldMenuLoader
    {
        namespace SdkModel
        {
            class WorldMenuLoaderModel : private Eegeo::NonCopyable
            {
            public:
                WorldMenuLoaderModel(Eegeo::UI::WorldMenu::WorldMenuItemRepository& menuItemRepository,
                                     Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransisionModel);
                ~WorldMenuLoaderModel();

                void OnWorldMenuItemGazed(Eegeo::UI::WorldMenu::WorldMenuItem& menuItem);
                void OnScreenVisiblityChanged(WorldMenuScreenFader::VisibilityState& visbilityState);

                void Update(float dt);

            private:
                Eegeo::UI::WorldMenu::WorldMenuItemRepository& m_menuItemRepository;
                WorldMenuScreenFader* m_pScreenFader;
                Eegeo::UI::WorldMenu::WorldMenuItem* m_pMenuItem;
                Eegeo::Helpers::TCallback1<WorldMenuLoaderModel, Eegeo::UI::WorldMenu::WorldMenuItem&> m_worldMenuItemGazeCallback;
                Eegeo::Helpers::TCallback1<WorldMenuLoaderModel, WorldMenuScreenFader::VisibilityState&> m_screenVisibilityChanged;
            };
        }
    }
}