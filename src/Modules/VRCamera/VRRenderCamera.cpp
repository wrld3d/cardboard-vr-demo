//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRRenderCamera.h"
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
    namespace VRCamera
    {
        
        Eegeo::dv3 VRRenderCamera::GetEcefInterestPoint() const
        {
            dv3 ecefPosition = m_ecefPosition;
            return ecefPosition.Normalise() * Eegeo::Space::EarthConstants::Radius;
        }
        
        double VRRenderCamera::GetAltitudeAboveSeaLevel() const
        {
            return Space::SpaceHelpers::GetAltitude(m_pRenderCamera->GetEcefLocation());
        }
        
        void VRRenderCamera::SetProjectionMatrix(Eegeo::m44& projection)
        {
            m_pRenderCamera->SetProjectionMatrix(projection);
        }
        
        Camera::CameraState VRRenderCamera::GetCameraState() const
        {
            return Camera::CameraState(m_pRenderCamera->GetEcefLocation(),
                                       GetEcefInterestPoint(),
                                       m_pRenderCamera->GetViewMatrix(),
                                       m_pRenderCamera->GetProjectionMatrix());
        }

        const Eegeo::VRCamera::VRCameraState& VRRenderCamera::GetVRCameraState()
        {
            UpdateFromPose(-1.f);
            Camera::CameraState leftCameraState = GetCameraState();

            UpdateFromPose(1.f);
            Camera::CameraState rightCameraState = GetCameraState();

            m_cachedVRState = VRCameraState(m_pRenderCamera->GetEcefLocation(),
                                            leftCameraState,
                                            rightCameraState,
                                            GetOrientation(),
                                            GetCameraOrientation(),
                                            GetHeadTrackerOrientation());

            return m_cachedVRState;
        }

        m33& VRRenderCamera::GetOrientation()
        {
            return m_currentOrientation;
        }
        
        void VRRenderCamera::UpdateFromPose(float eyeDistanceMultiplier)
        {
            m_ecefPosition = m_pRenderCamera->GetEcefLocation();
            m33 orientationMatrix;
            m33::Mul(orientationMatrix, m_orientation, m_headTrackerOrientation);
            
            v3 eyeOffsetModified = dv3::ToSingle(m_ecefPosition.Norm() * m_eyeDistance * eyeDistanceMultiplier);
            v3 rotatedEyeOffset = v3::Mul(eyeOffsetModified, orientationMatrix);
            
            m_currentOrientation = Eegeo::m33(orientationMatrix);
            
            float near, far;
            GetNearFarPlaneDistances(near,far);
            
            dv3 targetPos(m_ecefPosition.x + rotatedEyeOffset.x, m_ecefPosition.y + rotatedEyeOffset.y, m_ecefPosition.z + rotatedEyeOffset.z);
            
            m_pRenderCamera->SetOrientationMatrix(orientationMatrix);
            m_pRenderCamera->SetEcefLocation(targetPos);
            m_pRenderCamera->SetProjection(0.7f, near*m_nearMultiplier, far);
            
            
        }
        
        void VRRenderCamera::SetEcefPosition(const Eegeo::dv3& ecef)
        {
            m_ecefPosition = ecef;
            m_pRenderCamera->SetEcefLocation(m_ecefPosition);
        }
        
        void VRRenderCamera::SetStartLatLongAltitude(const Eegeo::Space::LatLongAltitude& eyePos, float heading)
        {
            m_ecefPosition = eyePos.ToECEF();
            
            Space::EcefTangentBasis tangentBasis;
            Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(m_ecefPosition, heading, tangentBasis);
            
            m_orientation.SetRow(0, tangentBasis.GetRight());
            m_orientation.SetRow(1, tangentBasis.GetUp());
            m_orientation.SetRow(2, -tangentBasis.GetForward());

            m33 orientationMatrix;
            m33::Mul(orientationMatrix, m_orientation, m_headTrackerOrientation);
            m_currentOrientation = Eegeo::m33(orientationMatrix);

            m_pRenderCamera->SetOrientationMatrix(m_currentOrientation);
            m_pRenderCamera->SetEcefLocation(m_ecefPosition);
        }
        
        void VRRenderCamera::SetStartPositionAndOrientation(const Eegeo::dv3& position, const Eegeo::m33& orientation)
        {
            m_pRenderCamera->SetEcefLocation(position);
            m_orientation = orientation;
        }
        
        void VRRenderCamera::Update(float dt)
        {
        }
        
        void VRRenderCamera::SetCameraOrientation(const Eegeo::m33& orientation)
        {
            m_orientation = orientation;
        }
        
        void VRRenderCamera::GetNearFarPlaneDistances(float& out_near, float& out_far)
        {
            double cameraAltitude = GetAltitudeAboveSeaLevel();
            double approxTerrainAltitude = 100;
            double approxTerrainAltitudeDelta = approxTerrainAltitude -100;
            
            const double ClipPlaneThresholdAltitude = 15000.0;
            Camera::CameraHelpers::GetAltitudeInterpolatedNearFar(cameraAltitude, approxTerrainAltitude, approxTerrainAltitudeDelta, ClipPlaneThresholdAltitude, out_near, out_far);
  
            
        }

        void VRRenderCamera::UpdateHeadOrientation(const float headTansform[])
        {
            Eegeo::v3 right = Eegeo::v3(headTansform[0],headTansform[4],headTansform[8]);
            Eegeo::v3 up = Eegeo::v3(headTansform[1],headTansform[5],headTansform[9]);
            Eegeo::v3 forward = Eegeo::v3(-headTansform[2],-headTansform[6],-headTansform[10]);
            m_headTrackerOrientation.SetRow(0, right);
            m_headTrackerOrientation.SetRow(1, up);
            m_headTrackerOrientation.SetRow(2, forward);
        }
            
    }
}
