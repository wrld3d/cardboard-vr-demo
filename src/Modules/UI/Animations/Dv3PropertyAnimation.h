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
                                     const Eegeo::dv3& startValue,
                                     const Eegeo::dv3& endValue,
                                     float time,
                                     float (*pEaseFunction)(float, float, float));
                ~Dv3PropertyAnimation();
                virtual void Update(float dt);
                
                virtual bool isComplete();
                virtual float getProgress();
                virtual float getMaxProgress();
                
            private:
                IDv3Animateable& m_dv3Animateable;
                const Eegeo::dv3 m_startValue;
                const Eegeo::dv3 m_endValue;
                Eegeo::dv3 m_direction;
                float m_time;
                
                Eegeo::dv3 m_currentValue;
                float m_timePassed;
                
                float (*m_pEaseFunction)(float start, float end, float val);
                
            };
        }
    }
}