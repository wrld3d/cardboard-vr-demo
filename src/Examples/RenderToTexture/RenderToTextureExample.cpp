// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <vector>
#include "RenderTexture.h"
#include "RenderContext.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "RenderableFilters.h"
#include "GlBufferPool.h"
#include "VertexBindingPool.h"
#include "Mesh.h"
#include "VertexLayout.h"
#include "PostProcessVignetteShader.h"
#include "PostProcessVignetteMaterial.h"
#include "PostProcessVignetteRenderer.h"
#include "PostProcessVignetteRenderable.h"
#include "Quad.h"
#include "RenderToTextureExample.h"
#include "ScreenProperties.h"
#include "GeometryHelpers.h"

namespace Examples
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
    
    inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const GeometryHelpers::Vertex& v)
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


    
    //Give the effect a 10 frames per second intensity update to give it an old-timey movie vibe...
    const float RenderToTextureExample::SecondsBetweenEffectUpdates = 0.1f;
    
    RenderToTextureExample::RenderToTextureExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController,
                                                   const Eegeo::Rendering::ScreenProperties& screenProperties,
                                                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& vertexLayoutPool,
                                                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                                                   Eegeo::Rendering::Shaders::ShaderIdGenerator& shaderIdGenerator,
                                                   Eegeo::Rendering::Materials::MaterialIdGenerator& materialIdGenerator,
                                                   Eegeo::Rendering::RenderableFilters& renderableFilters,
                                                   Eegeo::Rendering::GlBufferPool& glBufferPool)
    : GlobeCameraExampleBase(pCameraController, cameraTouchController)
    , m_screenProperties(screenProperties)
    ,m_vertexLayoutPool(vertexLayoutPool)
    ,m_vertexBindingPool(vertexBindingPool)
    ,m_shaderIdGenerator(shaderIdGenerator)
    ,m_materialIdGenerator(materialIdGenerator)
    ,m_renderableFilters(renderableFilters)
    ,m_glBufferPool(glBufferPool)
    ,m_pVignetteShader(NULL)
    ,m_pVignetteMaterial(NULL)
    ,m_pRenderable(NULL)
    ,m_pVignetteRenderer(NULL)
    ,m_pFBRenderTexture(NULL)
    ,m_secondsSinceLastEffectUpate(0.f)
    {
        m_pPositionUvVertexLayout = CreatePositionUvVertexLayout();
        
    }
    
    
    
    Eegeo::Rendering::Mesh* CreateUnlitBoxMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
    {
        Eegeo::v3 halfDimensions(width, height, width/2);
        std::vector<GeometryHelpers::Vertex> boxVertices;
        std::vector<u16> triangleIndices;
        
        BuildBox(halfDimensions, boxVertices, triangleIndices);
        
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
   
    Eegeo::Rendering::Mesh* CreateUnlitDistortionMesh(float width, float height, const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout, Eegeo::Rendering::GlBufferPool& glBufferPool)
    {
//        Eegeo::v3 halfDimensions(width, height, width/2);
        std::vector<GeometryHelpers::Vertex> boxVertices;
        std::vector<u16> triangleIndices;
        
        BuildDistortionMesh(boxVertices, triangleIndices, width, height);
        
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
    
    void RenderToTextureExample::Start()
    {
        // Allocate a full screen sized texture to render into, with depth and stencil attachments.
        //
        // This example assumes that the hardware is capable of allocating a RenderBuffer with a colour,
        // depth and stencil attachment, which should always be the case for iOS.
        //
        
        const bool needsDepthStencilBuffers = true;
        m_pRenderTexture = Eegeo_NEW(Eegeo::Rendering::RenderTexture)(static_cast<u32>(m_screenProperties.GetScreenWidth()),
                                                                      static_cast<u32>(m_screenProperties.GetScreenHeight()),
                                                                      needsDepthStencilBuffers);
        
        m_pFBRenderTexture = Eegeo_NEW(Eegeo::Rendering::FBRenderTexture)();
        m_pFBRenderTexture->InitRenderer(m_screenProperties.GetScreenWidth()*2.f, m_screenProperties.GetScreenHeight());
        
        
        m_pVignetteShader = PostProcessVignetteShader::Create(m_shaderIdGenerator.GetNextId());
        
        m_pVignetteMaterial = Eegeo_NEW(PostProcessVignetteMaterial)(m_materialIdGenerator.GetNextId(),
                                                                     "PostProcessVignetteMaterial",
                                                                     *m_pVignetteShader,
                                                                     *m_pRenderTexture,
                                                                     *m_pFBRenderTexture);
        
        Eegeo::Rendering::Mesh* pRenderableMesh = Eegeo::Rendering::Geometry::CreatePositionUVViewportQuad(m_glBufferPool, m_vertexLayoutPool);
        //Uncomment below to load box mesh
//        pRenderableMesh = CreateUnlitBoxMesh(0.45f, 0.45f, *m_pPositionUvVertexLayout, m_glBufferPool);
        //Uncomment below to load distortion mesh
//        pRenderableMesh = CreateUnlitDistortionMesh(m_screenProperties.GetScreenWidth(), m_screenProperties.GetScreenHeight(), *m_pPositionUvVertexLayout, m_glBufferPool);
                pRenderableMesh = CreateUnlitDistortionMesh(100, 100, *m_pPositionUvVertexLayout, m_glBufferPool);
        
        const Eegeo::Rendering::VertexLayouts::VertexLayout& vertexLayout = pRenderableMesh->GetVertexLayout();
        const Eegeo::Rendering::VertexLayouts::VertexAttribs& vertexAttributes = m_pVignetteShader->GetVertexAttributes();
        const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = m_vertexBindingPool.GetVertexBinding(vertexLayout, vertexAttributes);
        
        m_pRenderable = Eegeo_NEW(PostProcessVignetteRenderable)(Eegeo::Rendering::LayerIds::AfterWorld,
                                                                 m_pVignetteMaterial,
                                                                 vertexBinding,
                                                                 pRenderableMesh);
        
        m_pVignetteRenderer = Eegeo_NEW(PostProcessVignetteRenderer)(*m_pRenderable);
        
        m_renderableFilters.AddRenderableFilter(*m_pVignetteRenderer);
        
        UpdateEffect();
        
        //glDisable(GL_CULL_FACE);
    }
    
    void RenderToTextureExample::Suspend()
    {
        m_renderableFilters.RemoveRenderableFilter(*m_pVignetteRenderer);
        
        Eegeo_DELETE m_pVignetteRenderer;
        m_pVignetteRenderer = NULL;
        
        Eegeo_DELETE m_pRenderable;
        m_pRenderable = NULL;
        
        Eegeo_DELETE m_pVignetteMaterial;
        m_pVignetteMaterial = NULL;
        
        Eegeo_DELETE m_pVignetteShader;
        m_pVignetteShader = NULL;
        
        Eegeo_DELETE m_pFBRenderTexture;
        m_pFBRenderTexture = NULL;
    }
    
    void RenderToTextureExample::EarlyUpdate(float dt)
    {
        GlobeCameraExampleBase::EarlyUpdate(dt);
    }
    
    void RenderToTextureExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        if (m_screenProperties.GetScreenWidth() != screenProperties.GetScreenWidth() ||
            m_screenProperties.GetScreenHeight() != screenProperties.GetScreenHeight())
        {
            m_screenProperties = screenProperties;
            // recreate resources
            Suspend();
            Start();
        }
        GlobeCameraExampleBase::NotifyScreenPropertiesChanged(screenProperties);
    }
    
    void RenderToTextureExample::PreWorldDraw()
    {
        // Before the world is rendered, we should switch to rendering into our texture...
        m_pRenderTexture->BeginRendering();
        
//        Eegeo::Helpers::GLHelpers::ClearBuffers();
        
    }
    
    void RenderToTextureExample::Update(float dt)
    {
        m_secondsSinceLastEffectUpate += dt;
        if (m_secondsSinceLastEffectUpate > SecondsBetweenEffectUpdates)
        {
            UpdateEffect();
            m_secondsSinceLastEffectUpate = 0.f;
        }
        
    }
    
    void RenderToTextureExample::UpdateEffect()
    {
        // Set the vignette effect data for this frame (the colour and a radial intensity change)...
        m_pRenderable->SetVignetteColour(Eegeo::v3(1.0f, 1.0f, 1.0f));
    }

}

