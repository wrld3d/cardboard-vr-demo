// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuModule.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            DeadZoneMenuModule::DeadZoneMenuModule(IUIRenderableFilter& uiRenderableFilter
                                                   , IUIQuadFactory& uiQuadFactory
                                                   , IUIInteractionObservable& uiInteractionObservable
                                                   , IUICameraProvider& uiCameraProvider
                                                   , const std::string& spriteFileName
                                                   , const UIProgressBarConfig& progressBarConfig
                                                   , int numberOfTilesAlong1Axis
                                                   )
            {
                m_pViewFactory = new DeadZoneMenuItemViewFactory(uiRenderableFilter, uiQuadFactory, spriteFileName, progressBarConfig, numberOfTilesAlong1Axis);
                m_pRepository = new DeadZoneMenuItemRepository();
                m_pController = new DeadZoneMenuController(*m_pRepository, *m_pViewFactory, uiInteractionObservable, uiCameraProvider);
            }
            
            DeadZoneMenuModule::~DeadZoneMenuModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pRepository;
                Eegeo_DELETE m_pViewFactory;
            }
            
            void DeadZoneMenuModule::Update(float dt)
            {
                m_pController->Update(dt);
            }
            
            DeadZoneMenuItemRepository& DeadZoneMenuModule::GetRepository() const
            {
                return *m_pRepository;
            }
            
            DeadZoneMenuController& DeadZoneMenuModule::GetController() const
            {
                return *m_pController;
            }
            
        }
    }
}
