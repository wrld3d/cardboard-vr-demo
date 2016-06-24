// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Interiors.h"

    namespace InteriorsExplorer
{
    class InteriorVisibilityUpdater : private Eegeo::NonCopyable
    {
    public:
        
        InteriorVisibilityUpdater(Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel,
                                  const Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel,
                                  const Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                  float interiorTransitionTimeSeconds);
        ~InteriorVisibilityUpdater();
        
        void SetInteriorShouldDisplay(bool shouldDisplay);
        bool GetInteriorShouldDisplay() const { return m_interiorShouldDisplay; }
        bool GetInteriorHasLoaded() const;
        void Update(float dt);
        void UpdateVisiblityImmediately();
    private:
        
        Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
        const Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
        const Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
        const float m_interiorTransitionTimeSeconds;
        
        float m_interiorTransitionParameter;
        bool m_interiorShouldDisplay;
        
    };
}
