// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "UIMeshRenderable.h"
#include "RenderContext.h"
#include "RenderCamera.h"
#include "MathsHelpers.h"
#include "Mesh.h"
#include "VertexBindingPool.h"
#include "IMaterial.h"
#include "Shader.h"
#include "EnvironmentFlatteningService.h"

namespace Eegeo
{
    namespace UI
    {
        UIMeshRenderable::UIMeshRenderable(Eegeo::Rendering::LayerIds::Values layerId,
                                           const Eegeo::dv3& ecefPosition,
                                           const Eegeo::Rendering::Materials::IMaterial& material,
                                           const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding,
                                           Eegeo::Rendering::Mesh& mesh,
                                           const Eegeo::v4& initialColor,
                                           const Eegeo::v3& initialScale,
                                           bool depthTest,
                                           bool alphaBlend)
        : Eegeo::Rendering::RenderableBase(layerId, ecefPosition, &material, vertexBinding)
        , m_mesh(mesh)
        , m_color(initialColor)
        , m_scale(initialScale)
        , m_depthTest(depthTest)
        , m_alphaBlend(alphaBlend)
        , m_orientationEcef(Eegeo::m44::CreateIdentity())
        {
            
        }
        
        void UIMeshRenderable::OnMaterialChanged(const Eegeo::Rendering::Materials::IMaterial* pMaterial, Eegeo::Rendering::VertexLayouts::VertexBindingPool& vertexBindingPool)
        {
            const Eegeo::Rendering::VertexLayouts::VertexBinding& vertexBinding = vertexBindingPool.GetVertexBinding(m_mesh.GetVertexLayout(), GetMaterial()->GetShader().GetVertexAttributes());
            SetVertexBinding(vertexBinding);
        }
        
        void UIMeshRenderable::Render(Eegeo::Rendering::GLState& glState) const
        {
            m_material->SetStatePerRenderable(this, glState);
            
            m_mesh.BindVertexBuffers(GetVertexBinding(), glState);
            
            Eegeo_GL(glDrawElements(GL_TRIANGLES, m_mesh.GetNumOfIndices(), GL_UNSIGNED_SHORT, (void*)(0)));
            
            m_mesh.UnbindVertexBuffers(glState);
        }
        
        Eegeo::m44 UIMeshRenderable::CalcModelViewProjection(const Eegeo::dv3& ecefCameraPosition, const Eegeo::m44& viewProjection) const
        {
            const Eegeo::dv3& flattenedEcefPosition = GetEcefPosition();
            
            const Eegeo::v3& cameraRelativeModelOrigin = (flattenedEcefPosition - ecefCameraPosition).ToSingle();
            Eegeo::m44 translateRotate;
            translateRotate.SetFromBasis(m_orientationEcef.GetRow(0), m_orientationEcef.GetRow(1), m_orientationEcef.GetRow(2), cameraRelativeModelOrigin);
            
            Eegeo::m44 scale;
            scale.Scale(m_scale);
            
            Eegeo::m44 orientedCameraRelativeModel;
            Eegeo::m44::Mul(orientedCameraRelativeModel, translateRotate, scale);
            
            
            Eegeo::m44 modelViewProjection;
            Eegeo::m44::Mul(modelViewProjection, viewProjection, orientedCameraRelativeModel);
            return modelViewProjection;
        }
    }
}