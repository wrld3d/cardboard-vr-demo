//
//  VRDistortionMaterial
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#ifndef __ExampleApp__VRDistortionShader__
#define __ExampleApp__VRDistortionShader__

#include "Shader.h"
#include "Rendering.h"
#include "Graphics.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            class VRDistortionShader : public Eegeo::Rendering::Shader
            {
            public:
                static VRDistortionShader* Create(const Eegeo::Rendering::TShaderId shaderId);
                void Use(Eegeo::Rendering::GLState& glState) const;
                GLuint GetDiffuseSamplerId() const;
                void SetMVP(const m44& mvp) const;
                

            private:
                VRDistortionShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexCode, const std::string& fragmentCode);
                GLuint m_diffuseTextureSamplerUniformLocation;
            };
            
        }
    }
}

#endif /* defined(__ExampleApp__VRDistortionShader__) */
