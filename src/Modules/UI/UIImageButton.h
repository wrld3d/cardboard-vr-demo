//
//  UIImageButton.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include "ICallback.h"
#include "UISprite.h"
#include "UIQuad/UIQuad.h"
#include "IUICameraProvider.h"
#include "UIInteraction/IUIInteractableItem.h"

namespace Eegeo
{
    namespace UI
    {
        class UIImageButton : public Eegeo::UI::IUIInteractableItem, public UISprite
        {
        private:
            
            Eegeo::Helpers::ICallback0& m_onClickedEvent;
            float m_radius;
            
        public:
            UIImageButton(IUIRenderableFilter& uiRenderableFilter
                          , UIQuad* pQuad
                          , Eegeo::Helpers::ICallback0& onClickedEvent
                          , const Eegeo::v2& size = Eegeo::v2::One()
                          , const Eegeo::dv3& ecefPosition = Eegeo::dv3::Zero()
                          , const Eegeo::v3& scale = Eegeo::v3::One()
                          , const Eegeo::v4& color = Eegeo::v4::One()
                          );
            
            virtual ~UIImageButton();
            
            virtual bool IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider);
            
            virtual void OnItemClicked();
            virtual void OnFocusGained();
            virtual void OnFocusLost();
            
            const virtual float GetItemRadius() { return m_radius; }
        };
        
    }
}


