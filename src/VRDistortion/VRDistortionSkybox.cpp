//
//  VRDistortionSkybox.cpp
//  SDKSamplesApp
//
//  Created by Ali on 4/6/16.
//
//

#include "VRDistortionSkybox.h"
#include "RenderingModule.h"
#include "RenderableFilters.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "Colors.h"
#include "LayerIds.h"
#include "Mesh.h"
#include "Quad.h"
#include "VertexBindingPool.h"
#include "RenderContext.h"
#include "RenderQueue.h"



namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            VRDistortionSkybox::VRDistortionSkybox(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
                                                   Eegeo::Rendering::GlBufferPool& p_glBufferPool,
                                                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& p_VertexBindingPool,
                                                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& p_VertexLayoutPool,
                                                   Eegeo::Rendering::RenderableFilters& p_RenderableFilters):
            m_renderingModule(p_RenderingModule),
            m_glBufferPool(p_glBufferPool),
            m_vertexLayoutPool(p_VertexLayoutPool),
            m_vertexBindingPool(p_VertexBindingPool),
            m_renderableFilters(p_RenderableFilters),
            m_pRenderable(NULL)
            {
                
            }
            
            VRDistortionSkybox::~VRDistortionSkybox()
            {
                Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
                platformRenderableFilters.RemoveRenderableFilter(*this);
                
                delete m_Material;
                delete m_Shader;
            }
            
            void VRDistortionSkybox::Start()
            {
                m_Shader = Eegeo::Rendering::Shaders::ColorShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
                m_Material = new (Eegeo::Rendering::Materials::ColorMaterial) (
                                                                               m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                               "SkyboxMat",
                                                                               *m_Shader,
                                                                               Eegeo::v4(0.0f/255.f,24.0f/255.f,72.0f/255.f,1.0f)
                                                                               );
                
                Eegeo::Rendering::Mesh* pRenderableMesh = Eegeo::Rendering::Geometry::CreatePositionQuad(1.0f, m_glBufferPool, m_vertexLayoutPool);
                const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout = pRenderableMesh->GetVertexLayout();
                const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttributes = m_Shader->GetVertexAttributes();
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = m_vertexBindingPool.GetVertexBinding(vertexLayout, vertexAttributes);
                
                m_pRenderable = Eegeo_NEW(Eegeo::Rendering::Renderables::MeshRenderable)(Eegeo::Rendering::LayerIds::BeforeWorldTranslucency,
                                                                         Eegeo::dv3(),
                                                                         m_Material,
                                                                         pRenderableMesh,
                                                                         vertexBinding
                                                                         );
                m_renderableFilters.AddRenderableFilter(*this);
            }
            
            void VRDistortionSkybox::UpdateSkyColor(Eegeo::v3 color)
            {
                Eegeo::v4 newClr = Eegeo::v4(color, 1.0f); //Full aplha
                m_Material->SetColor(newClr);
            }
            
            void VRDistortionSkybox::Update(float dt)
            {

            }
            
            void VRDistortionSkybox::Draw()
            {}
            
            void VRDistortionSkybox::Suspend()
            {}
            
            // IRenderableFilter interface
            void VRDistortionSkybox::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
            {
                renderQueue.EnqueueRenderable(m_pRenderable);
            }
        }
    }
}