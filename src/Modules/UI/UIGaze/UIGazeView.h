//
//  UIGazeView.hpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/25/16.
//
//

#ifndef UIGazeView_h
#define UIGazeView_h

#include "../UIQuad/UIQuadFactory.h"
#include "../UIAnimatedSprite.h"
#include "../UISprite.h"


namespace Eegeo
{
    namespace UIGaze
    {
        class UIGazeView 
        {
            Eegeo::UI::IUIQuadFactory& m_QuadFactory;
            UI::UIAnimatedSprite* m_GazeProgress;
            UI::UISprite* m_Pointer;
            
            void Init();
            
        public:
            
            
            UIGazeView(Eegeo::UI::IUIQuadFactory& quadFactory);
            ~UIGazeView();
            
            void Update(float dt);
            void SetEcefPosition(const dv3& position);
            
            void ShowView();
            void HideView();
            void ResetProgress();
            
            
        };
    }
}
#endif /* UIGazeView_h */
