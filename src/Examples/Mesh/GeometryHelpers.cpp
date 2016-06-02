// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GeometryHelpers.h"
#include "Bounds.h"

namespace Examples
{
    namespace GeometryHelpers
    {
        
        
        void BuildQuad(const Eegeo::v2& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices)
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
            
            out_vertices.push_back(Vertex(points[0], faceNormal, Eegeo::v2(0, 0)));
            out_vertices.push_back(Vertex(points[1], faceNormal, Eegeo::v2(0, 1)));
            out_vertices.push_back(Vertex(points[2], faceNormal, Eegeo::v2(1, 1)));
            out_vertices.push_back(Vertex(points[3], faceNormal, Eegeo::v2(1, 0)));
            
            out_triangleIndices.push_back(0);
            out_triangleIndices.push_back(1);
            out_triangleIndices.push_back(2);
            out_triangleIndices.push_back(2);
            out_triangleIndices.push_back(3);
            out_triangleIndices.push_back(0);
        }
        
        void BuildBox(const Eegeo::v3& halfDimensions, std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices)
        {
            const int faces = 6;
            const int pointsPerFace = 4;
            out_vertices.clear();
            out_triangleIndices.clear();
            out_vertices.reserve(pointsPerFace*faces);
            out_triangleIndices.reserve(faces*3*2);
            
            Eegeo::v3 faceNormals[faces] =
            {
                Eegeo::v3(1.f, 0.f, 0.f),
                Eegeo::v3(0.f, 0.f, 1.f),
                Eegeo::v3(-1.f, 0.f, 0.f),
                Eegeo::v3(0.f, 0.f, -1.f),
                Eegeo::v3(0.f, 1.f, 0.f),
                Eegeo::v3(0.f, -1.f, 0.f)
            };
            
            Eegeo::v3 points[8] =
            {
                Eegeo::v3(halfDimensions.x, halfDimensions.y, halfDimensions.z),
                Eegeo::v3(halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                Eegeo::v3(halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                Eegeo::v3(halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, halfDimensions.y, halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, halfDimensions.y, -halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, -halfDimensions.y, halfDimensions.z),
                Eegeo::v3(-halfDimensions.x, -halfDimensions.y, -halfDimensions.z),
            };
            
            int pointIndices[faces*pointsPerFace] =
            {
                1, 0, 3, 2,
                0, 4, 2, 6,
                4, 5, 6, 7,
                5, 1, 7, 3,
                4, 0, 5, 1,
                7, 3, 6, 2,
            };
            
            
            Eegeo::Geometry::Bounds2D uvRects[] =
            {
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.0f), Eegeo::v2(0.5f, 0.5f)),    // +ve x, "0"
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.5f, 0.0f), Eegeo::v2(1.0f, 0.5f)),    // +ve z, "1"
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.0f, 0.5f), Eegeo::v2(0.5f, 1.0f)),    // -ve x, "2"
                Eegeo::Geometry::Bounds2D(Eegeo::v2(0.5f, 0.5f), Eegeo::v2(1.0f, 1.0f)),    // -ve z, "3"
                Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),             // +ve y (top)
                Eegeo::Geometry::Bounds2D(Eegeo::v2::Zero(), Eegeo::v2::One()),             // -ve y (bottom)
            };
            
            
            for (int i = 0; i < 6; ++i)
            {
                const Eegeo::v3& faceNormal = faceNormals[i];
                
                const Eegeo::Geometry::Bounds2D& uvRect = uvRects[i];
                
                u16 offset = static_cast<u16>(i*pointsPerFace);
                out_vertices.push_back(Vertex(points[pointIndices[offset + 0]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.max.y)));
                out_vertices.push_back(Vertex(points[pointIndices[offset + 1]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.max.y)));
                out_vertices.push_back(Vertex(points[pointIndices[offset + 2]], faceNormal, Eegeo::v2(uvRect.min.x, uvRect.min.y)));
                out_vertices.push_back(Vertex(points[pointIndices[offset + 3]], faceNormal, Eegeo::v2(uvRect.max.x, uvRect.min.y)));
                
                out_triangleIndices.push_back(offset + 0);
                out_triangleIndices.push_back(offset + 1);
                out_triangleIndices.push_back(offset + 2);
                out_triangleIndices.push_back(offset + 2);
                out_triangleIndices.push_back(offset + 1);
                out_triangleIndices.push_back(offset + 3);
            }
        }
        
        float distort(float r, float k1, float k2) {
            float r2 = r * r;
            return ((k2 * r2 + k1) * r2 + 1) * r;
        }
        
        float distortInv(float radius, float k1, float k2) {
            // Secant method.
            float r0 = 0;
            float r1 = 1;
            float dr0 = radius - distort(r0, k1, k2);
            while (Eegeo::Math::Abs(r1 - r0) > 0.0001f) {
                float dr1 = radius - distort(r1, k1, k2);
                float r2 = r1 - dr1 * ((r1 - r0) / (dr1 - dr0));
                r0 = r1;
                r1 = r2;
                dr0 = dr1;
            }
            return r1;
        }
        
        void GetLeftEyeVisibleScreenRect(float undistortedFrustum[], int screenWidth, int screenHeight, float *rect) {
            //TODO get values from cardboard
            float dist = 0.039f;
            float eyeX = (screenWidth - 0.064f) / 2;
            float eyeY = screenHeight / 2;
            float left = (undistortedFrustum[0] * dist + eyeX) / screenWidth;
            float top = (undistortedFrustum[1] * dist + eyeY) / screenHeight;
            float right = (undistortedFrustum[2] * dist + eyeX) / screenWidth;
            float bottom = (undistortedFrustum[3] * dist + eyeY) / screenHeight;

            rect[0] = left;
            rect[1] = bottom;
            rect[2] = right - left;
            rect[3] = top - bottom;
        }
        

        void ComputeMeshPoints(int width, int height, bool distortVertices,std::vector<Vertex>& vertices,  int screenWidth, int screenHeight, float k1, float k2) {

            const float scaleRef = 34500.0f;
            const int screenWidthRef = 1920, screenHeightRef = 1080;
            
            const float xScale = scaleRef * screenWidth / screenWidthRef;
            const float yScale = scaleRef * screenHeight / screenHeightRef;
            
            //TODO get lens frustum from cardboard sdk
            float lensFrustum[4] = {-0.6987169f,1.140147f,1.212875f,-1.140147f};
            float noLensFrustum[4] = {-0.5897436f,0.7948717f,0.8205128f,-0.7948718f};
            
            
            
            float viewport[4];
            GetLeftEyeVisibleScreenRect(noLensFrustum, screenWidth, screenHeight, viewport);
            vertices.reserve(2 * width * height);
            
            for (int e = 0, vidx = 0; e < 2; e++) {
                for (int j = 0; j < height; j++) {
                    for (int i = 0; i < width; i++, vidx++) {
                        double u = (float)i / (width - 1);
                        double v = (float)j / (height - 1);
                        double s, t;  // The texture coordinates in StereoScreen to read from.
                        if (distortVertices) {
                            // Grid points regularly spaced in StreoScreen, and barrel distorted in the mesh.
                            s = u;
                            t = v;
                            float x = Eegeo::Math::Lerp<float>(lensFrustum[0], lensFrustum[2], u);
//                            float x = Mathf.Lerp(lensFrustum[0], lensFrustum[2], u);
                            float y = Eegeo::Math::Lerp<float>(lensFrustum[3], lensFrustum[1], v);
                            float d = Eegeo::Math::Sqrtf(x * x + y * y);
                            float r = distortInv(d, k1, k2);
                            float p = x * r / d;
                            float q = y * r / d;
                            u = (p - noLensFrustum[0]) / (noLensFrustum[2] - noLensFrustum[0]);
                            v = (q - noLensFrustum[3]) / (noLensFrustum[1] - noLensFrustum[3]);
                        } else {
                            // Grid points regularly spaced in the mesh, and pincushion distorted in
                            // StereoScreen.
                            float p = Eegeo::Math::Lerp<float>(noLensFrustum[0], noLensFrustum[2], u);
                            float q = Eegeo::Math::Lerp<float>(noLensFrustum[3], noLensFrustum[1], v);
                            float r = Eegeo::Math::Sqrtf(p * p + q * q);
                            float d = distort(r, k1, k2);
                            float x = p * d / r;
                            float y = q * d / r;
                            s = Eegeo::Math::Clamp01((x - lensFrustum[0]) / (lensFrustum[2] - lensFrustum[0]));
                            t = Eegeo::Math::Clamp01((y - lensFrustum[3]) / (lensFrustum[1] - lensFrustum[3]));
                        }
                        // Convert u,v to mesh screen coordinates.
                        float aspect = screenWidth / screenHeight;
                        u = (viewport[0] + u * viewport[2] - 0.5f) * aspect * xScale;
                        v = (viewport[1] + v * viewport[3] - 0.5f ) * yScale;
                        s = (s + e) / 2;
                        vertices.push_back(Vertex(Eegeo::v3(u, v, 1), Eegeo::v3::Zero(), Eegeo::v2(s,t)));
                    }
                }
                
                float w = lensFrustum[2] - lensFrustum[0];
                lensFrustum[0] = -(w + lensFrustum[0]);
                lensFrustum[2] = w - lensFrustum[2];
                w = noLensFrustum[2] - noLensFrustum[0];
                noLensFrustum[0] = -(w + noLensFrustum[0]);
                noLensFrustum[2] = w - noLensFrustum[2];
                viewport[0] = 1 - (viewport[0] + viewport[2]);
            }
        }
        
        void ComputeMeshIndices(int width, int height, bool distortVertices, std::vector<u16>& indices) {
            indices.reserve(2 * (width - 1) * (height - 1) * 6);
            int halfwidth = width / 2;
            int halfheight = height / 2;
            std::vector<u16>::iterator iidx = indices.begin();
            for (int e = 0, vidx = 0; e < 2; e++) {
                for (int j = 0; j < height; j++) {
                    for (int i = 0; i < width; i++, vidx++) {
                        if (i == 0 || j == 0)
                            continue;
                        // Build a quad.  Lower right and upper left quadrants have quads with the triangle
                        // diagonal flipped to get the vignette to interpolate correctly.
                        if ((i <= halfwidth) == (j <= halfheight)) {
                            // Quad diagonal lower left to upper right.
//                            indices.insert(iidx++, vidx);
                            indices.insert(iidx++, vidx);
                            indices.insert(iidx++, vidx - width);
                            indices.insert(iidx++, vidx - width - 1);
                            indices.insert(iidx++, vidx - width - 1);
                            indices.insert(iidx++, vidx - 1);
                            indices.insert(iidx++, vidx);
                        } else {
                            // Quad diagonal upper left to lower right.
                            indices.insert(iidx++, vidx - 1);
                            indices.insert(iidx++, vidx);
                            indices.insert(iidx++, vidx - width);
                            indices.insert(iidx++, vidx - width);
                            indices.insert(iidx++, vidx - width - 1);
                            indices.insert(iidx++, vidx - 1);
                        }
                    }
                }
            }
        }
        
        void BuildDistortionMesh(std::vector<Vertex>& out_vertices, std::vector<u16>& out_triangleIndices, int screenWidth, int screenHeight) {
            out_vertices.clear();
            out_triangleIndices.clear();
            
            int kMeshWidth = 40, kMeshHeight = 40;
            //TODO get k1 and k2 values from cardboard sdk
            float k1 = 0.34f, k2 = 0.55f;
            bool kDistortVertices = true;
            ComputeMeshPoints(kMeshWidth, kMeshHeight, kDistortVertices, out_vertices, screenWidth, screenHeight, k1, k2);
            ComputeMeshIndices(kMeshWidth, kMeshHeight, kDistortVertices, out_triangleIndices);
            
        }
        
    }
}
