// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "Bounds.h"
#include "VectorMath.h"
#include "EcefTangentBasis.h"
#include "IImmutableInteriorViewModel.h"
#include "EnvironmentFlatteningService.h"

namespace Examples
{
    class InteriorCameraAnimationPositionProvider
    {
    private:
        
        const Eegeo::Resources::Interiors::IImmutableInteriorViewModel& m_interiorViewModel;
        const Eegeo::Rendering::EnvironmentFlatteningService& m_environmentFlatteningService;

    public:

        InteriorCameraAnimationPositionProvider(const Eegeo::Resources::Interiors::IImmutableInteriorViewModel& interiorViewModel,
                                                const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService);

        Eegeo::dv3 GetInteriorFocusPosition();

        Eegeo::dv3 GetBasePositionForFloor(int floor);
    };
}