// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModule.h"
#include "InteriorsExplorerModel.h"
#include "GlobeCameraController.h"
#include "InteriorsCameraControllerFactory.h"
#include "InteriorsCameraController.h"
#include "GlobeCameraTouchController.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorSelectionModel.h"
#include "InteriorInteractionModel.h"
#include "InteriorMenu/InteriorMenuModule.h"
#include "InteriorMenu/InteriorMenuItem.h"
#include "Logger.h"

namespace InteriorsExplorer
{
    
    InteriorsExplorerModule::InteriorsExplorerModule(  Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                                     , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                                                     , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                                     , Eegeo::UI::IUICameraProvider& uiCameraProvider
                                                     , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                                     , Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel
                                                     , Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel
                                                     , Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel) :
    m_interiorInteractionModel(interiorInteractionModel),
    m_interiorMenuItemGazeCallback(this, &InteriorsExplorerModule::OnMenuItemGazed)
    
    {
        floorId = 0;
        
        Eegeo::Resources::Interiors::InteriorId id(std::string("westport_house"));
        interiorSelectionModel.SelectInteriorId(id);
        
        const float transitionTime = 0.5f;
        m_pVisibilityUpdater = Eegeo_NEW(InteriorVisibilityUpdater)(interiorTransitionModel, interiorSelectionModel, interiorInteractionModel, transitionTime);
        m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorInteractionModel);
        
        
        std::string menuTextureFileName("mesh_example/PinIconTexturePage.png");
        m_pInteriorMenuModule = Eegeo_NEW(InteriorMenu::InteriorMenuModule)(uiRenderableFilter, uiQuadFactory, uiInteractionObservable,uiCameraProvider, menuTextureFileName, progressBarConfig, 4);
        m_pInteriorMenuModule->SetMenuShouldDisplay(m_pVisibilityUpdater->GetInteriorShouldDisplay());
        
        for (int lop=0; lop<7; lop++)
        {
            int iconId = lop+3;
            if(lop==0)
                iconId = 15;
            InteriorMenu::InteriorMenuItem* menuItem =  Eegeo_NEW(InteriorMenu::InteriorMenuItem)(lop, iconId, m_interiorMenuItemGazeCallback);
            m_pInteriorMenuModule->GetRepository().AddInteriorMenuItem(menuItem);
            m_pInteriorMenuItems.push_back(menuItem);
        }
        
    }
    
    InteriorsExplorerModule::~InteriorsExplorerModule()
    {
        while(m_pInteriorMenuItems.size()>0)
        {
            InteriorMenu::InteriorMenuItem* menuItem = *m_pInteriorMenuItems.begin();
            m_pInteriorMenuModule->GetRepository().RemoveInteriorMenuItem(menuItem);
            m_pInteriorMenuItems.erase(m_pInteriorMenuItems.begin());
            Eegeo_DELETE menuItem;
        }
        
        Eegeo_DELETE m_pInteriorMenuModule;
        Eegeo_DELETE m_pModel;
        Eegeo_DELETE m_pVisibilityUpdater;
    }
    
    
    void InteriorsExplorerModule::OnMenuItemGazed(InteriorMenu::InteriorMenuItem& menuItem)
    {
        floorId = menuItem.GetId();
        m_interiorInteractionModel.SetSelectedFloorIndex(floorId);
    }
    
    void InteriorsExplorerModule::SelectFloor(int floor)
    {
        floorId = floor;
        m_interiorInteractionModel.SetSelectedFloorIndex(floor);
    }
        
    bool InteriorsExplorerModule::InteriorLoaded()
    {
        return m_interiorInteractionModel.HasInteriorModel();
    }
    
    void InteriorsExplorerModule::Update(float dt) const
    {
        m_pInteriorMenuModule->Update(dt);
        if(m_interiorInteractionModel.HasInteriorModel())
        {
            m_interiorInteractionModel.SetSelectedFloorIndex(floorId);
            m_pVisibilityUpdater->Update(dt);
        }
    }
    
    void InteriorsExplorerModule::ToggleInteriorDisplay()
    {
        bool shouldDisplay = !m_pVisibilityUpdater->GetInteriorShouldDisplay();
        m_pVisibilityUpdater->SetInteriorShouldDisplay(shouldDisplay);
        m_pVisibilityUpdater->UpdateVisiblityImmediately();
        m_pInteriorMenuModule->SetMenuShouldDisplay(shouldDisplay);
    }
    
    void InteriorsExplorerModule::ShowInteriors()
    {
        if (!m_pVisibilityUpdater->GetInteriorShouldDisplay())
        {
            m_pVisibilityUpdater->SetInteriorShouldDisplay(true);
            m_pVisibilityUpdater->UpdateVisiblityImmediately();
            m_pInteriorMenuModule->SetMenuShouldDisplay(true);
        }
    }
    
    void InteriorsExplorerModule::HideInteriors()
    {
        if (m_pVisibilityUpdater->GetInteriorShouldDisplay())
        {
            m_pVisibilityUpdater->SetInteriorShouldDisplay(false);
            m_pVisibilityUpdater->UpdateVisiblityImmediately();
            m_pInteriorMenuModule->SetMenuShouldDisplay(false);
        }
     
    }
    
}
