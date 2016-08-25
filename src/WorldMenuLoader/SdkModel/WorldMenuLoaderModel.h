// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IVRDistortionTransitionModel.h"
#include "ICallback.h"
#include "WorldMenuScreenFader.h"
#include "WorldMenuItemRepository.h"
#include "ApplicationConfig.h"

#include <string>

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
                                     Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransisionModel,
                                     const ApplicationConfig::ApplicationConfiguration& appConfig);
                ~WorldMenuLoaderModel();

                void OnWorldMenuItemGazed(Eegeo::UI::WorldMenu::WorldMenuItem& menuItem);
                void OnScreenVisiblityChanged(WorldMenuScreenFader::VisibilityState& visbilityState);

                void Update(float dt);

                const std::string& GetCurrentSelectedLocation() const;

                void RegisterLocationChangedCallback(Eegeo::Helpers::ICallback1<std::string&>& callback);
                void UnregisterLocationChangedCallback(Eegeo::Helpers::ICallback1<std::string&>& callback);

                bool GetShouldRunVRSpline(){return m_shouldRunVRSpline;}

                WorldMenuScreenFader& GetWorldMenuScreenFader();
                
            private:
                Eegeo::UI::WorldMenu::WorldMenuItemRepository& m_menuItemRepository;
                WorldMenuScreenFader* m_pScreenFader;

                typedef std::vector<Eegeo::UI::WorldMenu::WorldMenuItem*> TWorldMenuItems;
                TWorldMenuItems  m_pWorldMenuItems;

                std::string m_selectedLocation;
                bool m_locationHasChanged;

                Eegeo::Helpers::TCallback1<WorldMenuLoaderModel, Eegeo::UI::WorldMenu::WorldMenuItem&> m_worldMenuItemGazeCallback;
                Eegeo::Helpers::TCallback1<WorldMenuLoaderModel, WorldMenuScreenFader::VisibilityState&> m_screenVisibilityChanged;

                Eegeo::Helpers::CallbackCollection1<std::string&> m_locationChangedCallbacks;
                
                bool m_shouldRunVRSpline;
                int m_lastMenuItemGazedId;

                void NotifyLocationChange(std::string& location);
            };
        }
    }
}
