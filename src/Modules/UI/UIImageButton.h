//
//  UIImageButton.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include "ICallback.h"
#include "UIQuad/UIQuad.h"
#include "UIInteraction/IUIInteractableItem.h"

namespace Eegeo
{
    namespace UI
    {
        class UIImageButton : public Eegeo::UI::IUIInteractableItem
        {
        private:
            UIQuad* m_ButtonImage;
            Eegeo::Helpers::ICallback0& m_OnClickedEvent;
            float m_Radius;
            
        public:
            UIImageButton(UIQuad* quad,
                          const Eegeo::v2& p_Dimension,
                          const Eegeo::dv3& ecefPosition,
                          Eegeo::Helpers::ICallback0& onClickedEvent
                          );
            
            virtual ~UIImageButton();
            inline void SetEcefPosition(const Eegeo::dv3& ecefPosition){ m_ButtonImage->SetEcefPosition(ecefPosition); }
            inline const dv3& GetEcefPosition() const { return m_ButtonImage->GetEcefPosition(); }
            inline Eegeo::v3 GetScale() { return m_ButtonImage->GetScale(); }
            inline void SetScale(Eegeo::v3 p_scale) {  m_ButtonImage->SetScale(p_scale); }
            inline void SetColor(const Eegeo::v4& color) { m_ButtonImage->SetColor(color); }
            
            // UIInteractableItem interface
            virtual void OnItemClicked();
            virtual void OnFocusGained();
            virtual void OnFocusLost();
            
            virtual void Update(float dt);
            
            const virtual float GetItemRadius() { return m_Radius; }
            const virtual Eegeo::dv3& GetItemEcefPosition() { return m_ButtonImage->GetEcefPosition(); }
        };
        
    }
}


