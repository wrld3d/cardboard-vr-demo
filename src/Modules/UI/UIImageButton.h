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
            
            Eegeo::Helpers::ICallback0& m_OnClickedEvent;
            float m_Radius;
            
        public:
            UIImageButton(UIQuad* quad
                          , Eegeo::Helpers::ICallback0& onClickedEvent
                          , Eegeo::v2 size = Eegeo::v2::One()
                          , Eegeo::dv3 ecefPosition = Eegeo::dv3::Zero()
                          , Eegeo::v3 scale = Eegeo::v3::One()
                          , Eegeo::v4 color = Eegeo::v4::One()
                          , int spriteId = 0
                          , Eegeo::v2 spriteGridSize = Eegeo::v2::One()
                          );
            
            virtual ~UIImageButton();
            
            virtual bool IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider);
            
            virtual void OnItemClicked();
            virtual void OnFocusGained();
            virtual void OnFocusLost();
            
            const virtual float GetItemRadius() { return m_Radius; }
        };
        
    }
}


