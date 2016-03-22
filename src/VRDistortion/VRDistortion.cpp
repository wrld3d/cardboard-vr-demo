//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//

#include <vector>
#include "Mesh.h"
#include "Quad.h"
#include "GlBufferPool.h"
#include "VertexLayout.h"
#include "VRDistortion.h"
#include "RenderContext.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "RenderableFilters.h"
#include "VertexBindingPool.h"
#include "ScreenProperties.h"
#include "GeometryHelpers.h"
#include "LayerIds.h"
#include "VRDistortionShader.h"
#include "VRDistortionMaterial.h"
#include "VRDistortionRenderable.h"
#include "VRDistortionRenderer.h"

#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            struct PositionUvVertex
            {
                float x;
                float y;
                float z;
                float u;
                float v;
            };
            
            inline PositionUvVertex MakePositionUvVertex(const Eegeo::v3& pos, const Eegeo::v2& uv)
            {
                PositionUvVertex v;
                v.x = pos.x;
                v.y = pos.y;
                v.z = pos.z;
                v.u = uv.x;
                v.v = uv.y;
                return v;
            }
            
            inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const Examples::GeometryHelpers::Vertex& v)
            {
                return MakePositionUvVertex(v.position, v.uv);
            }
            
            Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionUvVertexLayout()
            {
                using namespace Eegeo::Rendering::VertexLayouts;
                VertexLayout* pLayout = new (VertexLayout)(sizeof(PositionUvVertex));
                
                int positionOffset = offsetof(PositionUvVertex, x);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 3, GL_FLOAT,  positionOffset));
                
                int uvOffset = offsetof(PositionUvVertex, u);
                pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
                
                return pLayout;
            }
            
            
            VRDistortion::VRDistortion(
                                        const Eegeo::Rendering::ScreenProperties& screenProperties,
                                        Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                                        Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                        Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                                        Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                                        Eegeo::Rendering::RenderableFilters& renderableFilters,
                                        Eegeo::Rendering::GlBufferPool& glBufferPool)
            : m_screenProperties(screenProperties)
            ,m_vertexLayoutPool(vertexLayoutPool)
            ,m_vertexBindingPool(vertexBindingPool)
            ,m_shaderIdGenerator(shaderIdGenerator)
            ,m_materialIdGenerator(materialIdGenerator)
            ,m_renderableFilters(renderableFilters)
            ,m_glBufferPool(glBufferPool)
            ,m_pVRDistortionShader(NULL)
            ,m_pVRDistortionMaterial(NULL)
            ,m_pRenderable(NULL)
            ,m_pVRDistortionRenderer(NULL)
            ,m_pFBRenderTexture(NULL)
            {
                m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();
            }
            
            Eegeo::Rendering::Mesh* CreateUnlitDistortionMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
            {
                std::vector<Examples::GeometryHelpers::Vertex> boxVertices;
                std::vector<u16> triangleIndices;
                
                BuildDistortionMesh(boxVertices, triangleIndices, width, height, 1000);
                
                std::vector<PositionUvVertex> unlitVertices;
                
                std::transform(boxVertices.begin(), boxVertices.end(), std::back_inserter(unlitVertices), GeometryHelpersVertexToPositionUvVertex);
                
                size_t vertexBufferSizeBytes = sizeof(PositionUvVertex) * unlitVertices.size();
                size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
                
                return new (Eegeo::Rendering::Mesh)(
                                                    vertexLayout,
                                                    glBufferPool,
                                                    unlitVertices.data(),
                                                    vertexBufferSizeBytes,
                                                    triangleIndices.data(),
                                                    indexBufferSizeBytes,
                                                    static_cast<u32>(triangleIndices.size()),
                                                    "UnlitBoxMesh"
                                                    );
            }
            
            void VRDistortion::Initialize()
            {
                
                m_pFBRenderTexture = Eegeo_NEW(Eegeo::Rendering::FBRenderTexture)();
                m_pFBRenderTexture->InitRenderer(m_screenProperties.GetScreenWidth()*2.f, m_screenProperties.GetScreenHeight());
                
                
                m_pVRDistortionShader = VRDistortionShader::Create(m_shaderIdGenerator.GetNextId());
                
                m_pVRDistortionMaterial = Eegeo_NEW(VRDistortionMaterial)(m_materialIdGenerator.GetNextId(),
                                                                             "VRDistortionMaterial",
                                                                             *m_pVRDistortionShader,
                                                                             *m_pFBRenderTexture);
                
                Eegeo::Rendering::Mesh* pRenderableMesh = Eegeo::Rendering::Geometry::CreatePositionUVViewportQuad(m_glBufferPool, m_vertexLayoutPool);
              
                pRenderableMesh = CreateUnlitDistortionMesh(m_screenProperties.GetScreenWidth()*2.f, m_screenProperties.GetScreenHeight(), *m_pPositionUvVertexLayout, m_glBufferPool);
                
                const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout = pRenderableMesh->GetVertexLayout();
                const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttributes = m_pVRDistortionShader->GetVertexAttributes();
                const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = m_vertexBindingPool.GetVertexBinding(vertexLayout, vertexAttributes);
                
                m_pRenderable = Eegeo_NEW(VRDistortionRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                                                                         m_pVRDistortionMaterial,
                                                                         vertexBinding,
                                                                         pRenderableMesh);
                
                m_pVRDistortionRenderer = Eegeo_NEW(VRDistortionRenderer)(*m_pRenderable);
                
            }
            
            void VRDistortion::Suspend()
            {
                
                Eegeo_DELETE m_pVRDistortionRenderer;
                m_pVRDistortionRenderer = NULL;
                
                Eegeo_DELETE m_pRenderable;
                m_pRenderable = NULL;
                
                Eegeo_DELETE m_pVRDistortionMaterial;
                m_pVRDistortionMaterial = NULL;
                
                Eegeo_DELETE m_pVRDistortionShader;
                m_pVRDistortionShader = NULL;
                
                Eegeo_DELETE m_pFBRenderTexture;
                m_pFBRenderTexture = NULL;
            }
            
            
            void VRDistortion::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                if (m_screenProperties.GetScreenWidth() != screenProperties.GetScreenWidth() ||
                    m_screenProperties.GetScreenHeight() != screenProperties.GetScreenHeight())
                {
                    m_screenProperties = screenProperties;
                    
                    Suspend();
                    Initialize();
                }
            }
            
            void VRDistortion::BeginRendering()
            {
                
                EXAMPLE_LOG("RenderTexture: Start Rendering");
                m_pFBRenderTexture->BeginRendering();
                Eegeo::Helpers::GLHelpers::ClearBuffers();
            }
            
            void VRDistortion::RegisterRenderable()
            {
                m_renderableFilters.AddRenderableFilter(*m_pVRDistortionRenderer);
                
            }
            
            void VRDistortion::UnRegisterRenderable()
            {
                m_renderableFilters.RemoveRenderableFilter(*m_pVRDistortionRenderer);
            }
            
            
        }
    }
}

