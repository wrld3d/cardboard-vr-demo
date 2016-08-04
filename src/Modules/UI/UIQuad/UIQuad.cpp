// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

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
                       const std::string& name,
                       Eegeo::Rendering::Materials::UITexturedUniformColoredMaterial& material,
                       Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                       Eegeo::Rendering::GlBufferPool& glBufferPool,
                       const Eegeo::v2& dimension,
                       const Eegeo::v2& uvMin,
                       const Eegeo::v2& uvMax,
                       const Eegeo::dv3& ecefPosition,
                       const Eegeo::v4& initialColor,
                       const Eegeo::Rendering::LayerIds::Values renderLayer
                       )
        : m_material(material)
        , m_vertexBindingPool(vertexBindingPool)
        , m_glBufferPool(glBufferPool)
        , m_renderLayer(renderLayer)
        , m_pRenderable(NULL)
        {
            m_name = name;
            
            m_dimension = Eegeo::v2(dimension);
            m_ecefPosition = Eegeo::dv3(ecefPosition);
            
            m_pRenderableMesh = CreateUnlitQuadMesh(m_dimension, uvMin, uvMax, *CreatePositionUvVertexLayout(), m_glBufferPool);
            m_pRenderable = CreateUIMeshRenderable(*m_pRenderableMesh, m_material, m_vertexBindingPool, m_ecefPosition, m_renderLayer);
            
            SetItemShouldRender(true);
        }
        
        UIQuad::~UIQuad()
        {
            
            EXAMPLE_LOG("logs:: deleting quad: %s", m_name.c_str());
            
            Eegeo_DELETE m_pRenderableMesh;
            Eegeo_DELETE m_pRenderable;
        }
        
        // IRenderableFilter interface
        Eegeo::Rendering::RenderableBase& UIQuad::GetUpdatedRenderable(const Eegeo::Rendering::RenderContext& renderContext)
        {
            const Eegeo::Camera::RenderCamera& renderCamera = renderContext.GetRenderCamera();
            
            m33 orientation = GetLookAtOrientationMatrix(renderCamera.GetEcefLocation().ToSingle(), m_pRenderable->GetEcefPosition().ToSingle(), renderCamera.GetEcefLocation().ToSingle().Norm());
            m_pRenderable->SetOrientationEcef(orientation);
            
            const Eegeo::m44& viewProjection = renderCamera.GetViewProjectionMatrix();
            const Eegeo::dv3& ecefCameraPosition = renderCamera.GetEcefLocation();
            
            const Eegeo::m44& mvp = m_pRenderable->CalcModelViewProjection(ecefCameraPosition, viewProjection);
            m_pRenderable->SetModelViewProjection(mvp);
            
            return *m_pRenderable;
        }
    }
}
