// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "InteriorDistanceVisibilityUpdater.h"
#include "InteriorsFloorModel.h"

namespace InteriorsExplorer
{
    InteriorDistanceVisibilityUpdater::InteriorDistanceVisibilityUpdater(IInteriorsExplorerModule& interiorsExplorerModule,
                                                                         Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel,
                                                                         float distanceThreshold)
    : m_interiorsExplorerModule(interiorsExplorerModule)
    , m_interiorInteractionModel(interiorInteractionModel)
    , m_squaredDistanceThreshold(distanceThreshold*distanceThreshold)
    , m_interiorShouldDisplay(false)
    {
    }

    InteriorDistanceVisibilityUpdater::~InteriorDistanceVisibilityUpdater()
    {
    }

    void InteriorDistanceVisibilityUpdater::SetDistanceThreshold(float distanceThreshold)
    {
        m_squaredDistanceThreshold = distanceThreshold * distanceThreshold;
    }

    float InteriorDistanceVisibilityUpdater::GetDistanceThreshold() const
    {
        return Eegeo::Math::Sqrtf(m_squaredDistanceThreshold);
    }

    void InteriorDistanceVisibilityUpdater::SetInteriorShouldDisplay(bool shouldDisplay)
    {
        m_interiorShouldDisplay = shouldDisplay;
    }

    bool InteriorDistanceVisibilityUpdater::GetInteriorShouldDisplay() const
    {
        return m_interiorShouldDisplay;
    }

    bool InteriorDistanceVisibilityUpdater::GetInteriorIsVisible() const
    {
        return m_interiorsExplorerModule.IsInteriorVisible();
    }

    void InteriorDistanceVisibilityUpdater::UpdateVisiblity(const Eegeo::dv3& currentPostion)
    {
        if (m_interiorInteractionModel.HasInteriorModel())
        {
            Eegeo::dv3 interiorPostion = m_interiorInteractionModel.GetSelectedFloorModel()->GetFloorBoundsCenterEcef();

            if (currentPostion.SquareDistanceTo(interiorPostion) <= m_squaredDistanceThreshold)
            {
                if (!m_interiorsExplorerModule.IsInteriorVisible())
                {
                    m_interiorsExplorerModule.ShowInteriors();
                }
            }
            else
            {
                if (m_interiorsExplorerModule.IsInteriorVisible())
                {
                    m_interiorsExplorerModule.HideInteriors();
                }
            }
        }
    }
}
