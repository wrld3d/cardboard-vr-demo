// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuModule.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            DeadZoneMenuModule::DeadZoneMenuModule(IUIRenderableFilter& p_UIRenderableFilter
                                                   , IUIQuadFactory& p_IUIQuadFactory
                                                   , IUIInteractionObservable& p_IUIInteractionObservable
                                                   , IUICameraProvider& p_UICameraProvider
                                                   , std::string& spriteFileName
                                                   , int numberOfTilesAlong1Axis
                                                   )
            {
                m_pViewFactory = new DeadZoneMenuItemViewFactory(p_UIRenderableFilter, p_IUIQuadFactory, p_UICameraProvider, spriteFileName, numberOfTilesAlong1Axis);
                m_pRepository = new DeadZoneMenuItemRepository();
                m_pController = new DeadZoneMenuController(*m_pRepository, *m_pViewFactory, p_IUIInteractionObservable, p_UICameraProvider);
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
