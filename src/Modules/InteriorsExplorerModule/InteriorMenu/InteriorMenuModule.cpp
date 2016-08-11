// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorMenuController.h"
#include "InteriorMenuModule.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        InteriorMenuModule::InteriorMenuModule(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                               , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                                               , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                               , Eegeo::UI::IUICameraProvider& uiCameraProvider
                                               , Eegeo::UI::IUIQuadFactory& quadFactory
                                               , const std::string& spriteFileName
                                               , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                               , int numberOfTilesAlong1Axis)
        {
            m_menuShouldDisplayMenu = true;
            m_pViewFactory = new InteriorMenuItemViewFactory(uiRenderableFilter, uiQuadFactory, spriteFileName, progressBarConfig, numberOfTilesAlong1Axis);
            m_pRepository = new InteriorMenuItemRepository();
            m_pController = new InteriorMenuController(*m_pRepository, *m_pViewFactory, uiInteractionObservable, uiCameraProvider, quadFactory, uiRenderableFilter);
        }
        
        InteriorMenuModule::~InteriorMenuModule()
        {
            Eegeo_DELETE m_pController;
            Eegeo_DELETE m_pRepository;
            Eegeo_DELETE m_pViewFactory;
        }
        
        void InteriorMenuModule::SetMenuShouldDisplay(bool menuShouldDisplay)
        {
            m_menuShouldDisplayMenu = menuShouldDisplay;
            m_pController->SetMenuItemsShouldRender(menuShouldDisplay);
        }
        
        void InteriorMenuModule::Update(float dt)
        {
            m_pController->Update(dt);
        }
        
        InteriorMenuItemRepository& InteriorMenuModule::GetRepository() const
        {
            return *m_pRepository;
        }
        
        InteriorMenuController& InteriorMenuModule::GetController() const
        {
            return *m_pController;
        }
        
    }
}
