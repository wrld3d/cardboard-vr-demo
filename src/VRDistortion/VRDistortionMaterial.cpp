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

#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            VRDistortionMaterial::VRDistortionMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                                       const std::string& name,
                                                       VRDistortionShader& shader,
                                                       Eegeo::Rendering::FBRenderTexture& renderTexture,
                                                       Eegeo::Rendering::ScreenProperties& screenProperties)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_renderTexture(renderTexture)
            , m_screenProperties(screenProperties)
            {  
            }
            
            const Eegeo::Rendering::Shader& VRDistortionMaterial::GetShader() const
            {
                return m_shader;
            }
            
            void VRDistortionMaterial::SetState(Eegeo::Rendering::GLState& glState) const
            {
                
                glViewport(0, 0, m_screenProperties.GetScreenWidth()*2.f, m_screenProperties.GetScreenHeight());
                
                m_shader.Use(glState);
                m_renderTexture.EndRendering();
                
                const bool repeat = false;
                Eegeo::Helpers::GLHelpers::BindTexture2D(glState,
                                                         m_shader.GetDiffuseSamplerId(),
                                                         m_renderTexture.getTextureId(),
                                                         Eegeo::Rendering::TextureMinify_Nearest,
                                                         repeat);
            }
            
            void VRDistortionMaterial::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
            {
                m_screenProperties = screenProperties;
            }
            
            void VRDistortionMaterial::SetStatePerRenderable(const Rendering::RenderableBase* renderableBase, Rendering::GLState& glState) const{}
        }
    }
}