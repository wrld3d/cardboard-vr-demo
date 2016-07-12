// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once


#include "IAnimationObserver.h"

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class IAnimationObservable
            {
            public:
                virtual void AddAnimationsObserver(IAnimationObserver* pObserverToAdd) = 0;
                virtual void RemoveAnimationsObserver(IAnimationObserver* pObserverToRemove) = 0;
                virtual ~IAnimationObservable() {};
            };
        }
    }
}