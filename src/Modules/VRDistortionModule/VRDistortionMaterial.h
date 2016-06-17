//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//


#ifndef __ExampleApp__VRDistortionMaterial__
#define __ExampleApp__VRDistortionMaterial__

#include <string>
#include "Types.h"
#include "IMaterial.h"
#include "Rendering.h"
#include "RenderTexture.h"
#include "ScreenProperties.h"
#include "VRDistortionIncludes.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionMaterial : Eegeo::NonCopyable, public Eegeo::Rendering::Materials::IMaterial
            {
            public:
                VRDistortionMaterial(const Eegeo::Rendering::TMaterialId materialId,
                                     const std::string& name,
                                     VRDistortionShader& shader,
                                     Eegeo::Rendering::RenderTexture& renderTexture,
                                     Eegeo::Rendering::ScreenProperties& screenProperties);
                
                const std::string& GetName() const { return m_name; }
                void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
                
                const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
                const Eegeo::Rendering::Shader& GetShader() const;
                void SetState(Eegeo::Rendering::GLState& glState) const;
                void SetStatePerRenderable(const Rendering::RenderableBase* pRenderableBase, Rendering::GLState& glState)  const;
                
                bool isRenderingEnded(){ return m_isRenderingEnded; }
                void setIsRenderingEnded(bool isRenderingEnded){ m_isRenderingEnded = isRenderingEnded; }
                
            private:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_name;
                VRDistortionShader& m_shader;
                Eegeo::Rendering::RenderTexture& m_renderTexture;
                Eegeo::Rendering::ScreenProperties m_screenProperties;
                mutable bool m_isRenderingEnded;
            };
            
        }
    }
}

#endif /* defined(__ExampleApp__VRDistortionMaterial__) */
