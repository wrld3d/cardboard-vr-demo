//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once
#include "Types.h"
#include "VRRenderCamera.h"
#include "VectorMathDecl.h"
#include "Space.h"
#include "IInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "VRCameraPositionSpline.h"
#include "CameraState.h"
#include "IVRHeadTracker.h"

#include "Modules/UI/Animations/IDv3Animateable.h"

namespace Eegeo
{
    namespace VR
    {
        
        class JumpPointsCameraController : public VRCamera::VRRenderCamera, public Eegeo::UI::Animations::IDv3Animateable
        {

        public:
            JumpPointsCameraController(float screenWidth, float screenHeight, float eyeDistance);

            // on animation update
            virtual void OnDv3Updated(const Eegeo::dv3& delta);
        };
    }
}
