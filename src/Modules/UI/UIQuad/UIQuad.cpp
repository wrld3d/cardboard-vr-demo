//
//  UIQuad.cpp
//  SDKSamplesApp
//
//  Created by Ali on 4/6/16.
//
//

#include "UIQuad.h"
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
#include "RenderCamera.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "EcefTangentBasis.h"
#include "VertexLayout.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        Eegeo::Rendering::VertexLayouts::VertexLayout* CreatePositionUvVertexLayout()
        {
            using namespace Eegeo::Rendering::VertexLayouts;
            VertexLayout* pLayout = new (VertexLayout)(sizeof(Rendering::VertexTypes::TexturedVertex));
            
            int positionOffset = offsetof(Rendering::VertexTypes::TexturedVertex, x);
            pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::Position, 3, GL_FLOAT,  positionOffset));
            
            int uvOffset = offsetof(Rendering::VertexTypes::TexturedVertex, u);
            pLayout->AddElement(VertexLayoutElement(Eegeo::Rendering::VertexSemanticId::UV, 2, GL_FLOAT, uvOffset));
            
            return pLayout;
        }
        
        Eegeo::Rendering::Mesh* CreateUnlitQuadMesh(const Eegeo::v2& dimensions, const Eegeo::v2& uv_min, const Eegeo::v2& uv_max, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
        {
            std::vector<Rendering::VertexTypes::TexturedVertex> boxVertices;
            std::vector<u16> triangleIndices;
            
            BuildQuad(dimensions/2.0f, uv_min, uv_max, boxVertices, triangleIndices);
            
            size_t vertexBufferSizeBytes = sizeof(Rendering::VertexTypes::TexturedVertex) * boxVertices.size();
            size_t indexBufferSizeBytes = sizeof(u16) * triangleIndices.size();
            
            return new (Eegeo::Rendering::Mesh)(
                                                vertexLayout,
                                                glBufferPool,
                                                boxVertices.data(),
                                                vertexBufferSizeBytes,
                                                triangleIndices.data(),
                                                indexBufferSizeBytes,
                                                static_cast<u32>(triangleIndices.size()),
                                                "UnlitQuadMesh"
                                                );
        }
        
        UIMeshRenderable* CreateUIMeshRenderable(Eegeo::Rendering::Mesh& mesh, Eegeo::Rendering::Materials::IMaterial& material, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool, const Eegeo::dv3 ecefPosition, const Eegeo::Rendering::LayerIds::Values renderLayer)
        {
            const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding =
            vertexBindingPool.GetVertexBinding(mesh.GetVertexLayout(), material.GetShader().GetVertexAttributes());
            
            const bool depthTest = true;
            const bool alphaBlend = true;
            
            UIMeshRenderable* pUnlitBoxRenderable = new UIMeshRenderable(renderLayer,
                                                                         ecefPosition,
                                                                         material,
                                                                         vertexBinding,
                                                                         mesh,
                                                                         Eegeo::Rendering::Colors::WHITE,
                                                                         Eegeo::v3::One(),
                                                                         depthTest,
                                                                         alphaBlend
                                                                         );
            
            return pUnlitBoxRenderable;
        }
        
        UIQuad::UIQuad(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
                       Eegeo::Rendering::GlBufferPool& p_glBufferPool,
                       Eegeo::Rendering::VertexLayouts::VertexBindingPool& p_VertexBindingPool,
                       Eegeo::Rendering::VertexLayouts::VertexLayoutPool& p_VertexLayoutPool,
                       Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                       Eegeo::Rendering::RenderableFilters& p_RenderableFilters,
                       const std::string& fileName,
                       const Eegeo::dv3 p_ecefPosition,
                       const Eegeo::v2& p_Dimension,
                       const Eegeo::v2& p_uvMin,
                       const Eegeo::v2& p_uvMax,
                       const Eegeo::v4& p_initialColor,
                       const Eegeo::Rendering::LayerIds::Values p_RenderLayer
                       ):
        m_renderingModule(p_RenderingModule),
        m_vertexBindingPool(p_VertexBindingPool),
        m_renderableFilters(p_RenderableFilters),
        m_textureFileLoader(textureFileLoader),
        m_RenderLayer(p_RenderLayer),
        m_pRenderable(NULL)
        {
            
            m_Dimension = Eegeo::v2(p_Dimension);
            m_ecefPosition = Eegeo::dv3(p_ecefPosition);

            m_textureInfo.textureId = 0;
            m_textureInfo.width = 0;
            m_textureInfo.height = 0;
            
            const bool generateMipmaps = true;
            bool success = m_textureFileLoader.LoadTexture(m_textureInfo, fileName, generateMipmaps);
            Eegeo_ASSERT(success, "failed to load texture");
            if (!success)
                return;
            
            m_Shader = Eegeo::Rendering::Shaders::TexturedUniformColoredShader::Create(m_renderingModule.GetShaderIdGenerator().GetNextId());
            m_Material = new (Eegeo::Rendering::Materials::TexturedUniformColoredMaterial) (
                                                                                            m_renderingModule.GetMaterialIdGenerator().GetNextId(),
                                                                                            "UIRectMaterial",
                                                                                            *m_Shader,
                                                                                            m_textureInfo.textureId,
                                                                                            p_initialColor);
            
             pRenderableMesh = CreateUnlitQuadMesh(p_Dimension, p_uvMin, p_uvMax, *CreatePositionUvVertexLayout(), m_renderingModule.GetGlBufferPool());
            
            m_pRenderable = CreateUIMeshRenderable(*pRenderableMesh, *m_Material, m_vertexBindingPool, p_ecefPosition, p_RenderLayer);
            
            m_renderableFilters.AddRenderableFilter(*this);
        }
        
        UIQuad::~UIQuad()
        {
            Eegeo::Rendering::RenderableFilters& platformRenderableFilters = m_renderingModule.GetRenderableFilters();
            platformRenderableFilters.RemoveRenderableFilter(*this);
            
            Eegeo_DELETE pRenderableMesh;
            Eegeo_DELETE m_pRenderable;
            Eegeo_DELETE m_Material;
            Eegeo_DELETE m_Shader;
        }
        
        // IRenderableFilter interface
        void UIQuad::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
            
            if(m_pRenderable->GetEcefPosition().SquareDistanceTo(renderCamera.GetEcefLocation()) < 1)
                return;
            
            m33 orientation = GetLookAtOrientationMatrix(renderCamera.GetEcefLocation().ToSingle(), m_pRenderable->GetEcefPosition().ToSingle(), renderCamera.GetEcefLocation().ToSingle().Norm());
            m_pRenderable->SetOrientationEcef(orientation);
            
            const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
            const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
            
            const Eegeo::m44& mvp = m_pRenderable->CalcModelViewProjection(ecefCameraPosition, viewProjection);
            m_pRenderable->SetModelViewProjection(mvp);
            
            renderQueue.EnqueueRenderable(m_pRenderable);
            
        }
        
        void UIQuad::UpdateUVs(Eegeo::v2& min, Eegeo::v2& max)
        {
            Eegeo_DELETE pRenderableMesh;
            Eegeo_DELETE m_pRenderable;
            pRenderableMesh = CreateUnlitQuadMesh(m_Dimension, min, max, *CreatePositionUvVertexLayout(), m_renderingModule.GetGlBufferPool());
            m_pRenderable = CreateUIMeshRenderable(*pRenderableMesh, *m_Material, m_vertexBindingPool, m_ecefPosition, m_RenderLayer);
            
        }
    }
}
