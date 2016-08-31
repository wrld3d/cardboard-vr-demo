// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IVRDistortionTransitionModel.h"
#include "ICallback.h"
#include "IScreenFadeEffectController.h"

namespace Examples
{
    namespace ScreenFadeEffect
    {
        namespace SdkModel
        {
            class ScreenFadeEffectController : public IScreenFadeEffectController, protected Eegeo::NonCopyable
            {
            public:

                ScreenFadeEffectController(Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransitionModel,
                                     float transitionTimeSeconds);
                virtual ~ScreenFadeEffectController();

                virtual void SetShouldFadeToBlack(bool shouldFade);
                virtual bool GetShouldFadeToBlack() const { return m_shouldFadeToBlack; }

                void Update(float dt);

                virtual void RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback);
                virtual void UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback);

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
