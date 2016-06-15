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
#include "IUIRenderableFilter.h"

namespace Eegeo
{
    namespace UI
    {
        class UISprite : public UIBaseItem
        {
        
        private:
            IUIRenderableFilter& m_UIRenderableFilter;
            UIQuad* m_Quad;
            
            Eegeo::v2 m_SpriteGridSize;
            int m_SpriteId;
            
            Eegeo::v2 m_MinUV;
            Eegeo::v2 m_MaxUV;
            
            void UpdateUVs();
            
        public:
            
            UISprite(IUIRenderableFilter& p_UIRenderableFilter
                     , UIQuad* quad
                     , Eegeo::v2 size = Eegeo::v2::One()
                     , Eegeo::dv3 ecefPosition = Eegeo::dv3::Zero()
                     , Eegeo::v3 scale = Eegeo::v3::One()
                     , Eegeo::v4 color = Eegeo::v4::One()
                     , int spriteId = 0
                     , Eegeo::v2 spriteGridSize = Eegeo::v2::One());
            
            virtual ~UISprite();
            
            int GetSpriteId();
            void SetSpriteId(int spriteId);
            
            int GetMaxSpriteId();
            void SetPreviousSprite();
            void SetNextSprite();
            
            virtual void Update(float dt);
            
            
        };
        
    }
}

#endif /* UISprite_h */
