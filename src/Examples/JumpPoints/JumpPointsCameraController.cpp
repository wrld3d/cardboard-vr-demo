//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "JumpPointsCameraController.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "SpaceHelpers.h"
#include "EcefTangentBasis.h"
#include "Quaternion.h"
#include "EarthConstants.h"
#include "MathFunc.h"
#include "IVRHeadTracker.h"
#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        JumpPointsCameraController::JumpPointsCameraController(float screenWidth, float screenHeight, float eyeDistance)
        : VRCamera::VRRenderCamera(screenWidth, screenHeight, eyeDistance)
        {
        }

        void JumpPointsCameraController::OnDv3Updated(const Eegeo::dv3& delta)
        {
            SetEcefPosition(delta);
        }
    }
}
