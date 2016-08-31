// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Animations.h"

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class IAnimation
            {
                
            private:
                int m_tag;
                IAnimationObserver* m_pAnimationObserver;
                
            public:
                
                void SetAnimationObserver(IAnimationObserver* animationObserver){m_pAnimationObserver = animationObserver;}
                IAnimationObserver* GetAnimationObserver(){return m_pAnimationObserver;}
                
                void SetTag(int tag){m_tag = tag;}
                int GetTag(){return m_tag;}
                
                virtual void Update(float dt) = 0;
                virtual bool IsComplete() = 0;
                virtual float GetProgress() = 0;
                
                virtual ~IAnimation(){}
                
            };
        }
    }
}