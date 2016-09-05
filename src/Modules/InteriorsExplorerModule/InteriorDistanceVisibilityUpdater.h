// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "Interiors.h"
#include "InteriorInteractionModel.h"

#include "IInteriorsExplorerModule.h"

namespace InteriorsExplorer
{
    class InteriorDistanceVisibilityUpdater : private Eegeo::NonCopyable
    {
    public:

        InteriorDistanceVisibilityUpdater(IInteriorsExplorerModule& interiorsExplorerModule,
                                          Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                          float distanceThreshold);
        ~InteriorDistanceVisibilityUpdater();

        void SetDistanceThreshold(float distanceThreshold);
        float GetDistanceThreshold() const;
        void SetInteriorShouldDisplay(bool shouldDisplay);
        bool GetInteriorShouldDisplay() const;
        bool GetInteriorIsVisible() const;
        void UpdateVisiblity(const Eegeo::dv3& currentPostion);

    private:

        IInteriorsExplorerModule& m_interiorsExplorerModule;
        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
        float m_squaredDistanceThreshold;
        bool m_interiorShouldDisplay;

    };
}
