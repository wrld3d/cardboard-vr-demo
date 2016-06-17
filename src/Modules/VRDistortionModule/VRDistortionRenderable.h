//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#ifndef __ExampleApp__VRDistortionRenderable__
#define __ExampleApp__VRDistortionRenderable__

#include "Rendering.h"
#include "MeshRenderable.h"
#include "VectorMathDecl.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionRenderable : public Eegeo::Rendering::Renderables::MeshRenderable
            {
            public:
                VRDistortionRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                       Eegeo::Rendering::Materials::IMaterial* pMaterial,
                                       const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                       Eegeo::Rendering::Mesh* pMesh)
                : MeshRenderable(layerId, Eegeo::dv3(), pMaterial, pMesh, vertexBinding)
                {}
                
                virtual void Render(Eegeo::Rendering::GLState& glState) const;
                
            };
        }
    }
}

#endif /* defined(__ExampleApp__VRDistortionRenderable__) */
