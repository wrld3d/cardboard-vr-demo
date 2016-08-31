// Copyright (c) 2014 eeGeo. All rights reserved.

#pragma once

#include "GLState.h"
#include "RenderableBase.h"
#include "IdTypes.h"
#include "TexturedUniformColoredShader.h"
#include "IMaterial.h"

namespace Eegeo
{
    namespace Rendering
    {
        namespace Materials
        {
            /*!
             * \brief Material that tints via a uniform colour (not a color per vertex)
             */
            class UITexturedUniformColoredMaterial : protected Eegeo::NonCopyable, public IMaterial
            {
            public:
                UITexturedUniformColoredMaterial(const TMaterialId materialId,
                        const std::string& name,
                        Shaders::TexturedUniformColoredShader& shader,
                        TTextureId textureId,
                        const v4& initialColor);

                const TMaterialId GetId() const { return m_id; }
                const Shader& GetShader() const { return m_shader; }
                const std::string& GetName() const { return m_name; }

                void SetState(Rendering::GLState& glState) const;

                void SetStatePerRenderable(const Rendering::RenderableBase* renderableBase, Rendering::GLState& glState) const;

                void SetColor(v4& color) { m_color = color; }
                const v4& GetColor() const { return m_color; }

            protected:
                const TMaterialId m_id;
                const std::string m_name;
                Shaders::TexturedUniformColoredShader& m_shader;
                TTextureId m_textureId;
                v4 m_color;
            };
        }
    }
}