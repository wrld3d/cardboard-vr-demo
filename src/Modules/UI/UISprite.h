//
//  UISprite.hpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#ifndef UISprite_h
#define UISprite_h

#include "UIQuad/UIQuad.h"
#include "IUIRenderableFilter.h"

namespace Eegeo
{
    namespace UI
    {
        class UISprite 
        {
        
        private:
            IUIRenderableFilter& m_UIRenderableFilter;
            Eegeo::dv3 m_EcefPosition;
            Eegeo::v4 m_Color;
            Eegeo::v3 m_Scale;
            Eegeo::v2 m_Size;
            
            
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
            
            void SetEcefPosition(Eegeo::dv3 position);
            const Eegeo::dv3& GetEcefPosition();
            
            void SetSize(Eegeo::v2 size);
            const Eegeo::v2& GetSize();
            
            void SetColor(Eegeo::v4 color);
            const Eegeo::v4& GetColor();
            
            void SetScale(Eegeo::v3 scale);
            const Eegeo::v3& GetScale();
            
        };
        
    }
}

#endif /* UISprite_h */
