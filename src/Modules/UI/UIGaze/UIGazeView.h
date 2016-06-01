//
//  UIGazeView.hpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/25/16.
//
//

#ifndef UIGazeView_h
#define UIGazeView_h

#include "../UIAnimatedSprite.h"
#include "../UIImageButton.h"


namespace Eegeo
{
    namespace UIGaze
    {
        class UIGazeView 
        {
            
            UI::UIAnimatedSprite& m_GazeProgress;
            UI::UIImageButton& m_Pointer;
            
        public:
            
            UIGazeView(UI::UIAnimatedSprite& gazeProgress, UI::UIImageButton& pointer);
            ~UIGazeView();
            
            void ShowView();
            void HideView();
            void ResetProgress();
            
            void UpdateEcefPosition(const dv3& position);
            
        };
    }
}
#endif /* UIGazeView_h */
