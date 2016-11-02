//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCameraStreamingController.h"
#include "StreamingVolumeController.h"
#include "QuadTreeCube.h"

namespace Eegeo
{
    namespace VRCamera
    {
        VRCameraStreamingController::VRCameraStreamingController(const VRRenderCamera& vrRenderCamera,
                                                                 const Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                                 const std::vector<double>& lodRefinementAltitudes,
                                                                 const Rendering::EnvironmentFlatteningService& environmentFlatteningService)
        : m_vrRenderCamera(vrRenderCamera)
        {
            m_pStreamingVolume = Eegeo_NEW(Eegeo::Streaming::CameraFrustumStreamingVolume)(resourceCeilingProvider,
                                                                                           lodRefinementAltitudes,
                                                                                           Eegeo::Streaming::QuadTreeCube::MAX_DEPTH_TO_VISIT,
                                                                                           environmentFlatteningService);

            m_pStreamingVolume->setDeepestLevelForAltitudeLodRefinement(11);
            m_pStreamingVolume->SetForceMaximumRefinement(true);
        }

        VRCameraStreamingController::~VRCameraStreamingController()
        {
            Eegeo_DELETE m_pStreamingVolume;
        }

        Eegeo::Streaming::IStreamingVolume& VRCameraStreamingController::GetStreamingVolume() const
        {
            return *m_pStreamingVolume;
        }

        void VRCameraStreamingController::UpdateStreamingVolume()
        {
            Eegeo::Camera::CameraState cameraState(m_vrRenderCamera.GetCameraState());
            Eegeo::Camera::RenderCamera& renderCamera = m_vrRenderCamera.GetCamera();

            std::vector<Eegeo::Geometry::Plane> frustumPlanes(Eegeo::Geometry::Frustum::PLANES_COUNT);
            BuildFrustumPlanesFromViewProjection(frustumPlanes, renderCamera.GetViewProjectionMatrix());
            const double d = renderCamera.GetAltitude() * Eegeo::Streaming::StreamingVolumeController::CAMERA_ALTITUDE_TO_FAR_PLANE_DISTANCE_MULTIPLIER;
            const double cameraFarPlaneD = fmin(fmax(d, Eegeo::Streaming::StreamingVolumeController::MIN_STREAMING_FAR_PLANE_DISTANCE), frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d);
            frustumPlanes[Eegeo::Geometry::Frustum::PLANE_FAR].d = static_cast<float>(cameraFarPlaneD);

            //Workaround: added 100.0f to FOV to load textures for surroundings even when camera is not looking at it to fix interior loading crash.
            //m_pStreamingVolume->updateStreamingVolume(renderCamera.GetEcefLocation(), frustumPlanes, renderCamera.GetFOV());
            m_pStreamingVolume->updateStreamingVolume(renderCamera.GetEcefLocation(), frustumPlanes, renderCamera.GetFOV()+100.0f);
            m_pStreamingVolume->ResetVolume(cameraState.InterestPointEcef());
        }
    }
}
