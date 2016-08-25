// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "IVRDistortionTransitionModel.h"
#include "ICallback.h"

namespace Examples
{
    namespace ScreenFadeEffect
    {
        namespace SdkModel
        {
            class IScreenFadeEffectController
            {
            public:

                enum VisibilityState
                {
                    FullyFaded,
                    Transitioning,
                    FullyVisible
                };

                virtual ~IScreenFadeEffectController(){}

                virtual void SetShouldFadeToBlack(bool shouldFade) = 0;
                virtual bool GetShouldFadeToBlack() const = 0;

                virtual void RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback) = 0;
                virtual void UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback1<VisibilityState&>& callback) = 0;

            };
        }
    }
}
