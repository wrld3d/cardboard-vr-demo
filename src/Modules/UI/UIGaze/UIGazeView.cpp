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
        UIGazeView::UIGazeView(UI::UIAnimatedSprite& gazeProgress, UI::UIImageButton& pointer)
        : m_GazeProgress(gazeProgress)
        , m_Pointer(pointer)
        {
        }
        UIGazeView::~UIGazeView()
        {}
        
        void UIGazeView::ShowView()
        {
            m_GazeProgress.SetScale(v3::One());
        }
        
        void UIGazeView::HideView()
        {
            m_GazeProgress.SetScale(v3::Zero());
            m_GazeProgress.Reset();
        }
        
        void UIGazeView::ResetProgress()
        {
            m_GazeProgress.Reset();
        }
        
        void UIGazeView::UpdateEcefPosition(const dv3& position)
        {
            m_GazeProgress.SetEcefPosition(position);
            m_Pointer.SetEcefPosition(position);
        }
        
    }
}
