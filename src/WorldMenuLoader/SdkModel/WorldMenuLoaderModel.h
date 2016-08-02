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
                WorldMenuLoaderModel(Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransisionModel,
                                     Eegeo::Helpers::ICallback0& onBlackOutCallback);
                ~WorldMenuLoaderModel();

                void FadeIn();
                
                void OnScreenVisiblityChanged(WorldMenuScreenFader::VisibilityState& visbilityState);

                void Update(float dt);

            private:
                
                WorldMenuScreenFader* m_pScreenFader;
                Eegeo::UI::WorldMenu::WorldMenuItem* m_pMenuItem;
                Eegeo::Helpers::TCallback1<WorldMenuLoaderModel, WorldMenuScreenFader::VisibilityState&> m_screenVisibilityChanged;
                Eegeo::Helpers::ICallback0& m_onBlackOutCallback;
            };
        }
    }
}