//
//  UIAnimatedQuad.h
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UISprite.h"
#include "ICallback.h"
#include "UIQuad/UIQuad.h"

#ifndef UIAnimatedSprite_h
#define UIAnimatedSprite_h

namespace Eegeo
{
    namespace UI
    {
        class UIAnimatedSprite : public UISprite
        {
            
        private:
            
            float m_TimeElapsed;
            float m_FrameRate;
            
            float m_Radius;
            
            UIQuad* m_Quad;
            
            void Init();
            
        public:
            
            UIAnimatedSprite( UIQuad* quad
                             , float frameRate
                             , Eegeo::v2 spriteGridSize = Eegeo::v2::One()
                             , int spriteId = 0
                             , Eegeo::v2 size = Eegeo::v2::One()
                             , Eegeo::dv3 ecefPosition = Eegeo::dv3::Zero()
                             , Eegeo::v3 scale = Eegeo::v3::One()
                             , Eegeo::v4 color = Eegeo::v4::One()
                             );
        
            
            virtual ~UIAnimatedSprite();
            
            void Reset();
            
            virtual void Update(float dt);
            
            const virtual float GetItemRadius() { return m_Radius; }
            
        };
        
    }
}




#endif /* UIAnimatedQuad_h */
