//
//  UIQuad.h
//  SDKSamplesApp
//
//  Created by Ali on 4/6/16.
//
//

#pragma once

#include "TexturedUniformColoredShader.h"
#include "TexturedUniformColoredMaterial.h"
#include "Rendering.h"
#include "IRenderableFilter.h"
#include "Modules.h"
#include "UIMeshRenderable.h"
#include "GLHelpers.h"
#include "ITextureFileLoader.h"
#include "UIGeometryHelpers.h"

namespace Eegeo
{
    namespace UI
    {
        class UIQuad : public Eegeo::Rendering::IRenderableFilter
        {
        private:
            Eegeo::Modules::Core::RenderingModule& m_renderingModule;
            Eegeo::Rendering::Shaders::TexturedUniformColoredShader* m_Shader;
            Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* m_Material;
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
            UIMeshRenderable* m_pRenderable;
            Eegeo::Rendering::RenderableFilters& m_renderableFilters;
            Helpers::GLHelpers::TextureInfo m_textureInfo;
            Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
            Eegeo::m33 m_basisToEcef;
            
            Eegeo::Rendering::Mesh* pRenderableMesh;
            Eegeo::v2 m_Dimension;
            Eegeo::dv3 m_ecefPosition;
            const Eegeo::Rendering::LayerIds::Values m_RenderLayer;
            
        public:
            UIQuad(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
                   Eegeo::Rendering::GlBufferPool& p_glBufferPool,
                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& p_VertexBindingPool,
                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& p_VertexLayoutPool,
                   Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                   Eegeo::Rendering::RenderableFilters& p_RenderableFilters,
                   const std::string& fileName,
                   const Eegeo::dv3 p_ecefPosition,
                   const Eegeo::v2& p_Dimension,
                   const Eegeo::v2& p_uvMin = Eegeo::v2::Zero(),
                   const Eegeo::v2& p_uvMax = Eegeo::v2::One(),
                   const Eegeo::v4& p_initialColor = Eegeo::v4::One(),
                   const Eegeo::Rendering::LayerIds::Values p_RenderLayer = Eegeo::Rendering::LayerIds::Values::AfterWorld
                   );
            virtual ~UIQuad();
            inline void SetEcefPosition(const Eegeo::dv3& ecefPosition){ m_pRenderable->SetEcefPosition(ecefPosition); }
            inline const dv3& GetEcefPosition() const { return m_pRenderable->GetEcefPosition(); }
            inline Eegeo::v3 GetScale() { return m_pRenderable->GetScale(); }
            inline void SetScale(Eegeo::v3 p_scale) { m_pRenderable->SetScale(p_scale); }
            inline void SetColor(const Eegeo::v4& color) { m_pRenderable->SetColor(color); }
            
            void UpdateUVs(Eegeo::v2& min, Eegeo::v2& max);
            
            // IRenderableFilter interface
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        };
        
    }
}

