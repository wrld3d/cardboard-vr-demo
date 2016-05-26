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

namespace Eegeo
{
    namespace UI
    {
        struct Vertex
        {
            Eegeo::v3 position;
            Eegeo::v3 normal;
            Eegeo::v2 uv;
            
            Vertex()
            : position(Eegeo::v3::Zero())
            , normal(Eegeo::v3::Zero())
            , uv(Eegeo::v2::Zero())
            {
            }
            
            Vertex(const Eegeo::v3& position, const Eegeo::v3& normal, const Eegeo::v2 uv)
            : position(position)
            , normal(normal)
            , uv(uv)
            {
            }
        };
        
        struct PositionUvVertex
        {
            float x;
            float y;
            float z;
            float u;
            float v;
        };
        
        inline PositionUvVertex MakePositionUvVertex(const Eegeo::v3& pos, const Eegeo::v2& uv)
        {
            PositionUvVertex v;
            v.x = pos.x;
            v.y = pos.y;
            v.z = pos.z;
            v.u = uv.x;
            v.v = uv.y;
            return v;
        }
        
        inline PositionUvVertex GeometryHelpersVertexToPositionUvVertex(const Vertex& v)
        {
            return MakePositionUvVertex(v.position, v.uv);
        }
        
        void BuildQuad(const Eegeo::v2& halfDimensions, const Eegeo::v2& uv_min, const Eegeo::v2& uv_max, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices);
        Eegeo::m33 GetLookAtOrientationMatrix(const Eegeo::v3& targetPosition, const Eegeo::v3& objectPosition, Eegeo::v3 up);
        void GetMaterialForQuadFromTexture(Eegeo::Modules::Core::RenderingModule& p_RenderingModule, Eegeo::Helpers::ITextureFileLoader& textureFileLoader, const std::string& fileName, Helpers::GLHelpers::TextureInfo& out_textureInfo, Eegeo::Rendering::Materials::TexturedUniformColoredMaterial* out_material, Eegeo::Rendering::Shaders::TexturedUniformColoredShader* out_shader);
    }
}