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
                virtual void AddAnimation(IAnimation* pAnimationToAdd);
                virtual void RemoveAnimation(IAnimation* pAnimationToRemove);
                
                
            private:
                
                typedef std::vector<IAnimationObserver*> TAnimationObserver;
                TAnimationObserver m_animationObservers;
                
                typedef std::vector<IAnimation*> TAnimation;
                TAnimation m_animations;
                
            };
        }
    }
}
