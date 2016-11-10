// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "TexturedUniformColoredShader.h"
#include "UITexturedUniformColoredMaterial.h"
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
            
            Eegeo::Rendering::Materials::UITexturedUniformColoredMaterial& m_material;
            Eegeo::Rendering::Mesh* m_pRenderableMesh;
            
            Eegeo::Rendering::VertexLayouts::VertexBindingPool& m_vertexBindingPool;
            Eegeo::Rendering::GlBufferPool& m_glBufferPool;
            
            UIMeshRenderable* m_pRenderable;
            
            Eegeo::m33 m_basisToEcef;
            
            Eegeo::v2 m_dimension;
            Eegeo::dv3 m_ecefPosition;
            const Eegeo::Rendering::LayerIds::Values m_renderLayer;
            
            std::string m_name;
            
        public:
            
            UIQuad(
                   const std::string& name,
                   Eegeo::Rendering::Materials::UITexturedUniformColoredMaterial& material,
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
            inline void SetEcefPosition(const Eegeo::dv3& ecefPosition){ m_pRenderable->SetEcefPosition(ecefPosition); }
            inline const dv3& GetEcefPosition() const { return m_pRenderable->GetEcefPosition(); }
            inline const Eegeo::m44& GetOrientationMatrix() { return m_pRenderable->GetOrientationEcef(); }
            inline const Eegeo::v3& GetScale() { return m_pRenderable->GetScale(); }
            inline void SetScale(const Eegeo::v3& scale) { m_pRenderable->SetScale(scale); }
            inline void SetColor(const Eegeo::v4& color) { m_pRenderable->SetColor(color); }
            inline const Eegeo::v4& GetColor() { return m_pRenderable->GetColor(); }
            inline void SetAlpha(float alpha) { m_pRenderable->SetAlpha(alpha); }
            inline const float GetAlpha() { return m_pRenderable->GetAlpha(); }

            // IUIRenderable interface
            virtual Eegeo::Rendering::RenderableBase& GetUpdatedRenderable(const Eegeo::Rendering::RenderContext& renderContext);
        };
        
    }
}

