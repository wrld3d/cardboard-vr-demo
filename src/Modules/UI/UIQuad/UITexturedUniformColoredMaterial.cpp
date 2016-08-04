// Copyright (c) 2014 eeGeo. All rights reserved.

#include "UITexturedUniformColoredMaterial.h"
#include "GLHelpers.h"
#include "UIMeshRenderable.h"

namespace Eegeo
{
    namespace Rendering
    {
        namespace Materials
        {

            UITexturedUniformColoredMaterial::UITexturedUniformColoredMaterial(const TMaterialId materialId,
                                             const std::string& name,
                                             Shaders::TexturedUniformColoredShader& shader,
                                             TTextureId textureId,
                                             const v4& initialColor)
            : m_id(materialId)
            , m_name(name)
            , m_shader(shader)
            , m_textureId(textureId)
            , m_color(initialColor)
            {
            }

            void UITexturedUniformColoredMaterial::SetState(Rendering::GLState& glState) const
            {
                m_shader.Use(glState);

                glState.Blend.Enable();
                glState.BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glState.BlendEquation(GL_FUNC_ADD);
                glState.DepthMask(GL_FALSE);
                glState.DepthTest(false);

                bool repeatTexture = false;
                Rendering::TextureMinifyType textureMinifyType = Rendering::TextureMinify_Linear;
                Helpers::GLHelpers::BindTexture2D(glState, m_shader.GetDiffuseSamplerId(), m_textureId, textureMinifyType, repeatTexture);
            }
            
            void UITexturedUniformColoredMaterial::SetStatePerRenderable(const Rendering::RenderableBase* pRenderableBase, Rendering::GLState& glState) const
            {
                m_shader.SetMVP(pRenderableBase->GetModelViewProjection());

                const UI::UIMeshRenderable* renderable = static_cast<const UI::UIMeshRenderable*>(pRenderableBase);
                m_shader.SetColor(renderable->GetColor());
            }
        }
    }
}