// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace Eegeo
{
    namespace UI
    {
        class AnimationEase
        {
        public:
           
            static float Linear(float start, float end, float val);
            
            static float EaseInQuad(float start, float end, float val);
            
            static float EaseOutQuad(float start, float end, float val);
            
            static float EaseInOutQuad(float start, float end, float val);
            
            static float EaseInCubic(float start, float end, float val);
            
            static float EaseOutCubic(float start, float end, float val);
            
            static float EaseInOutCubic(float start, float end, float val);
            
            static float EaseInQuart(float start, float end, float val);
            
            static float EaseOutQuart(float start, float end, float val);
            
            static float EaseInOutQuart(float start, float end, float val);
            
            static float EaseInQuint(float start, float end, float val);
            
            static float EaseOutQuint(float start, float end, float val);
            
            static float EaseInOutQuint(float start, float end, float val);
            
            static float EaseInSine(float start, float end, float val);
            
            static float EaseOutSine(float start, float end, float val);
            
            static float EaseInOutSine(float start, float end, float val);
            
            static float EaseInExpo(float start, float end, float val);
            
            static float EaseOutExpo(float start, float end, float val);
            
            static float EaseInOutExpo(float start, float end, float val);
            
            static float EaseInCirc(float start, float end, float val);
            
            static float EaseOutCirc(float start, float end, float val);
            
            static float EaseInOutCirc(float start, float end, float val);
            
            static float EaseOutBounce(float start, float end, float val);
            
            static float EaseInBounce(float start, float end, float val);
            
            static float EaseInOutBounce(float start, float end, float val);
           
        };
        
    }
}
