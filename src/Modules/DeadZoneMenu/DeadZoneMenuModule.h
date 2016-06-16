// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "EegeoWorld.h"
#include "../UI/UIInteraction/IUIInteractionObservable.h"
#include "DeadZoneMenuController.h"
#include "DeadZoneMenuItemRepository.h"
#include "DeadZoneMenuItemViewFactory.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            /*!
             * \brief Default implementation of DeadZone Menu control and rendering.
             *
             *  This module handles the displaying and control of DeadZone Menu.
             *
             */
            class DeadZoneMenuModule : protected Eegeo::NonCopyable
            {
            public:
                
                DeadZoneMenuModule(IUIRenderableFilter& p_UIRenderableFilter
                                   , IUIQuadFactory& p_IUIQuadFactory
                                   , IUIInteractionObservable& p_IUIInteractionObservable
                                   , IUICameraProvider& p_UICameraProvider
                                   , std::string& spriteFileName
                                   , int numberOfTilesAlong1Axis
                                   );
                
                ~DeadZoneMenuModule();
                
                void Update(float dt);
                
                DeadZoneMenuItemRepository& GetRepository() const;
                
                DeadZoneMenuController& GetController() const;
                
            private:
                DeadZoneMenuItemViewFactory* m_pViewFactory;
                DeadZoneMenuItemRepository* m_pRepository;
                DeadZoneMenuController * m_pController;
            };
        }
    }
}
