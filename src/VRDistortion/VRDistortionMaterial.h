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
#include "VRDistortionIncludes.h"
#include "../../FBRenderTexture/FBRenderTexture.h"

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
                                     Eegeo::Rendering::FBRenderTexture& renderTexture);
                
                const Eegeo::Rendering::TMaterialId GetId() const { return m_id; }
                const Eegeo::Rendering::Shader& GetShader() const;
                const std::string& GetName() const { return m_name; }
                
                void SetState(Eegeo::Rendering::GLState& glState) const;
                
                void SetStatePerRenderable(const Rendering::RenderableBase* renderableBase, Rendering::GLState& glState)  const;
                
            private:
                const Eegeo::Rendering::TMaterialId m_id;
                const std::string m_name;
                VRDistortionShader& m_shader;
                Eegeo::Rendering::FBRenderTexture& m_renderTexture;
            };
            
        }
    }
}

#endif /* defined(__ExampleApp__VRDistortionMaterial__) */
