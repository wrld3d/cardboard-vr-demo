// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IAnimation.h"
#include "IAnimationObserver.h"
#include "IAnimationObservable.h"


namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class AnimationsController : protected Eegeo::NonCopyable, public IAnimationObservable
            {
            public:
                AnimationsController();
                
                ~AnimationsController();
                
                void Update(float deltaTime);
                
                virtual void AddAnimationsObserver(IAnimationObserver* pObserverToAdd);
                virtual void RemoveAnimationsObserver(IAnimationObserver* pObserverToRemove);
                
                
            private:
                
                std::vector<IAnimationObserver*> m_animationObservables;
                std::vector<IAnimation*> m_animations;
                
            };
        }
    }
}
