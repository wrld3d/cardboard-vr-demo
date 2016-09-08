// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

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
            UI::UISprite* m_pPointer;
            
            void Init(Eegeo::UI::IUIQuadFactory& quadFactory,
                      UI::IUIRenderableFilter& uiRenderableFilter,
                      const std::string& gazePointerAsset);
            
        public:
            
            UIGazeView(Eegeo::UI::IUIQuadFactory& quadFactory,
                       UI::IUIRenderableFilter& uiRenderableFilter,
                       const std::string& gazePointerAsset);
            ~UIGazeView();
            
            void Update(float dt);
            void SetEcefPosition(const dv3& position);
            
            void ShowView();
            void HideView();
            void ResetProgress();
            
            
        };
    }
}

