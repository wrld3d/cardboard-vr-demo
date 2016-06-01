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
        
        
        UIQuad::UIQuad(
                       Eegeo::Rendering::Materials::TexturedUniformColoredMaterial& material,
                       Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                       Eegeo::Rendering::RenderableFilters& renderableFilters,
                       Eegeo::Rendering::GlBufferPool& glBufferPool,
                       const Eegeo::v2& dimension,
                       const Eegeo::dv3& ecefPosition,
                       const Eegeo::v2& uvMin,
                       const Eegeo::v2& uvMax,
                       const Eegeo::v4& initialColor,
                       const Eegeo::Rendering::LayerIds::Values renderLayer
                       )
        : m_Material(material)
        , m_VertexBindingPool(vertexBindingPool)
        , m_RenderableFilters(renderableFilters)
        , m_GlBufferPool(glBufferPool)
        , m_RenderLayer(renderLayer)
        , m_Renderable(NULL)
        {
            
            m_Dimension = Eegeo::v2(dimension);
            m_EcefPosition = Eegeo::dv3(ecefPosition);
            
            m_RenderableMesh = CreateUnlitQuadMesh(m_Dimension, uvMin, uvMax, *CreatePositionUvVertexLayout(), m_GlBufferPool);
            m_Renderable = CreateUIMeshRenderable(*m_RenderableMesh, m_Material, m_VertexBindingPool, m_EcefPosition, m_RenderLayer);
            
            m_RenderableFilters.AddRenderableFilter(*this);
        }

        
        UIQuad::~UIQuad()
        {
            m_RenderableFilters.RemoveRenderableFilter(*this);
            
            Eegeo_DELETE m_RenderableMesh;
            Eegeo_DELETE m_Renderable;
        }
        
        // IRenderableFilter interface
        void UIQuad::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
            
            if(m_Renderable->GetEcefPosition().SquareDistanceTo(renderCamera.GetEcefLocation()) < 1)
                return;
            
            m33 orientation = GetLookAtOrientationMatrix(renderCamera.GetEcefLocation().ToSingle(), m_Renderable->GetEcefPosition().ToSingle(), renderCamera.GetEcefLocation().ToSingle().Norm());
            m_Renderable->SetOrientationEcef(orientation);
            
            const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
            const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
            
            const Eegeo::m44& mvp = m_Renderable->CalcModelViewProjection(ecefCameraPosition, viewProjection);
            m_Renderable->SetModelViewProjection(mvp);
            
            renderQueue.EnqueueRenderable(m_Renderable);
            
        }
        
        void UIQuad::UpdateUVs(Eegeo::v2& min, Eegeo::v2& max)
        {
            Eegeo_DELETE m_RenderableMesh;
            Eegeo_DELETE m_Renderable;
            m_RenderableMesh = CreateUnlitQuadMesh(m_Dimension, min, max, *CreatePositionUvVertexLayout(), m_GlBufferPool);
            m_Renderable = CreateUIMeshRenderable(*m_RenderableMesh, m_Material, m_VertexBindingPool, m_EcefPosition, m_RenderLayer);
            
            
        }
    }
}
