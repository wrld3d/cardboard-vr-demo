//
//  GazeUIView.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/25/16.
//
//

#include "GazeUIView.h"

namespace Eegeo
{
    namespace GazeUI
    {
        GazeUIView::GazeUIView(UI::UIAnimatedSprite& loader, UI::UIImageButton& pointer)
        : m_Loader(loader)
        , m_Pointer(pointer)
        {
        }
        
        void GazeUIView::UpdateGazeProgress(int progress)
        {
        }
        
        void GazeUIView::ShowView()
        {
            m_Loader.SetScale(v3::One());
        }
        
        void GazeUIView::HideView()
        {
            m_Loader.SetScale(v3::Zero());
            m_Loader.Reset();
        }
        
        void GazeUIView::ResetProgress()
        {
            m_Loader.Reset();
        }
        
        void GazeUIView::SetCenterPoint(float x, float y)
        {
        }
        
        void GazeUIView::UpdateEcefPosition(dv3 position)
        {
            m_Loader.SetEcefPosition(position);
            m_Pointer.SetEcefPosition(position);
        }
        
    }
}
