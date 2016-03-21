//
//  FBRenderTexture
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#pragma once

#include "Types.h"
#include "Graphics.h"

namespace Eegeo
{
    namespace Rendering
    {
        // Framebuffer and Texture (color buffer) based Render To Texture
        class FBRenderTexture : protected Eegeo::NonCopyable
        {
            
        public:
            FBRenderTexture()
            : g_undistortTextureId(0)
            , g_undistortFramebufferId(0)
            , g_undistortRenderbufferId(0)
            , m_rendering(false)
            , m_initialized(false)
            {
            }
            
            bool IsRendering() const { return m_rendering; }
            
            void InitRenderer(int viewportWidth, int viewportHeight);
            void BeginRendering();
            void EndRendering();
            
            GLuint getTextureId(){ return g_undistortTextureId; }
            
            ~FBRenderTexture();
            
        private:
            
            GLuint g_undistortFramebufferId;
            GLuint g_undistortTextureId;
            GLuint g_undistortRenderbufferId ;
            
            bool m_rendering;
            bool m_initialized;
            
        };
    }
}