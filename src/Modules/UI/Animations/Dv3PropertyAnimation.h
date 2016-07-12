// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "IAnimation.h"
#include "IDv3Animateable.h"

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class Dv3PropertyAnimation: public NonCopyable, public IAnimation
            {
                
            public:
                Dv3PropertyAnimation(IDv3Animateable& dv3Animateable,
                                     Eegeo::dv3& startValue,
                                     Eegeo::dv3& endValue,
                                     float time);
                ~Dv3PropertyAnimation();
                virtual void Update(float dt);
                
                bool isComplete();
                float getProgress();
                
            private:
                IDv3Animateable& m_dv3Animateable;
                Eegeo::dv3& m_startValue;
                Eegeo::dv3& m_endValue;
                Eegeo::dv3 m_direction;
                float m_time;
                
                Eegeo::dv3 m_currentValue;
                float m_timePassed;
                
            };
        }
    }
}