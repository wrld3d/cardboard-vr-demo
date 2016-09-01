// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ScreenFadeEffectController.h"
#include "MathFunc.h"

namespace Examples
{
    namespace ScreenFadeEffect
    {
        namespace SdkModel
        {
            ScreenFadeEffectController::ScreenFadeEffectController(Eegeo::VR::Distortion::IVRDistortionTransitionModel& screenTransitionModel,
                                                       float transitionTimeSeconds)
            : m_screenTransitionModel(screenTransitionModel)
            , m_shouldFadeToBlack(false)
            , m_transitionParameter(2.0f)
            , m_transitionTimeSeconds(Eegeo::Max(transitionTimeSeconds, 0.0f))
            , m_currentVisibiltyState(VisibilityState::FullyVisible)
            {

            }

            ScreenFadeEffectController::~ScreenFadeEffectController()
            {}

            void ScreenFadeEffectController::SetShouldFadeToBlack(bool shouldFade)
            {
                m_shouldFadeToBlack = shouldFade;
            }

            void ScreenFadeEffectController::Update(float dt)
            {
                const float transitionTarget = m_shouldFadeToBlack ? 0.f : 1.f;

                float delta = 0.f;
                if (m_transitionParameter < transitionTarget)
                {
                    delta = dt;
                }
                else if (m_transitionParameter > transitionTarget)
                {
                    delta = -dt;
                }

                m_transitionParameter += delta / m_transitionTimeSeconds;
                m_transitionParameter = Eegeo::Math::Clamp01(m_transitionParameter);

                m_screenTransitionModel.SetVisibilityParam(m_transitionParameter);

                if ((m_currentVisibiltyState == VisibilityState::FullyFaded && m_transitionParameter > 0.f) ||
                    (m_currentVisibiltyState == VisibilityState::FullyVisible && m_transitionParameter < 1.f))
                {
                    m_currentVisibiltyState = VisibilityState::Transitioning;
                    NotifyStateChange();
                }

                if (m_currentVisibiltyState == VisibilityState::Transitioning)
                {
                    if (m_transitionParameter >= 1.f)
                    {
                        m_currentVisibiltyState = VisibilityState::FullyVisible;
                        NotifyStateChange();
                    }
                    else if (m_transitionParameter <= 0.f)
                    {
                        m_currentVisibiltyState = VisibilityState::FullyFaded;
                        NotifyStateChange();
                    }
                }
            }

            void ScreenFadeEffectController::NotifyStateChange()
            {
                m_visibilityChangedCallbacks.ExecuteCallbacks(m_currentVisibiltyState);
            }
            
            void ScreenFadeEffectController::RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback)
            {
                m_visibilityChangedCallbacks.AddCallback(callback);
            }
            
            void ScreenFadeEffectController::UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback)
            {
                m_visibilityChangedCallbacks.RemoveCallback(callback);
            }
        }
    }
}
