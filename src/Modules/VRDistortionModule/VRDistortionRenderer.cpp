//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#include "RenderContext.h"
#include "RenderQueue.h"
#include "VRDistortionRenderable.h"
#include "VRDistortionRenderer.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            VRDistortionRenderer::VRDistortionRenderer(VRDistortionRenderable& renderable)
            : m_renderable(renderable)
            {    
            }
            
            void VRDistortionRenderer::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext,
                                                          Eegeo::Rendering::RenderQueue& renderQueue)
            {
                renderQueue.EnqueueRenderable(m_renderable);
            }
        }
    }
}