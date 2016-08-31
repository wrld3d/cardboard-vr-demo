// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "EegeoWorld.h"
#include "../UI/UIInteraction/IUIInteractionObservable.h"
#include "WorldMenuController.h"
#include "WorldMenuItemRepository.h"
#include "WorldMenuItemViewFactory.h"
namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            /*!
             * \brief Default implementation of World Menu control and rendering.
             *
             *  This module handles the displaying and control of World Menu.
             *
             */
            class WorldMenuModule : protected Eegeo::NonCopyable
            {
                
            public:
                
                WorldMenuModule(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                   , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                                   , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                   , Eegeo::UI::IUICameraProvider& uiCameraProvider
                                   , const std::string& spriteFileName
                                   , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                   , int numberOfTilesAlong1Axis
                                   );
                
                ~WorldMenuModule();
                
                void Update(float dt);
                
                WorldMenuItemRepository& GetRepository() const;
                WorldMenuController& GetController() const;
                
                void SetMenuShouldDisplay(bool menuShouldDisplay);
                
            private:
                
                bool m_menuShouldDisplayMenu;
                
                WorldMenuItemViewFactory* m_pViewFactory;
                WorldMenuItemRepository* m_pRepository;
                WorldMenuController * m_pController;
            };
        }
    }
    
}