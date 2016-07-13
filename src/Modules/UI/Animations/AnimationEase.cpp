// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AnimationEase.h"
#include "MathFunc.h"

namespace Eegeo
{
    namespace UI
    {
        float AnimationEase::Linear(float start, float end, float val)
        {
            return Eegeo::Math::Lerp<float>(start, end, val);
        }
        
        float AnimationEase::EaseInQuad(float start, float end, float val)
        {
            end -= start;
            return end * val * val + start;
        }
        
        float AnimationEase::EaseOutQuad(float start, float end, float val)
        {
            end -= start;
            return -end * val * (val - 2) + start;
        }
        
        float AnimationEase::EaseInOutQuad(float start, float end, float val)
        {
            val /= .5f;
            end -= start;
            
            if (val < 1)
                return end / 2 * val * val + start;
            
            val--;
            
            return -end / 2 * (val * (val - 2) - 1) + start;
        }
        
        float AnimationEase::EaseInCubic(float start, float end, float val)
        {
            end -= start;
            return end * val * val * val + start;
        }
        
        float AnimationEase::EaseOutCubic(float start, float end, float val)
        {
            val--;
            end -= start;
            return end * (val * val * val + 1) + start;
        }
        
        float AnimationEase::EaseInOutCubic(float start, float end, float val)
        {
            val /= .5f;
            end -= start;
            
            if (val < 1)
                return end / 2 * val * val * val + start;
            
            val -= 2;
            
            return end / 2 * (val * val * val + 2) + start;
        }
        
        float AnimationEase::EaseInQuart(float start, float end, float val)
        {
            end -= start;
            return end * val * val * val * val + start;
        }
        
        float AnimationEase::EaseOutQuart(float start, float end, float val)
        {
            val--;
            end -= start;
            return -end * (val * val * val * val - 1) + start;
        }
        
        float AnimationEase::EaseInOutQuart(float start, float end, float val)
        {
            val /= .5f;
            end -= start;
            
            if (val < 1)
                return end / 2 * val * val * val * val + start;
            
            val -= 2;
            
            return -end / 2 * (val * val * val * val - 2) + start;
        }
        
        float AnimationEase::EaseInQuint(float start, float end, float val)
        {
            end -= start;
            return end * val * val * val * val * val + start;
        }
        
        float AnimationEase::EaseOutQuint(float start, float end, float val)
        {
            val--;
            end -= start;
            return end * (val * val * val * val * val + 1) + start;
        }
        
        float AnimationEase::EaseInOutQuint(float start, float end, float val)
        {
            val /= .5f;
            end -= start;
            
            if (val < 1)
                return end / 2 * val * val * val * val * val + start;
            
            val -= 2;
            
            return end / 2 * (val * val * val * val * val + 2) + start;
        }
        
        float AnimationEase::EaseInSine(float start, float end, float val)
        {
            end -= start;
            return -end * Eegeo::Math::Cos(val / 1 * (Eegeo::Math::kPI / 2)) + end + start;
        }
        
        float AnimationEase::EaseOutSine(float start, float end, float val)
        {
            end -= start;
            return end * Eegeo::Math::Sin(val / 1 * (Eegeo::Math::kPI / 2)) + start;
        }
        
        float AnimationEase::EaseInOutSine(float start, float end, float val)
        {
            end -= start;
            return -end / 2 * (Eegeo::Math::Cos(Eegeo::Math::kPI * val / 1) - 1) + start;
        }
        
        float AnimationEase::EaseInExpo(float start, float end, float val)
        {
            end -= start;
            return end * Eegeo::Math::Pow(2, 10 * (val / 1 - 1)) + start;
        }
        
        float AnimationEase::EaseOutExpo(float start, float end, float val)
        {
            end -= start;
            return end * (-Eegeo::Math::Pow(2, -10 * val / 1) + 1) + start;
        }
        
        float AnimationEase::EaseInOutExpo(float start, float end, float val)
        {
            val /= .5f;
            end -= start;
            
            if (val < 1)
                return end / 2 * Eegeo::Math::Pow(2, 10 * (val - 1)) + start;
            
            val--;
            
            return end / 2 * (-Eegeo::Math::Pow(2, -10 * val) + 2) + start;
        }
        
        float AnimationEase::EaseInCirc(float start, float end, float val)
        {
            end -= start;
            return -end * (Eegeo::Math::Sqrtf(1 - val * val) - 1) + start;
        }
        
        float AnimationEase::EaseOutCirc(float start, float end, float val)
        {
            val--;
            end -= start;
            return end * Eegeo::Math::Sqrtf(1 - val * val) + start;
        }
        
        float AnimationEase::EaseInOutCirc(float start, float end, float val)
        {
            val /= .5f;
            end -= start;
            if (val < 1) return -end / 2 * (Eegeo::Math::Sqrtf(1 - val * val) - 1) + start;
            val -= 2;
            return end / 2 * (Eegeo::Math::Sqrtf(1 - val * val) + 1) + start;
        }
        
        float AnimationEase::EaseOutBounce(float start, float end, float val)
        {
            val /= 1.0f;
            end -= start;
            if (val < (1 / 2.75f))
            {
                return end * (7.5625f * val * val) + start;
            }else if (val < (2 / 2.75f))
            {
                val -= (1.5f / 2.75f);
                return end * (7.5625f * (val) * val + .75f) + start;
            }else if (val < (2.5 / 2.75))
            {
                val -= (2.25f / 2.75f);
                return end * (7.5625f * (val) * val + .9375f) + start;
            }else{
                val -= (2.625f / 2.75f);
                return end * (7.5625f * (val) * val + .984375f) + start;
            }
        }
        
        float AnimationEase::EaseInBounce(float start, float end, float val)
        {
            end -= start;
            float d = 1.0f;
            return end - EaseOutBounce(0, end, d-val) + start;
        }
        
        float AnimationEase::EaseInOutBounce(float start, float end, float val)
        {
            end -= start;
            float d= 1.0f;
            if (val < d/2) return EaseInBounce(0, end, val*2) * 0.5f + start;
            else return EaseOutBounce(0, end, val*2-d) * 0.5f + end*0.5f + start;
        }
        
    }
}
