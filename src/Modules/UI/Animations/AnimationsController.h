// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <vector>
#include "Types.h"
#include "IAnimation.h"
#include "IAnimationObserver.h"
#include "IAnimationsObservable.h"


namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class AnimationsController : protected Eegeo::NonCopyable, public IAnimationsObservable
            {
            public:
                AnimationsController();
                
                ~AnimationsController();
                
                void Update(float deltaTime);
                
                virtual void AddAnimation(IAnimation* pAnimationToAdd);
                virtual void RemoveAnimation(IAnimation* pAnimationToRemove);
                virtual void RemoveAnimationsForTag(int tag);
                virtual void ClearAllAnimations();
                
                
            private:
                
                typedef std::vector<IAnimation*> TAnimation;
                TAnimation m_animations;
                
            };
        }
    }
}
