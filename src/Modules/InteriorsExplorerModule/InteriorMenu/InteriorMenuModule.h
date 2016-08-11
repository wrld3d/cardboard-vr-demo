// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "EegeoWorld.h"
#include "../UI/UIInteraction/IUIInteractionObservable.h"
#include "InteriorMenuController.h"
#include "InteriorMenuItemRepository.h"
#include "InteriorMenuItemViewFactory.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        /*!
         * \brief Default implementation of Interior Menu control and rendering.
         *
         *  This module handles the displaying and control of Interior Menu.
         *
         */
        class InteriorMenuModule : protected Eegeo::NonCopyable
        {
            
        public:
            
            InteriorMenuModule(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                               , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                               , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                               , Eegeo::UI::IUICameraProvider& uiCameraProvider
                               , Eegeo::UI::IUIQuadFactory& quadFactory
                               , const std::string& spriteFileName
                               , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                               , int numberOfTilesAlong1Axis
                               );
            
            ~InteriorMenuModule();
            
            void Update(float dt);
            
            InteriorMenuItemRepository& GetRepository() const;
            InteriorMenuController& GetController() const;
            
            void SetMenuShouldDisplay(bool menuShouldDisplay);
            
        private:
            
            bool m_menuShouldDisplayMenu;
            
            InteriorMenuItemViewFactory* m_pViewFactory;
            InteriorMenuItemRepository* m_pRepository;
            InteriorMenuController * m_pController;
        };
    }
}
