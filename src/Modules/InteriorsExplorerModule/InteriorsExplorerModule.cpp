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
#include "Logger.h"

namespace InteriorsExplorer
{
    
    InteriorsExplorerModule::InteriorsExplorerModule(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                     Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                                     Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel) :
    m_InteriorInteractionModel(interiorInteractionModel)
    {
        Eegeo::Resources::Interiors::InteriorId id(std::string("westport_house"));
        interiorSelectionModel.SelectInteriorId(id);
        
        const float transitionTime = 0.5f;
        m_pVisibilityUpdater = Eegeo_NEW(InteriorVisibilityUpdater)(interiorTransitionModel, interiorSelectionModel, interiorInteractionModel, transitionTime);
        m_pModel = Eegeo_NEW(InteriorsExplorerModel)(interiorInteractionModel);
        
    }
    
    InteriorsExplorerModule::~InteriorsExplorerModule()
    {
        Eegeo_DELETE m_pModel;
        Eegeo_DELETE m_pVisibilityUpdater;
    }
    void InteriorsExplorerModule::ToggleInteriorDisplay(){
        m_InteriorInteractionModel.SetSelectedFloorIndex(2);
        m_pVisibilityUpdater->SetInteriorShouldDisplay(!m_pVisibilityUpdater->GetInteriorShouldDisplay());
    }
    
    InteriorVisibilityUpdater& InteriorsExplorerModule::GetInteriorVisibilityUpdater() const
    {
        return *m_pVisibilityUpdater;
    }
    
    bool InteriorsExplorerModule::InteriorLoaded(){
        return m_InteriorInteractionModel.HasInteriorModel();
    }
    
    void InteriorsExplorerModule::Update(float dt) const
    {
        m_pVisibilityUpdater->Update(dt);
    }
    
    void InteriorsExplorerModule::SwitchToInterior(){
        m_pVisibilityUpdater->SetInteriorShouldDisplay(true);
    }
    
    InteriorsExplorerModel& InteriorsExplorerModule::GetInteriorsExplorerModel() const
    {
        return *m_pModel;
    }
    
}
