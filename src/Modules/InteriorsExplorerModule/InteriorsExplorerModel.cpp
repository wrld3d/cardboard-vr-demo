// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorsExplorerModel.h"

#include "InteriorsModel.h"
#include "InteriorsFloorModel.h"
#include "InteriorSelectionModel.h"
#include "InteriorsModel.h"
#include "InteriorId.h"
#include "InteriorsFloorModel.h"
#include "InteriorInteractionModel.h"

namespace InteriorsExplorer
{
    
    InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel
    )
    : m_interiorInteractionModel(interiorInteractionModel)
    { }
    
    InteriorsExplorerModel::~InteriorsExplorerModel()
    { }
    
    void InteriorsExplorerModel::SelectFloor(int floor)
    {
        if (!m_interiorInteractionModel.HasInteriorModel())
        {
            return;
        }
        
        
        m_interiorInteractionModel.SetSelectedFloorIndex(floor);
        
        const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = m_interiorInteractionModel.GetSelectedFloorModel();
        Eegeo_ASSERT(pFloorModel, "Could not fetch current floor model");
        
    }
    
}
