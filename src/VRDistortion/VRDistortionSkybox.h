//
//  VRDistortionSkybox.h
//  SDKSamplesApp
//
//  Created by Ali on 4/6/16.
//
//

#ifndef VRDistortionSkybox_h
#define VRDistortionSkybox_h

#include "ColorShader.h"
#include "ColorMaterial.h"
#include "Rendering.h"
#include "IRenderableFilter.h"
#include "Modules.h"
#include "MeshRenderable.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            class VRDistortionSkybox : public Eegeo::Rendering::IRenderableFilter
            {
            private:
                Eegeo::Modules::Core::RenderingModule& m_renderingModule;
                Eegeo::Rendering::Shaders::ColorShader* m_Shader;
                Eegeo::Rendering::Materials::ColorMaterial* m_Material;
                Eegeo::Rendering::GlBufferPool& m_glBufferPool;
                Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
                Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
                Eegeo::Rendering::Renderables::MeshRenderable* m_pRenderable;
                Eegeo::Rendering::RenderableFilters& m_renderableFilters;
                Eegeo::v4 backgroundColor;
                
            public:
                VRDistortionSkybox(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
                                   Eegeo::Rendering::GlBufferPool& p_glBufferPool,
                                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& p_VertexBindingPool,
                                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& p_VertexLayoutPool,
                                   Eegeo::Rendering::RenderableFilters& p_RenderableFilters);
                virtual ~VRDistortionSkybox();
                void Start();
                void Update(float dt);
                void Draw();
                void Suspend();
                void UpdateSkyColor(Eegeo::v3 color);
                
                // IRenderableFilter interface
                void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
            };
            
        }
    }
}

#endif /* VRDistortionSkybox_h */
