// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AnimationsController.h"
#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            
            AnimationsController::AnimationsController()
            {
            }
            
            
            AnimationsController::~AnimationsController()
            {
            }
            
            void AnimationsController::Update(float deltaTime)
            {
            }
            
            void AnimationsController::AddAnimationsObserver(IAnimationObserver* pObserverToAdd)
            {
                if(pObserverToAdd!=NULL)
                {
                    m_animationObservables.push_back(pObserverToAdd);
                }
            }
            
            void AnimationsController::RemoveAnimationsObserver(IAnimationObserver* pObserverToRemove)
            {
                
                if(pObserverToRemove!=NULL)
                {
                    std::vector<IAnimationObserver*>::iterator position = std::find(m_animationObservables.begin(), m_animationObservables.end(),pObserverToRemove);
                    if (position != m_animationObservables.end())
                    {
                        m_animationObservables.erase(position);
                    }
                }
            }
            
            
        }
    }
}
