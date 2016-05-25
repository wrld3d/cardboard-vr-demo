//
//  UIAnimatedQuad.h
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIQuad.h"
#include "IUIInteractableItem.h"
#include "UIImageButtonClickedCallback.h"

#ifndef UIAnimatedSprite_h
#define UIAnimatedSprite_h

namespace Eegeo
{
    namespace UI
    {
        class UIAnimatedSprite : public Eegeo::UI::IUIInteractableItem
        {
            
        private:
            
            float m_TimeElapsed;
            float m_FrameRate;
            
            int m_CurrentFrameNumber;
            float m_Radius;
            
            Eegeo::v2& m_FramesGridSize;
            
            UIQuad* m_Quad;
            IUIImageButtonClickedCallback& m_OnClickedEvent;
            
            Eegeo::v3 m_scale;
            
        public:
            UIAnimatedSprite(Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                             , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                             , const std::string& p_SpriteSheetName
                             , const Eegeo::dv3& p_EcefPosition
                             , const Eegeo::v2& p_Dimension
                             , IUIImageButtonClickedCallback& p_OnClickedEvent
                             , Eegeo::v2& p_FramesGridSize
                             , float p_FrameRate
                          );
            
            virtual ~UIAnimatedSprite();
            
            void Reset();
            
            inline void SetEcefPosition(const Eegeo::dv3& ecefPosition){ m_Quad->SetEcefPosition(ecefPosition); }
            inline Eegeo::v3 GetScale() { return m_Quad->GetScale(); }
            void SetScale(Eegeo::v3 p_scale);
            
            // UIInteractableItem interface
            virtual void OnItemClicked();
            virtual void OnFocusGained();
            virtual void OnFocusLost();
            
            virtual void Update(float dt);
            
            const virtual float GetItemRadius() { return m_Radius; }
            
            const virtual Eegeo::dv3& GetItemEcefPosition() { return m_Quad->GetEcefPosition(); }
        };
        
    }
}




#endif /* UIAnimatedQuad_h */
