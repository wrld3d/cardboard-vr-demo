// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Dv3PropertyAnimation.h"
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
                                                       const Eegeo::dv3& startValue,
                                                       const Eegeo::dv3& endValue,
                                                       float time,
                                                       float (*pEaseFunction)(float, float, float))
            :m_dv3Animateable(dv3Animateable)
            ,m_startValue(startValue)
            ,m_endValue(endValue)
            ,m_time(time)
            ,m_pEaseFunction(pEaseFunction)
            ,m_timePassed(0)
            {
                m_direction = (m_endValue - m_startValue).Norm();
            }
            
            Dv3PropertyAnimation::~Dv3PropertyAnimation() {}
            
            bool Dv3PropertyAnimation::isComplete()
            {
                return m_timePassed>=m_time;
            }
            
            float Dv3PropertyAnimation::getProgress()
            {
                return (m_timePassed/m_time)*getMaxProgress();
            }
            
            float Dv3PropertyAnimation::getMaxProgress()
            {
                return 1.f;
            }
            
            void Dv3PropertyAnimation::Update(float dt)
            {
                m_timePassed+=dt;
                Eegeo::dv3 pos = Eegeo::dv3::Lerp(m_startValue, m_endValue, m_pEaseFunction(0, 1, (getProgress()/getMaxProgress())));
                m_dv3Animateable.OnDv3Updated(pos);
            }
            
        }
    }
}
