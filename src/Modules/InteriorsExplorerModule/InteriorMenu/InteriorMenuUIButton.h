// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "InteriorMenuItem.h"
#include "../../UI/UISprite.h"
#include "../../UI/UIQuad/UIQuad.h"
#include "../../UI/IUICameraProvider.h"
#include "../../UI/UIInteraction/IUIInteractableItem.h"
#include "../../UI/UIAnimatedSprite.h"
#include "../../UI/UIProgressBarConfig.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        class InteriorMenuUIButton : public Eegeo::UI::IUIInteractableItem
        {
        protected:
            Eegeo::UI::UISprite* m_pSprite;
            Eegeo::UI::UIAnimatedSprite* m_pGazeProgress;
            
            float m_radius;
            bool m_isFocused;
            bool m_isItemSelected;
            Eegeo::v3 m_scale;
            
        public:
            InteriorMenuUIButton(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                          , Eegeo::UI::IUIQuadFactory& quadFactory
                          , const std::string& assetPath
                          , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                          , const Eegeo::v2& size = Eegeo::v2::One()
                          , const Eegeo::dv3& ecefPosition = Eegeo::dv3::Zero()
                          , const Eegeo::v3& scale = Eegeo::v3::One()
                          , const Eegeo::v4& color = Eegeo::v4::One()
                          , const Eegeo::v2& uvMin = Eegeo::v2::One()
                          , const Eegeo::v2& uvMax = Eegeo::v2::One()
                          );
            
            virtual ~InteriorMenuUIButton();
            
            void Init(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter, const std::string& assetPath, const Eegeo::UI::UIProgressBarConfig& progressBarConfig, const Eegeo::v2& size, const Eegeo::dv3& ecefPosition, const Eegeo::v3& scale, const Eegeo::v4& color, const Eegeo::v2& uvMin, const Eegeo::v2& uvMax);
            virtual void Update(float dt);
            
            virtual void OnFocusGained();
            virtual void OnFocusLost();
            
            const virtual float GetItemRadius() { return m_radius; }
            
            void SetEcefPosition(const Eegeo::dv3& position);
            Eegeo::dv3 GetEcefPosition();
            
            void SetSize(const Eegeo::v2& size);
            Eegeo::v2 GetSize();
            
            void SetColor(const Eegeo::v4& color);
            Eegeo::v4 GetColor();
            
            void SetScale(const Eegeo::v3& scale);
            Eegeo::v3 GetScale();
            
            void SetItemSelected();
            void SetItemUnselected();
            
            bool GetItemShouldRender(){ return m_pSprite->GetItemShouldRender(); }
            void SetItemShouldRender(bool shouldRender){ m_pSprite->SetItemShouldRender(shouldRender); }
            
        };
        
    }
}


