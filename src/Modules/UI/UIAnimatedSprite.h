//
//  UIAnimatedQuad.h
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIQuad/UIQuad.h"
#include "UIInteraction/IUIInteractableItem.h"
#include "ICallback.h"

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
            Eegeo::Helpers::ICallback0& m_OnClickedEvent;
            
            Eegeo::v3 m_scale;
            
        public:
            UIAnimatedSprite(UIQuad* quad
                             , Eegeo::Helpers::ICallback0& onClickedEvent
                             , const Eegeo::v2& dimension
                             , Eegeo::v2& framesGridSize
                             , float frameRate
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
