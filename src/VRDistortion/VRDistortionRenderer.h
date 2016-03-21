//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#ifndef __ExampleApp__VRDistortionRenderer__
#define __ExampleApp__VRDistortionRenderer__

#include "Types.h"
#include "Rendering.h"
#include "IRenderableFilter.h"
#include "VRDistortionIncludes.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionRenderer : Eegeo::NonCopyable, public Eegeo::Rendering::IRenderableFilter
            {
                
            public:
                VRDistortionRenderer(VRDistortionRenderable& renderable);
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
            private:
                VRDistortionRenderable& m_renderable;
                
            };
            
        }
    }
}

#endif /* defined(__ExampleApp__VRDistortionRenderer__) */
