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
#include "../IUIRenderableFilter.h"

namespace Eegeo
{
    namespace UIGaze
    {
        class UIGazeView 
        {
            UI::UIAnimatedSprite* m_pGazeProgress;
            UI::UISprite* m_pPointer;
            
            void Init(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter);
            
        public:
            
            UIGazeView(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter);
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
