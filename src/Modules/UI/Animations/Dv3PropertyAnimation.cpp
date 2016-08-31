// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Dv3PropertyAnimation.h"
#include "IAnimationObserver.h"
#include "IDv3Animateable.h"
#include "AnimationEase.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            
            Dv3PropertyAnimation::Dv3PropertyAnimation(IDv3Animateable& dv3Animateable,
                                                       IAnimationObserver* animationObserver,
                                                       const Eegeo::dv3& startValue,
                                                       const Eegeo::dv3& endValue,
                                                       float time,
                                                       float (*pEaseFunction)(float, float, float))
            :m_dv3Animateable(dv3Animateable)
            ,m_animationObserver(animationObserver)
            ,m_startValue(startValue)
            ,m_endValue(endValue)
            ,m_time(time)
            ,m_pEaseFunction(pEaseFunction)
            ,m_timePassed(0)
            {
                if(m_animationObserver!=NULL)
                {
                    m_animationObserver->OnAnimationAdded(*this);
                }
                
                m_direction = (m_endValue - m_startValue).Norm();
            }
            
            Dv3PropertyAnimation::~Dv3PropertyAnimation()
            {
                if(m_animationObserver!=NULL)
                {
                    m_animationObserver->OnAnimationRemoved(*this);
                }
            }
            
            bool Dv3PropertyAnimation::IsComplete()
            {
                return m_timePassed>=m_time;
            }
            
            float Dv3PropertyAnimation::GetProgress()
            {
                return (m_timePassed/m_time);
            }
            
            void Dv3PropertyAnimation::Update(float dt)
            {
                m_timePassed+=dt;
                Eegeo::dv3 pos = Eegeo::dv3::Lerp(m_startValue, m_endValue, m_pEaseFunction(0, 1, GetProgress()));
                m_dv3Animateable.OnDv3Updated(pos);
                
                if(m_animationObserver!=NULL)
                {
                    m_animationObserver->OnAnimationProgress(*this);
                }
            }
            
        }
    }
}
