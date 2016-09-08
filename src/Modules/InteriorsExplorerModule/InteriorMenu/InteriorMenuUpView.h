// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "../../UI/UIQuad/UIQuadFactory.h"
#include "../../UI/UIAnimatedSprite.h"
#include "../../UI/UISprite.h"
#include "../../UI/IUIRenderableFilter.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        class InteriorMenuUpView 
        {
            Eegeo::UI::UISprite* m_pPointer;
            bool m_isShown;
            
            void Init(Eegeo::UI::IUIQuadFactory& quadFactory,
                      Eegeo::UI::IUIRenderableFilter& uiRenderableFilter,
                      std::string texture,
                      int spriteID,
                      int numTilesAlong1Axes);

        public:
            
            InteriorMenuUpView(Eegeo::UI::IUIQuadFactory& quadFactory,
                               Eegeo::UI::IUIRenderableFilter& uiRenderableFilter,
                               std::string texture,
                               int spriteID,
                               int numTilesAlong1Axes);
            ~InteriorMenuUpView();
            
            void Update(float dt);
            void SetEcefPosition(const Eegeo::dv3& position);
            bool IsShown(){return m_isShown;}
            
            
            void ShowView();
            void HideView();
            
        };
    }
}

