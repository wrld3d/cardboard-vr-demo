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
//        "if(Position.z <= -0.01){\n"
        "float r2 = clamp(dot(Position.xy,Position.xy), 0.0, 2.771);\n"
        "pos = vec2(Position.xy * (1.0 + (0.52 + 0.16 * r2) * r2));\n"
//        "}\n"
        "gl_Position = vec4(pos, 0.0, 1.0);\n" 
        "}";
    }
    
//    std::string VertexShader()
//    {
//        return
//        "attribute vec2 Position;\n"
//        "attribute mediump vec2 UV;\n"
//        "varying mediump vec2 DestinationUV;\n"
//        "void main(void) { \n"
//        "DestinationUV = UV;\n"
//        "gl_Position = vec4(Position, 0.0, 1.0);\n"
//        "}";
//    }
    
    std::string FragmentShader()
    {
        return
        "precision mediump float;\n"
        "varying vec3 v_Grid;\n"
        "varying mediump vec2 DestinationUV;\n"
        "uniform sampler2D diffuseTex; \n"
        "void main(void) { \n"
        "highp vec4 colour = texture2D(diffuseTex, DestinationUV.xy); \n"
//        "float depth = gl_FragCoord.z / gl_FragCoord.w; \n" // Calculate world-space distance.
        //TODO: depth doesnt match with eegeo i think. need to test
//        "if ((mod(abs(v_Grid.x), 10.0) < 0.1) || (mod(abs(v_Grid.z), 10.0) < 0.1)) { \n"
//        "    gl_FragColor = max(0.0, (90.0-depth) / 90.0) * vec4(1.0, 1.0, 1.0, 1.0) \n"
//        "    + min(1.0, depth / 90.0) * colour; \n"
//        "} else { \n"
        "    gl_FragColor = colour; \n"
//        "} \n"
        "}";
    }
    
//    std::string FragmentShader()
//    {
//        return
//        "varying mediump vec2 DestinationUV;\n"
//        "uniform sampler2D diffuseTex; \n"
//        "uniform highp vec3 vignetteColour; \n"
//        "uniform highp float vignetteRadiusModifier; \n"
//        "void main(void) { \n"
//        "highp vec4 colour = texture2D(diffuseTex, DestinationUV.xy); \n"
//        "highp float greyscale = dot(colour.rgb, vec3(0.3, 0.59, 0.11)); \n"
//        "highp vec2 d = DestinationUV.xy - 0.5;\n"
//        "colour.rgb = greyscale * vignetteColour * (1.0 - dot(d, d) * vignetteRadiusModifier); \n"
//        "gl_FragColor = vec4(colour.rgb, 1.0); \n"
//        "}";
//    }
    
    PostProcessVignetteShader* PostProcessVignetteShader::Create(const Eegeo::Rendering::TShaderId shaderId)
    {
        return Eegeo_NEW(PostProcessVignetteShader)(shaderId, VertexShader(), FragmentShader());
    }
    
    PostProcessVignetteShader::PostProcessVignetteShader(const Eegeo::Rendering::TShaderId shaderId, const std::string& vertexCode, const std::string& fragmentCode)
    : Shader(shaderId)
    {
        CompileProgram(vertexCode, fragmentCode);
        
        m_diffuseTextureSamplerUniformLocation = GetUniformLocation("diffuseTex");
//        m_vignetteColourUniform = GetUniformLocation("vignetteColour");
       // m_vignetteRadiusModifierUniform = GetUniformLocation("vignetteRadiusModifier");
    }
    
    GLuint PostProcessVignetteShader::GetDiffuseSamplerId() const
    {
        return 0;
    }
    
    void PostProcessVignetteShader::SetVignetteColour(const Eegeo::v3& vignetteColour)
    {
//        SetUniformV3(vignetteColour, m_vignetteColourUniform);
    }
    
//    void PostProcessVignetteShader::SetVignetteRadiusModifier(float vignetteRadiusModifier)
//    {
//        SetUniformFloat(vignetteRadiusModifier, m_vignetteRadiusModifierUniform);
//    }
    
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