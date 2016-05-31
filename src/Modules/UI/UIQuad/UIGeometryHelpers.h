//
//  UIGeometryHelpers.h
//  SDKSamplesApp
//
//  Created by Ali on 5/13/16.
//
//

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include <vector>
#include "EcefTangentBasis.h"
#include "GLHelpers.h"
#include "ITextureFileLoader.h"
#include "RenderingModule.h"
#include "AllVertexTypes.h"

namespace Eegeo
{
    namespace UI
    {
        void BuildQuad(const Eegeo::v2& halfDimensions, const Eegeo::v2& uv_min, const Eegeo::v2& uv_max, std::vector<Rendering::VertexTypes::TexturedVertex>& out_vertices, std::vector<u16>& out_triangleIndices);
        Eegeo::m33 GetLookAtOrientationMatrix(const Eegeo::v3& targetPosition, const Eegeo::v3& objectPosition, Eegeo::v3 up);
        void GetMaterialForQuadFromTexture(Eegeo::Modules::Core::RenderingModule& p_RenderingModule, Eegeo::Helpers::ITextureFileLoader& textureFileLoader, const std::string& fileName, Helpers::GLHelpers::TextureInfo& out_textureInfo, Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* out_material, Eegeo::Rendering::Shaders::TexturedUniformColoredShader* out_shader);
    }
}