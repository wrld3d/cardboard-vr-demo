// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AnimationsController.h"
#include "IAnimation.h"
#include "IAnimationObserver.h"
#include "Logger.h"
#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            
            AnimationsController::AnimationsController(){}
            
            AnimationsController::~AnimationsController()
            {
                m_animationObservers.clear();
                for(TAnimation::iterator animIt = m_animations.begin(); animIt != m_animations.end(); ++animIt)
                {
                    Eegeo_DELETE (*animIt);
                }
                m_animations.clear();
                
            }
            
            void AnimationsController::Update(float deltaTime)
            {
                TAnimation animationsTrash;
                for(TAnimation::iterator animIt = m_animations.begin(); animIt != m_animations.end(); ++animIt)
                {
                    (*animIt)->Update(deltaTime);
                    if((*animIt)->getProgress()<(*animIt)->getMaxProgress())
                    {
                        for(TAnimationObserver::iterator observerIt = m_animationObservers.begin(); observerIt != m_animationObservers.end(); ++observerIt)
                        {
                            (*observerIt)->OnAnimationProgress(**animIt);
                        }
                    }
                    else
                    {
                        animationsTrash.push_back(*animIt);
                    }
                }
                
                while(animationsTrash.size()>0)
                {
                    IAnimation* animation = *animationsTrash.begin();
                    TAnimation::iterator position = std::find(m_animations.begin(), m_animations.end(), animation);
                    
                    if (position != m_animations.end())
                    {
                        m_animations.erase(position);
                    }
                    
                    for(TAnimationObserver::iterator observerIt = m_animationObservers.begin(); observerIt != m_animationObservers.end(); ++observerIt)
                    {
                        (*observerIt)->OnAnimationRemoved(*animation);
                    }
                    
                    animationsTrash.erase(animationsTrash.begin());
                    Eegeo_DELETE animation;
                }
            }
            
            void AnimationsController::AddAnimation(IAnimation* pAnimationToAdd)
            {
                if(pAnimationToAdd!=NULL)
                {
                    m_animations.push_back(pAnimationToAdd);
                    for(TAnimationObserver::iterator observerIt = m_animationObservers.begin(); observerIt != m_animationObservers.end(); ++observerIt)
                    {
                         (*observerIt)->OnAnimationAdded(*pAnimationToAdd);
                    }
                }
            }
            
            void AnimationsController::RemoveAnimation(IAnimation* pAnimationToRemove)
            {
                if(pAnimationToRemove!=NULL)
                {
                    TAnimation::iterator position = std::find(m_animations.begin(), m_animations.end(),pAnimationToRemove);
                    if (position != m_animations.end())
                    {
                        Eegeo_DELETE *position;
                        m_animations.erase(position);
                    }
                }
            }
            
            void AnimationsController::AddAnimationsObserver(IAnimationObserver* pObserverToAdd)
            {
                if(pObserverToAdd!=NULL)
                {
                    m_animationObservers.push_back(pObserverToAdd);
                }
            }
            
            void AnimationsController::RemoveAnimationsObserver(IAnimationObserver* pObserverToRemove)
            {
                
                if(pObserverToRemove!=NULL)
                {
                    TAnimationObserver::iterator position = std::find(m_animationObservers.begin(), m_animationObservers.end(),pObserverToRemove);
                    if (position != m_animationObservers.end())
                    {
                        m_animationObservers.erase(position);
                    }
                }
            }
            
            
        }
    }
}
