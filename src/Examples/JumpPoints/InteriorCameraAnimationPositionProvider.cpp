// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorCameraAnimationPositionProvider.h"

namespace Examples
{

    InteriorCameraAnimationPositionProvider::InteriorCameraAnimationPositionProvider(const Eegeo::Resources::Interiors::IImmutableInteriorViewModel& interiorViewModel,
                                                                                     const Eegeo::Rendering::EnvironmentFlatteningService& environmentFlatteningService)
    : m_interiorViewModel(interiorViewModel)
    , m_environmentFlatteningService(environmentFlatteningService)
    {
    }

    Eegeo::dv3 InteriorCameraAnimationPositionProvider::GetInteriorFocusPosition()
    {
        Eegeo::v3 tangentSpacePosition = m_interiorViewModel.GetFloorCenteredTangentSpaceLookAt();
        const Eegeo::Space::EcefTangentBasis& interiorTangentBasis = m_interiorViewModel.GetTangentBasis();

        Eegeo::m33 tangentBasis;
        interiorTangentBasis.GetBasisOrientationAsMatrix(tangentBasis);
        const Eegeo::v3 relativeCameraInterestEcef = Eegeo::v3::Mul(tangentSpacePosition, tangentBasis);

        const Eegeo::Geometry::Bounds3D& tangentSpaceBounds = m_interiorViewModel.GetTangentSpaceBounds();

        const Eegeo::dv3 interiorOriginAtBase = interiorTangentBasis.GetPointEcef() + interiorTangentBasis.GetUp() * tangentSpaceBounds.GetMin().y;

        Eegeo::dv3 finalEcefInterestPosition = m_environmentFlatteningService.GetScaledPointEcef(interiorOriginAtBase, m_environmentFlatteningService.GetCurrentScale()) + relativeCameraInterestEcef;

        return finalEcefInterestPosition;
    }

    Eegeo::dv3 InteriorCameraAnimationPositionProvider::GetBasePositionForFloor(int floor)
    {
        return m_interiorViewModel.GetFloorTransformOrigin(floor);
    }
}
