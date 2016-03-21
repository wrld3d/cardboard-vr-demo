//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//


#include "VRDistortionMaterial.h"
#include "GLHelpers.h"
#include "Rendering.h"
#include "VectorMath.h"
#include "VRDistortionShader.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            VRDistortionMaterial::VRDistortionMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                       const std::string& name,
                                                       VRDistortionShader& shader,
                                                       Eegeo::Rendering::FBRenderTexture& renderTexture)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_renderTexture(renderTexture)
            {  
            }
            
            const Eegeo::Rendering::Shader& VRDistortionMaterial::GetShader() const
            {
                return m_shader;
            }
            
            void VRDistortionMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                m_shader.Use(glState);
                m_renderTexture.EndRendering();
                
                const bool repeat = false;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState,
                                                         m_shader.GetDiffuseSamplerId(),
                                                         m_renderTexture.getTextureId(),
                                                         Eegeo::Rendering::TextureMinify_Nearest,
                                                         repeat);
            }
            
            void VRDistortionMaterial::SetStatePerRenderable(const Rendering::RenderableBase* renderableBase, Rendering::GLState& glState) const{}
        }
    }
}