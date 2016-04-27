//
//  SkyboxModule.cpp
//  SDKSamplesApp
//
//  Created by Ali on 4/6/16.
//
//

#include "SkyboxModule.h"
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
    namespace Skybox
    {
        SkyboxModule::SkyboxModule(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
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
            backgroundColor = Eegeo::v4(0.0f/255.f,24.0f/255.f,72.0f/255.f,1.0f);
        }
        
        SkyboxModule::~SkyboxModule()
        {
            Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
            platformRenderableFilters.RemoveRenderableFilter(*this);
            
            Eegeo_DELETE m_Material;
            Eegeo_DELETE m_Shader;
        }
        
        void SkyboxModule::Start()
        {
            m_Shader = Eegeo::Rendering::Shaders::ColorShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
            m_Material = new (Eegeo::Rendering::Materials::ColorMaterial) (
                                                                           m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                           "SkyboxMat",
                                                                           *m_Shader,
                                                                           backgroundColor
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
        
        void SkyboxModule::UpdateSkyColor(Eegeo::v3 color)
        {
            backgroundColor.Set(color.GetX(), color.GetY(), color.GetZ(), 1.0f);
            m_Material->SetColor(backgroundColor);
        }
        
        void SkyboxModule::Update(float dt){}
        
        void SkyboxModule::Draw()
        {}
        
        void SkyboxModule::Suspend()
        {}
        
        // IRenderableFilter interface
        void SkyboxModule::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            renderQueue.EnqueueRenderable(m_pRenderable);
        }
    }
}