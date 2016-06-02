//
//  UIImageButton.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#include "UIImageButton.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        UIImageButton::UIImageButton(UIQuad* quad,
                                     const Eegeo::v2& p_Dimension,
                                     const Eegeo::dv3& ecefPosition,
                                     Eegeo::Helpers::ICallback0& onClickedEvent) :
          m_OnClickedEvent(onClickedEvent)
        {
            m_ButtonImage = quad;
            m_Radius = (p_Dimension.x > p_Dimension.y ? p_Dimension.x : p_Dimension.y)/2.0f;
            m_ButtonImage->SetEcefPosition(ecefPosition);
            
        }
        
        UIImageButton::~UIImageButton(){
            Eegeo_DELETE m_ButtonImage;
        }
        
        void UIImageButton::Update(float dt)
        {
        }
        
        void UIImageButton::OnItemClicked()
        {
            m_OnClickedEvent();
        }
        
        void UIImageButton::OnFocusGained()
        {
            m_ButtonImage->SetScale(Eegeo::v3::One() * 1.1f);
        }
        
        void UIImageButton::OnFocusLost()
        {
            m_ButtonImage->SetScale(Eegeo::v3::One());
        }
        
    }
}
