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
            Eegeo::Rendering::GlBufferPool& m_glBufferPool;
            Eegeo::Rendering::VertexLayouts::VertexLayoutPool& m_vertexLayoutPool;
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
            UIMeshRenderable* m_pRenderable;
            Eegeo::Rendering::RenderableFilters& m_renderableFilters;
            Helpers::GLHelpers::TextureInfo m_textureInfo;
            Eegeo::Helpers::ITextureFileLoader& m_textureFileLoader;
            float test;
            Eegeo::dv3 m_ecefPosition;
            Eegeo::m33 m_basisToEcef;
            Eegeo::v2 m_Dimension;
            Eegeo::v2 m_uvMin;
            Eegeo::v2 m_uvMax;
            
        public:
            UIQuad(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
                   Eegeo::Rendering::GlBufferPool& p_glBufferPool,
                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& p_VertexBindingPool,
                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& p_VertexLayoutPool,
                   Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                   Eegeo::Rendering::RenderableFilters& p_RenderableFilters,
                   Eegeo::dv3& p_ecefPosition,
                   Eegeo::v2& p_Dimension
                   );
            UIQuad(Eegeo::Modules::Core::RenderingModule& p_RenderingModule,
                   Eegeo::Rendering::GlBufferPool& p_glBufferPool,
                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& p_VertexBindingPool,
                   Eegeo::Rendering::VertexLayouts::VertexLayoutPool& p_VertexLayoutPool,
                   Eegeo::Helpers::ITextureFileLoader& textureFileLoader,
                   Eegeo::Rendering::RenderableFilters& p_RenderableFilters,
                   Eegeo::dv3& p_ecefPosition,
                   Eegeo::v2& p_Dimension,
                   Eegeo::v2& p_uvMin,
                   Eegeo::v2& p_uvMax
                   );
            virtual ~UIQuad();
            void Start();
            void Update(float dt);
            void Draw();
            void Suspend();
            
            // IRenderableFilter interface
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
        };
        
    }
}

