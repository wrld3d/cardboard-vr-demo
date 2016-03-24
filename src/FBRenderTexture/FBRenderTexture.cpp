//
//  FBRenderTexture
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 3/21/16.
//
//

#include "FBRenderTexture.h"
#include "Logger.h"

namespace Eegeo
{
    namespace Rendering
    {
        
        void FBRenderTexture::InitRenderer(int viewportWidth, int viewportHeight)
        {
            if(m_initialized){
                return;
            }
            
//            Eegeo_ASSERT(m_initialized, "FrameBufferRenderTexture Already Initialized.");
            
            Eegeo_GL(glGenTextures(1, &g_undistortTextureId));
            Eegeo_GL(glBindTexture(GL_TEXTURE_2D, g_undistortTextureId));
            Eegeo_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
            Eegeo_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
            Eegeo_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
            Eegeo_GL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
            Eegeo_GL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, viewportWidth, viewportHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr));
            
            Eegeo_GL(glGenRenderbuffers(1, &g_undistortRenderbufferId));
            Eegeo_GL(glBindRenderbuffer(GL_RENDERBUFFER, g_undistortRenderbufferId));
            Eegeo_GL(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, viewportWidth, viewportHeight));
            
            Eegeo_GL(glGenFramebuffers(1, &g_undistortFramebufferId));
            Eegeo_GL(glBindFramebuffer(GL_FRAMEBUFFER, g_undistortFramebufferId));
            
            Eegeo_GL(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, g_undistortTextureId, 0));
            Eegeo_GL(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, g_undistortRenderbufferId));
            
            Eegeo_GL(glBindFramebuffer(GL_FRAMEBUFFER, 0));
            
            m_initialized = true;
            
        }
        
        void FBRenderTexture::BeginRendering()
        {
            if(m_rendering)
            {
                return;
            }
            glBindFramebuffer(GL_FRAMEBUFFER, g_undistortFramebufferId);
            m_rendering = true;
        }
        
        void FBRenderTexture::EndRendering()
        {
            if(!m_rendering)
            {
                return;
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
            m_rendering = false;
        }
        
        FBRenderTexture::~FBRenderTexture()
        {
            if(m_initialized)
            {
                
                Eegeo_GL(glDeleteFramebuffers(1, &g_undistortFramebufferId));
                Eegeo_GL(glDeleteRenderbuffers(1, &g_undistortRenderbufferId));
                Eegeo_GL(glDeleteTextures(1, &g_undistortTextureId));
            }
        }
    }
    
}
