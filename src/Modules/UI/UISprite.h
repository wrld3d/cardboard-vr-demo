//
//  UISprite.hpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#ifndef UISprite_h
#define UISprite_h

#include "UIBaseItem.h"
#include "UIQuad/UIQuad.h"

namespace Eegeo
{
    namespace UI
    {
        class UISprite : public UIBaseItem, private NonCopyable
        {
        
        private:
            
            UIQuad* m_Quad;
            
            Eegeo::v2 m_SpriteGridSize;
            int m_SpriteId;
            
            Eegeo::v2 m_MinUV;
            Eegeo::v2 m_MaxUV;
            
            void UpdateUVs();
            
        public:
            
            UISprite(  UIQuad* quad
                     , Eegeo::v2 spriteGridSize = Eegeo::v2::One()
                     , int spriteId = 1
                     , Eegeo::dv3 ecefPosition = Eegeo::dv3::Zero()
                     , Eegeo::v2 size = Eegeo::v2::One()
                     , Eegeo::v3 scale = Eegeo::v3::One()
                     , Eegeo::v4 color = Eegeo::v4::One());
            
            virtual ~UISprite();
            
            void SetSpriteId(int spriteId);
            int getSpriteId();
            
            virtual void Update();
            
            
        };
        
    }
}

#endif /* UISprite_h */
