//
//  UIImageButton.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include "UIImageButtonClickedCallback.h"
#include "UIQuad.h"
#include "IUIInteractableItem.h"

namespace Eegeo
{
    namespace UI
    {
        class UIImageButton : public Eegeo::UI::IUIInteractableItem
        {
        private:
            UIQuad* m_ButtonImage;
            IUIImageButtonClickedCallback& m_OnClickedEvent;
            float m_Radius;
            
        public:
            UIImageButton(Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                          , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                          , const std::string& fileName
                          , const Eegeo::dv3& p_ecefPosition
                          , const Eegeo::v2& p_Dimension
                          , IUIImageButtonClickedCallback& p_OnClickedEvent
                          , const Eegeo::v2& p_uvMin = Eegeo::v2::Zero()
                          , const Eegeo::v2& p_uvMax = Eegeo::v2::One()
                          , const Eegeo::v4& p_initialColor = Eegeo::v4::One()
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


