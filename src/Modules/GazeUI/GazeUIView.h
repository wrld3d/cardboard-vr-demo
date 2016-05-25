//
//  GazeUIView.hpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/25/16.
//
//

#ifndef GazeUIView_h
#define GazeUIView_h

#include "../UI/UIAnimatedSprite.h"
#include "../UI/UIImageButton.h"


namespace Eegeo
{
    namespace GazeUI
    {
        class GazeUIView 
        {
            
            UI::UIAnimatedSprite& m_Loader;
            UI::UIImageButton& m_Pointer;
            
            
        public:
            
            GazeUIView(UI::UIAnimatedSprite& loader, UI::UIImageButton& pointer);
            ~GazeUIView();
            
            void UpdateGazeProgress(int progress);
            void ShowView();
            void HideView();
            void ResetProgress();
            void SetCenterPoint(float x, float y);
            
            
            void UpdateEcefPosition(dv3 position);
            
        };
    }
}
#endif /* GazeUIView_h */
