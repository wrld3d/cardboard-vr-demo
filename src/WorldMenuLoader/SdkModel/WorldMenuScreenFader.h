// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IVRDistortionTransitionModel.h"
#include "ICallback.h"

namespace Examples
{
    namespace WorldMenuLoader
    {
        namespace SdkModel
        {
            class WorldMenuScreenFader : private Eegeo::NonCopyable
            {
            public:

                enum VisibilityState
                {
                    FullyFaded,
                    Transitioning,
                    FullyVisible
                };

                WorldMenuScreenFader(Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransitionModel,
                                     float transitionTimeSeconds);
                ~WorldMenuScreenFader();

                void SetShouldFadeToBlack(bool shouldFade);
                bool GetShouldFadeToBlack() const { return m_shouldFadeToBlack; }

                void Update(float dt);

                void RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback);
                void UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback);

            private:

                Eegeo::VR::Distortion::IVRDistortionTransitionModel& m_screenTransitionModel;
                const float m_transitionTimeSeconds;
                
                float m_transitionParameter;
                bool m_shouldFadeToBlack;
                
                VisibilityState m_currentVisibiltyState;
                
                Eegeo::Helpers::CallbackCollection1<VisibilityState&> m_visibilityChangedCallbacks;
                
                void NotifyStateChange();
            };
        }
    }
}
