//
//  UIGeometryHelpers.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/13/16.
//
//

#include "UIGeometryHelpers.h"
namespace Eegeo
{
    namespace UI
    {
        void BuildQuad(const Eegeo::v2& halfDimensions, const Eegeo::v2& uv_min, const Eegeo::v2& uv_max, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices)
        {
            const int faces = 1;
            const int pointsPerFace = 4;
            out_vertices.clear();
            out_triangleIndices.clear();
            out_vertices.reserve(pointsPerFace*faces);
            out_triangleIndices.reserve(faces*3*2);
            
            Eegeo::v3 faceNormal = Eegeo::v3(1.f, 0.f, 0.f);
            
            Eegeo::v3 points[4] =
            {
                Eegeo::v3(halfDimensions.x, -halfDimensions.y, 0),
                Eegeo::v3(halfDimensions.x, halfDimensions.y, 0),
                Eegeo::v3(-halfDimensions.x, halfDimensions.y, 0),
                Eegeo::v3(-halfDimensions.x, -halfDimensions.y, 0),
            };
            
            out_vertices.push_back(Vertex(points[0], faceNormal, Eegeo::v2(uv_min.x, uv_min.y)));
            out_vertices.push_back(Vertex(points[1], faceNormal, Eegeo::v2(uv_min.x, uv_max.y)));
            out_vertices.push_back(Vertex(points[2], faceNormal, Eegeo::v2(uv_max.x, uv_max.y)));
            out_vertices.push_back(Vertex(points[3], faceNormal, Eegeo::v2(uv_max.x, uv_min.y)));
            
            out_triangleIndices.push_back(0);
            out_triangleIndices.push_back(1);
            out_triangleIndices.push_back(2);
            out_triangleIndices.push_back(2);
            out_triangleIndices.push_back(3);
            out_triangleIndices.push_back(0);
            
        }
        
        Eegeo::m33 GetLookAtOrientationMatrix(const Eegeo::v3& targetPosition, const Eegeo::v3& objectPosition, Eegeo::v3 up){
            Eegeo::v3 delta = targetPosition-objectPosition;
            Eegeo::v3 direction(delta.Norm());
            Eegeo::v3 right = (Eegeo::v3::Cross(up,direction)).Norm();
            up = (Eegeo::v3::Cross(direction, right)).Norm();
            Eegeo::m33 orientation;
            orientation.SetFromBasis(right, up, direction);
            return orientation;
        }
    }
}
