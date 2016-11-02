//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once
#include "Types.h"
#include "MapModule.h"
#include "VRRenderCamera.h"
#include "CameraFrustumStreamingVolume.h"

namespace Eegeo
{
    namespace VRCamera
    {
        class VRCameraStreamingController : protected Eegeo::NonCopyable
        {
        public:
            VRCameraStreamingController(const VRRenderCamera& vrRenderCamera,
                                        const Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                        const std::vector<double>& lodRefinementAltitudes,
                                        const Rendering::EnvironmentFlatteningService& environmentFlatteningService);
            ~VRCameraStreamingController();

            Eegeo::Streaming::IStreamingVolume& GetStreamingVolume() const;
            void UpdateStreamingVolume();
            
        private:
            Eegeo::Streaming::CameraFrustumStreamingVolume* m_pStreamingVolume;
            const VRRenderCamera& m_vrRenderCamera;
        };
    }
}
