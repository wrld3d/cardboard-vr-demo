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
#include "IUIRenderable.h"

namespace Eegeo
{
    namespace UI
    {
        class UIQuad : public IUIRenderable
        {
        private:
            
            Eegeo::Rendering::Materials::TexturedUniformColoredMaterial& m_Material;
            Eegeo::Rendering::Mesh* m_RenderableMesh;
            
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_VertexBindingPool;
            Eegeo::Rendering::GlBufferPool& m_GlBufferPool;
            
            UIMeshRenderable* m_Renderable;
            
            Eegeo::m33 m_basisToEcef;
            
            Eegeo::v2 m_Dimension;
            Eegeo::dv3 m_EcefPosition;
            const Eegeo::Rendering::LayerIds::Values m_RenderLayer;
            
            std::string m_Name;
            
        public:
            
            UIQuad(
                   const std::string& name,
                   Eegeo::Rendering::Materials::TexturedUniformColoredMaterial& material,
                   Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool,
                   Eegeo::Rendering::GlBufferPool& glBufferPool,
                   const Eegeo::v2& dimension,
                   const Eegeo::v2& uvMin = Eegeo::v2::Zero(),
                   const Eegeo::v2& uvMax = Eegeo::v2::One(),
                   const Eegeo::dv3& ecefPosition = Eegeo::v3::One(),
                   const Eegeo::v4& initialColor = Eegeo::v4::One(),
                   const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::Values::AfterWorld
                   );
            
            virtual ~UIQuad();
            inline void SetEcefPosition(const Eegeo::dv3& ecefPosition){ m_Renderable->SetEcefPosition(ecefPosition); }
            inline const dv3& GetEcefPosition() const { return m_Renderable->GetEcefPosition(); }
            inline const Eegeo::v3& GetScale() { return m_Renderable->GetScale(); }
            inline void SetScale(const Eegeo::v3& p_scale) { m_Renderable->SetScale(p_scale); }
            inline void SetColor(const Eegeo::v4& color) { m_Renderable->SetColor(color); }
            inline const Eegeo::v4& GetColor() { return m_Renderable->GetColor(); }

            // IUIRenderable interface
            virtual Eegeo::Rendering::RenderableBase& GetUpdatedRenderable(const Eegeo::Rendering::RenderContext& renderContext);
        };
        
    }
}

