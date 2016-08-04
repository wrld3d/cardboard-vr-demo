// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "RenderableBase.h"
#include "Quaternion.h"

namespace Eegeo
{
    namespace UI
    {
        class UIMeshRenderable : public Eegeo::Rendering::RenderableBase
        {
        public:
            UIMeshRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                             const Eegeo::dv3& ecefPosition,
                             const Eegeo::Rendering::Materials::IMaterial& material,
                             const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                             Eegeo::Rendering::Mesh& mesh,
                             const Eegeo::v4& initialColor,
                             const Eegeo::v3& initialScale,
                             bool depthTest,
                             bool alphaBlend
                             );
            
            virtual Eegeo::m44 CalcModelViewProjection(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection) const;
            
            virtual void Render(Eegeo::Rendering::GLState& glState) const;
            
            virtual void OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool);
            
            void SetOrientationEcef(const Eegeo::m33& orientationEcef) { m_orientationEcef = orientationEcef.ToM44(); }
            void SetColor(const Eegeo::v4 color) { m_color = color; }
            
            const Eegeo::v4& GetColor() const { return m_color; }
            
            const Eegeo::v3& GetScale() { return m_scale; }
            void SetScale(const Eegeo::v3& scale) { m_scale = scale; }
            
        private:
            Eegeo::Rendering::Mesh& m_mesh;
            Eegeo::m44 m_orientationEcef;
            Eegeo::v4 m_color;
            Eegeo::v3 m_scale;
        };
    }
}
