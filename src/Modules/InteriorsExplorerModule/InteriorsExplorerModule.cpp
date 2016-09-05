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
#include "InteriorTransitionModel.h"
#include "InteriorMenu/InteriorMenuModule.h"
#include "InteriorMenu/InteriorMenuController.h"
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
                                                     , Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel
                                                     , const std::string& menuTextureFileName
                                                     , int numberOfTilesAlong1Axis) :
    m_interiorInteractionModel(interiorInteractionModel),
    m_interiorSelectionModel(interiorSelectionModel),
    m_interiorTransitionModel(interiorTransitionModel),
    m_interiorMenuItemGazeCallback(this, &InteriorsExplorerModule::OnMenuItemGazed)
    {
        m_floorId = 0;
        
        Eegeo::Resources::Interiors::InteriorId id(std::string("westport_house"));
        interiorSelectionModel.SelectInteriorId(id);
        
        const float transitionTime = 3.f;
        m_pVisibilityUpdater = Eegeo_NEW(InteriorVisibilityUpdater)(interiorTransitionModel, interiorSelectionModel, interiorInteractionModel, transitionTime);
        m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorInteractionModel);
        
        m_pInteriorMenuModule = Eegeo_NEW(InteriorMenu::InteriorMenuModule)(uiRenderableFilter, uiQuadFactory, uiInteractionObservable,uiCameraProvider, uiQuadFactory, menuTextureFileName, progressBarConfig, numberOfTilesAlong1Axis);
        m_pInteriorMenuModule->SetMenuShouldDisplay(m_pVisibilityUpdater->GetInteriorShouldDisplay());
        
        for (int lop=-1; lop<7; lop++)
        {
            int iconId = lop+3;
            if(lop==-1)
                iconId = 15;
            InteriorMenu::InteriorMenuItem* pMenuItem =  Eegeo_NEW(InteriorMenu::InteriorMenuItem)(lop, iconId, m_interiorMenuItemGazeCallback);
            m_pInteriorMenuModule->GetRepository().AddInteriorMenuItem(pMenuItem);
            m_interiorMenuItems.push_back(pMenuItem);
        }
        
        
    }
    
    InteriorsExplorerModule::~InteriorsExplorerModule()
    {
        while(m_interiorMenuItems.size()>0)
        {
            InteriorMenu::InteriorMenuItem* pMenuItem = *m_interiorMenuItems.begin();
            m_pInteriorMenuModule->GetRepository().RemoveInteriorMenuItem(pMenuItem);
            m_interiorMenuItems.erase(m_interiorMenuItems.begin());
            Eegeo_DELETE pMenuItem;
        }
        
        Eegeo_DELETE m_pInteriorMenuModule;
        Eegeo_DELETE m_pModel;
        Eegeo_DELETE m_pVisibilityUpdater;
    }
    
    void InteriorsExplorerModule::ForceEnterInterior(int floorId)
    {
        ShowInteriors();
        m_floorId = floorId;
        SelectFloor(m_floorId, false);
        m_pInteriorMenuModule->SetMenuShouldDisplay(false);
    }
    
    void InteriorsExplorerModule::ForceLeaveInterior()
    {
        HideInteriors();
    }
    
    void InteriorsExplorerModule::OnMenuItemGazed(InteriorMenu::InteriorMenuItem& menuItem)
    {
        m_menuItemCallbacks.ExecuteCallbacks(menuItem);
    }
    
    void InteriorsExplorerModule::SelectFloor(int floor, bool shouldAnimate)
    {
        if(m_floorId>=0)
        {
            m_floorId = floor;
            if (shouldAnimate)
            {
                m_pModel->AnimateToFloor(floor);
            }
            else
            {
                m_pModel->SelectFloor(floor);
            }

            m_pInteriorMenuModule->GetController().SetSelectedFloorId(m_floorId);
        }
    }

    int InteriorsExplorerModule::GetSelectedFloor() const
    {
        return m_floorId;
    }

    void InteriorsExplorerModule::SelectInterior(std::string interiorID)
    {
        Eegeo::Resources::Interiors::InteriorId id(interiorID);
        m_interiorSelectionModel.SelectInteriorId(id);
    }

    std::string InteriorsExplorerModule::GetSelectedInteriorID() const
    {
        return m_interiorSelectionModel.GetSelectedInteriorId().Value();
    }

    bool InteriorsExplorerModule::InteriorLoaded()
    {
        return m_interiorInteractionModel.HasInteriorModel();
    }
    
    void InteriorsExplorerModule::Update(float dt) const
    {
        if(m_floorId>=0)
        {
            m_pInteriorMenuModule->Update(dt);
            if(m_interiorInteractionModel.HasInteriorModel())
            {
                m_pVisibilityUpdater->Update(dt);
                m_pModel->Update(dt);
            }
        }
    }
    
    void InteriorsExplorerModule::ToggleInteriorDisplay()
    {
        bool shouldDisplay = !m_pVisibilityUpdater->GetInteriorShouldDisplay();
        m_pVisibilityUpdater->SetInteriorShouldDisplay(shouldDisplay);
        m_pInteriorMenuModule->SetMenuShouldDisplay(shouldDisplay);
    }
    
    void InteriorsExplorerModule::ShowInteriors()
    {
        if (!m_pVisibilityUpdater->GetInteriorShouldDisplay())
        {
            m_floorId = 0;
            m_pModel->SelectFloor(m_floorId);
            m_pInteriorMenuModule->GetController().SetSelectedFloorId(m_floorId);
            m_pVisibilityUpdater->SetInteriorShouldDisplay(true);
            m_pInteriorMenuModule->SetMenuShouldDisplay(true);  
        }
    }
    
    void InteriorsExplorerModule::HideInteriors()
    {
        if (m_pVisibilityUpdater->GetInteriorShouldDisplay())
        {
            m_pVisibilityUpdater->SetInteriorShouldDisplay(false);
            m_pInteriorMenuModule->SetMenuShouldDisplay(false);
        }
     
    }

    bool InteriorsExplorerModule::IsInteriorVisible()
    {
        return m_pVisibilityUpdater->GetInteriorShouldDisplay();
    }

    void InteriorsExplorerModule::RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback0& callback)
    {
        m_interiorTransitionModel.RegisterChangedCallback(callback);
        m_interiorInteractionModel.RegisterInteractionStateChangedCallback(callback);
    }

    void InteriorsExplorerModule::UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback0& callback)
    {
        m_interiorTransitionModel.UnregisterChangedCallback(callback);
        m_interiorInteractionModel.UnregisterInteractionStateChangedCallback(callback);
    }

    void InteriorsExplorerModule::RegisterMenuItemGazedCallback(Eegeo::Helpers::ICallback1<InteriorMenu::InteriorMenuItem&>& callback)
    {
        m_menuItemCallbacks.AddCallback(callback);
    }

    void InteriorsExplorerModule::UnregisterMenuItemGazedCallback(Eegeo::Helpers::ICallback1<InteriorMenu::InteriorMenuItem&>& callback)
    {
        m_menuItemCallbacks.RemoveCallback(callback);
    }

    void InteriorsExplorerModule::RegisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback)
    {
        m_pModel->RegisterInteriorAnimationCallback(callback);
    }

    void InteriorsExplorerModule::UnregisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback)
    {
        m_pModel->UnregisterInteriorAnimationCallback(callback);
    }

    void InteriorsExplorerModule::SetMenuVisibilityThresholdAngle(float angle)
    {
        m_pInteriorMenuModule->GetController().SetMenuVisibilityThresholdAngle(angle);
    }

    float InteriorsExplorerModule::GetMenuVisibilityThresholdAngle()
    {
        return m_pInteriorMenuModule->GetController().GetMenuVisibilityThresholdAngle();
    }
}
