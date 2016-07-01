// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "UISprite.h"
#include "UIQuad/UIQuad.h"
#include "IUICameraProvider.h"
#include "UIInteraction/IUIInteractableItem.h"
#include "UIAnimatedSprite.h"

namespace Eegeo
{
    namespace UI
    {
        class UIProgressButton : public Eegeo::UI::IUIInteractableItem
        {
        private:
            UISprite* m_pSprite;
            UI::UIAnimatedSprite* m_pGazeProgress;
            Eegeo::Helpers::ICallback0& m_onClickedEvent;
            float m_radius;
            
        public:
            UIProgressButton(IUIRenderableFilter& uiRenderableFilter
                          , Eegeo::UI::IUIQuadFactory& quadFactory
                          , const std::string& assetPath
                          , const std::string& progressTileMapPath
                          , Eegeo::Helpers::ICallback0& onClickedEvent
                          , const Eegeo::v2& size = Eegeo::v2::One()
                          , const Eegeo::dv3& ecefPosition = Eegeo::dv3::Zero()
                          , const Eegeo::v3& scale = Eegeo::v3::One()
                          , const Eegeo::v4& color = Eegeo::v4::One()
                          , const Eegeo::v2& uvMin = Eegeo::v2::One()
                          , const Eegeo::v2& uvMax = Eegeo::v2::One()
                          );
            
            virtual ~UIProgressButton();
            
            void Init(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter, const std::string& assetPath, const std::string& progressTileMapPath, const Eegeo::v2& size, const Eegeo::dv3& ecefPosition, const Eegeo::v3& scale, const Eegeo::v4& color, const Eegeo::v2& uvMin, const Eegeo::v2& uvMax);
            virtual void Update(float dt);
            virtual bool IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider);
            
            virtual void OnItemClicked();
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
        };
        
    }
}


