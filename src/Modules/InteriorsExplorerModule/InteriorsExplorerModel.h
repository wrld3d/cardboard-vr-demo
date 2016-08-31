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

        void AnimateToFloor(int floor);

        void Update(float dt);

        void RegisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback);

        void UnregisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback);
        
    private:
        
        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
        int m_currentFloor;
        float m_currentFloorParam;
        bool m_isAnimating;
        float m_animationSpeed;
        InteriorsExplorer::InteriorsExplorerFloorAnimationState m_currentState;
        
        Eegeo::Helpers::CallbackCollection1<InteriorsExplorerFloorAnimationState> m_animationCallbackCollection;
    };
}