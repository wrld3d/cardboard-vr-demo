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
                
            }
            
            void AnimationsController::Update(float deltaTime)
            {
                TAnimation animationsTrash;
                for(TAnimation::iterator animIt = m_animations.begin(); animIt != m_animations.end(); ++animIt)
                {
                    (*animIt)->Update(deltaTime);
                    if((*animIt)->IsComplete())
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
                    
                    animationsTrash.erase(animationsTrash.begin());
                    Eegeo_DELETE animation;
                }
            }
            
            
            void AnimationsController::ClearAllAnimations()
            {
                for(TAnimation::iterator animIt = m_animations.begin(); animIt != m_animations.end(); ++animIt)
                {
                    Eegeo_DELETE (*animIt);
                }
                m_animations.clear();
            }
            
            void AnimationsController::RemoveAnimationsForTag(int tag)
            {
                
                TAnimation animationsTrash;
                for(TAnimation::iterator animIt = m_animations.begin(); animIt != m_animations.end(); ++animIt)
                {
                    if ((*animIt)->GetTag()==tag)
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
                    
                    
                    animationsTrash.erase(animationsTrash.begin());
                    Eegeo_DELETE animation;
                }
            }
            
            
            void AnimationsController::AddAnimation(IAnimation* pAnimationToAdd)
            {
                if(pAnimationToAdd!=NULL)
                {
                    m_animations.push_back(pAnimationToAdd);
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
            
        }
    }
}
