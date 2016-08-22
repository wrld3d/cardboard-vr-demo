// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "ICallback.h"
#include "VectorMath.h"
#include "IInteriorsExplorerModule.h"
#include "JumpPointsCameraController.h"
#include "InteriorCameraAnimationPositionProvider.h"

namespace Examples
{
    class FloorSwitchCameraAnimator: protected Eegeo::NonCopyable
    {
    private:

        InteriorsExplorer::IInteriorsExplorerModule& m_interiorsExplorerModule;
        Eegeo::VR::JumpPointsCameraController& m_vrCamera;
        InteriorCameraAnimationPositionProvider m_cameraPositionProvider;
        Eegeo::dv3 m_cameraPosBase;

        bool m_isAnimating;
        Eegeo::Helpers::TCallback1<FloorSwitchCameraAnimator, InteriorsExplorer::InteriorsExplorerFloorAnimationState> m_animationCallback;

    public:

        FloorSwitchCameraAnimator(InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                  Eegeo::VR::JumpPointsCameraController& vrCamera,
                                  InteriorCameraAnimationPositionProvider cameraPositionProvider,
                                  const Eegeo::dv3& cameraPosBase);

        ~FloorSwitchCameraAnimator();

        void Update(float dt);

        void SetCameraBasePosition(const Eegeo::dv3& cameraPosBase);

        void FloorAnimationStateChanged(InteriorsExplorer::InteriorsExplorerFloorAnimationState& state);
    };
}