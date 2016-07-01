// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

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
            
            UIQuad* m_pQuad;
            Eegeo::v2 m_Size;
            
        public:
            
            UISprite(IUIRenderableFilter& uiRenderableFilter
                     , UIQuad* pQuad
                     , const Eegeo::v2& size = Eegeo::v2::One()
                     , const Eegeo::dv3& ecefPosition = Eegeo::dv3::Zero()
                     , const Eegeo::v3& scale = Eegeo::v3::One()
                     , const Eegeo::v4& color = Eegeo::v4::One());
            
            virtual ~UISprite();
            
            virtual void Update(float dt);
            
            void SetEcefPosition(const Eegeo::dv3& position);
            Eegeo::dv3 GetEcefPosition();
            
            void SetSize(const Eegeo::v2& size);
            Eegeo::v2 GetSize();
            
            void SetColor(const Eegeo::v4& color);
            Eegeo::v4 GetColor();
            
            void SetScale(const Eegeo::v3& scale);
            Eegeo::v3 GetScale();
            
            bool GetItemShouldRender(){ return m_pQuad->GetItemShouldRender(); }
            void SetItemShouldRender(bool shouldRender){ m_pQuad->SetItemShouldRender(shouldRender); }
            
        };
        
    }
}
