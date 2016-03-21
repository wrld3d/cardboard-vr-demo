// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <string>
#include "PostProcessVignetteShader.h"
#include "ShaderCompiler.h"
#include "RenderContext.h"

namespace Examples
{    
    std::string VertexShader()
    {
        return
        "attribute vec2 Position;\n"
        "attribute mediump vec2 UV;\n"
        "varying mediump vec2 DestinationUV;\n"
        "void main(void) { \n"
        "DestinationUV = UV;\n"
        "vec2 pos = Position;\n"
        "gl_Position = vec4(pos, 0.0, 1.0);\n" 
        "}";
    }
    
    
    std::string FragmentShader()
    {
        return
        "precision mediump float;\n"
        "varying vec3 v_Grid;\n"
        "varying mediump vec2 DestinationUV;\n"
        "uniform sampler2D diffuseTex; \n"
        "void main(void) { \n"
        "highp vec4 colour = texture2D(diffuseTex, DestinationUV.xy); \n"
        "    gl_FragColor = colour; \n"
        "}";
    }
    
    PostProcessVignetteShader* PostProcessVignetteShader::Create(const Eegeo::Rendering::TShaderId shaderId)
    {
        return Eegeo_NEW(PostProcessVignetteShader)(shaderId, VertexShader(), FragmentShader());
    }
    
    PostProcessVignetteShader::PostProcessVignetteShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexCode, const std::string& fragmentCode)
    : Shader(shaderId)
    {
        CompileProgram(vertexCode, fragmentCode);
        m_diffuseTextureSamplerUniformLocation = GetUniformLocation("diffuseTex");
    }
    
    GLuint PostProcessVignetteShader::GetDiffuseSamplerId() const
    {
        return 0;
    }
    
    void PostProcessVignetteShader::SetVignetteColour(const Eegeo::v3& vignetteColour)
    {
    }
    
    
    void PostProcessVignetteShader::Use(Eegeo::Rendering::GLState& glState) const
    {
        UseProgram(glState);
        SetUniformTextureSampler(glState, GetDiffuseSamplerId(), m_diffuseTextureSamplerUniformLocation);
    }
    
    void PostProcessVignetteShader::SetMVP(const Eegeo::m44& mvp) const
    {
        // unimplemented base class method... input vertices are assumed to be in clip space.
    }
}