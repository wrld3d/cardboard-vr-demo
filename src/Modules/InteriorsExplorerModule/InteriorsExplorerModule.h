// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Interiors.h"
#include "Types.h"
#include "GlobeCamera.h"
#include "Rendering.h"
#include "IIdentity.h"
#include "InteriorsExplorer.h"
#include "IInteriorsExplorerModule.h"

namespace InteriorsExplorer
{
    class InteriorsExplorerModule : public IInteriorsExplorerModule, private Eegeo::NonCopyable
    {
    public:
        
        InteriorsExplorerModule(
                                Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel);
        
        ~InteriorsExplorerModule();
        
        InteriorsExplorerModel& GetInteriorsExplorerModel() const;
        InteriorVisibilityUpdater& GetInteriorVisibilityUpdater() const;
        
        void Update(float dt) const;
        
        void SwitchToInterior();
        bool InteriorLoaded();
        
        void ToggleInteriorDisplay();
        
    private:
        
        InteriorsExplorerModel* m_pModel;
        InteriorVisibilityUpdater* m_pVisibilityUpdater;
        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
    };
}
