// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Dv3PropertyAnimation.h"
#include "IDv3Animateable.h"

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            
            Dv3PropertyAnimation::Dv3PropertyAnimation(IDv3Animateable& dv3Animateable,
                                                       Eegeo::dv3& startValue,
                                                       Eegeo::dv3& endValue,
                                                       float time)
            :m_dv3Animateable(dv3Animateable)
            ,m_startValue(startValue)
            ,m_endValue(endValue)
            ,m_time(time)
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
                return (int)(m_timePassed/m_time);
            }
            
            void Dv3PropertyAnimation::Update(float dt)
            {
                m_timePassed+=dt;
                m_timePassed = m_time;
                Eegeo::dv3 delta = m_direction*getProgress();
                m_dv3Animateable.onDv3Updated(delta);
            }
            
        }
    }
}
