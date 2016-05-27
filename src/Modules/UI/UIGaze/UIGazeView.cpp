//
//  UIGazeView.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/25/16.
//
//

#include "UIGazeView.h"

namespace Eegeo
{
    namespace UIGaze
    {
        UIGazeView::UIGazeView(UI::UIAnimatedSprite& loader, UI::UIImageButton& pointer)
        : m_Loader(loader)
        , m_Pointer(pointer)
        {
        }
        
        void UIGazeView::ShowView()
        {
            m_Loader.SetScale(v3::One());
        }
        
        void UIGazeView::HideView()
        {
            m_Loader.SetScale(v3::Zero());
            m_Loader.Reset();
        }
        
        void UIGazeView::ResetProgress()
        {
            m_Loader.Reset();
        }
        
        void UIGazeView::UpdateEcefPosition(dv3 position)
        {
            m_Loader.SetEcefPosition(position);
            m_Pointer.SetEcefPosition(position);
        }
        
    }
}
