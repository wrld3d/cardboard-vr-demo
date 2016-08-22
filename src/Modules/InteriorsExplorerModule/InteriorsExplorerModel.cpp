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
    const float FloorSwtichingSpeed = 0.5f;


    InteriorsExplorerModel::InteriorsExplorerModel(Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel)
    : m_interiorInteractionModel(interiorInteractionModel)
    , m_currentFloor(0)
    , m_currentFloorParam(0.f)
    , m_isAnimating(false)
    , m_animationSpeed(1.f)
    , m_currentState(InteriorsExplorer::InteriorsExplorerFloorAnimationState::AnimationEnded)
    { }
    
    InteriorsExplorerModel::~InteriorsExplorerModel()
    { }
    
    void InteriorsExplorerModel::SelectFloor(int floor)
    {
        if (!m_interiorInteractionModel.HasInteriorModel())
        {
            return;
        }

        const bool shouldExitExpandedMode = m_interiorInteractionModel.IsFullyExpanded() || m_interiorInteractionModel.IsEnteringExpanded();
        if (shouldExitExpandedMode)
        {
            m_interiorInteractionModel.ToggleExpanded();
        }

        if (m_interiorInteractionModel.GetSelectedFloorIndex() == floor)
        {
            return;
        }

        m_interiorInteractionModel.SetSelectedFloorIndex(floor);

        const Eegeo::Resources::Interiors::InteriorsFloorModel* pFloorModel = m_interiorInteractionModel.GetSelectedFloorModel();
        Eegeo_ASSERT(pFloorModel, "Could not fetch current floor model");
        
    }

    void InteriorsExplorerModel::AnimateToFloor(int floor)
    {
        if (!m_interiorInteractionModel.HasInteriorModel())
        {
            return;
        }

        if (m_interiorInteractionModel.GetSelectedFloorIndex() == floor)
        {
            return;
        }

        m_currentFloor = floor;
        m_currentFloorParam = m_interiorInteractionModel.GetFloorParam();
        m_isAnimating = true;
        m_animationSpeed = (m_interiorInteractionModel.GetSelectedFloorIndex() < floor ? FloorSwtichingSpeed : -FloorSwtichingSpeed);

        const bool shouldEnterExpandedMode = m_interiorInteractionModel.IsCollapsed() || m_interiorInteractionModel.IsExitingExpanded();
        if (shouldEnterExpandedMode)
        {
            m_interiorInteractionModel.ToggleExpanded();
        }

        m_currentState = InteriorsExplorer::InteriorsExplorerFloorAnimationState::AnimationStarted;
        m_animationCallbackCollection.ExecuteCallbacks(m_currentState);
    }

    void InteriorsExplorerModel::Update(float dt)
    {
        if (m_isAnimating && m_interiorInteractionModel.IsFullyExpanded())
        {
            m_currentFloorParam += dt * m_animationSpeed;

            const bool floorAnimationEnded = (m_animationSpeed > 0 && m_currentFloorParam > m_currentFloor) || (m_animationSpeed < 0 && m_currentFloorParam < m_currentFloor);
            if (floorAnimationEnded)
            {
                m_currentFloorParam = m_currentFloor;
                m_interiorInteractionModel.ToggleExpanded();
                m_interiorInteractionModel.SetSelectedFloorIndex(m_currentFloor);
            }

            m_interiorInteractionModel.SetFloorParam(m_currentFloorParam);
        }

        if (m_isAnimating && m_interiorInteractionModel.IsCollapsed())
        {
            m_isAnimating = false;
            m_currentState = InteriorsExplorer::InteriorsExplorerFloorAnimationState::AnimationEnded;
            m_animationCallbackCollection.ExecuteCallbacks(m_currentState);
        }
    }

    void InteriorsExplorerModel::RegisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback)
    {
        m_animationCallbackCollection.AddCallback(callback);
    }

    void InteriorsExplorerModel::UnregisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback)
    {
        m_animationCallbackCollection.RemoveCallback(callback);
    }
    
}
