// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"
#include "ICallback.h"
#include "InteriorId.h"
#include "InteriorsExplorer.h"

    namespace InteriorsExplorer
{
    class InteriorsExplorerModel : private Eegeo::NonCopyable
    {
    public:
        InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel);
        ~InteriorsExplorerModel();
        void SelectFloor(int floor);
        
    private:
        
        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
        
        
    };
}