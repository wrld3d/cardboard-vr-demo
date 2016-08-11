// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldMenuController.h"
#include "WorldMenuModule.h"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            WorldMenuModule::WorldMenuModule(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                                   , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                                                   , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                                   , Eegeo::UI::IUICameraProvider& uiCameraProvider
                                                   , const std::string& spriteFileName
                                                   , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                                   , int numberOfTilesAlong1Axis)
            {
                m_menuShouldDisplayMenu = true;
                m_pViewFactory = new WorldMenuItemViewFactory(uiRenderableFilter, uiQuadFactory, spriteFileName, progressBarConfig, numberOfTilesAlong1Axis);
                m_pRepository = new WorldMenuItemRepository();
                m_pController = new WorldMenuController(*m_pRepository, *m_pViewFactory, uiInteractionObservable, uiCameraProvider, uiQuadFactory, uiRenderableFilter);
            }
            
            WorldMenuModule::~WorldMenuModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pRepository;
                Eegeo_DELETE m_pViewFactory;
            }
            
            void WorldMenuModule::SetMenuShouldDisplay(bool menuShouldDisplay)
            {
                m_menuShouldDisplayMenu = menuShouldDisplay;
                m_pController->SetMenuItemsShouldRender(menuShouldDisplay);
            }
            
            void WorldMenuModule::Update(float dt)
            {
                m_pController->Update(dt);
            }
            
            WorldMenuItemRepository& WorldMenuModule::GetRepository() const
            {
                return *m_pRepository;
            }
            
            WorldMenuController& WorldMenuModule::GetController() const
            {
                return *m_pController;
            }
            
        }
    }
}
