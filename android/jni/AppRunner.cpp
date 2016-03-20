// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppRunner.h"
#include "Graphics.h"
#include "AndroidThreadHelper.h"
#include "RenderTexture.h"
#include "Logger.h"

AppRunner::AppRunner
(
    const std::string& apiKey,
    AndroidNativeState* pNativeState
)
	: m_apiKey(apiKey)
	, m_pNativeState(pNativeState)
	, m_pAppHost(NULL)
	, m_isPaused(false)
{
	Eegeo::Helpers::ThreadHelpers::SetThisThreadAsMainThread();
}

AppRunner::~AppRunner()
{
	bool destroyEGL = true;
	m_displayService.ReleaseDisplay(destroyEGL);

	if(m_pAppHost != NULL)
	{
		Eegeo_DELETE(m_pAppHost);
	}
}

void AppRunner::CreateAppHost()
{
	if(m_pAppHost == NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost = Eegeo_NEW(AppHost)
		             (
		                 m_apiKey,
		                 *m_pNativeState,
		                 m_displayService.GetDisplayWidth(),
		                 m_displayService.GetDisplayHeight(),
		                 m_displayService.GetDisplay(),
		                 m_displayService.GetSharedSurface(),
		                 m_displayService.GetResourceBuildSharedContext()
		             );
	}
}

void AppRunner::Pause()
{
	if(m_pAppHost != NULL && !m_isPaused)
	{
		m_pAppHost->OnPause();
		m_isPaused = true;
	}

	ReleaseDisplay();
}

void AppRunner::Resume()
{
	if(m_pAppHost != NULL && m_isPaused)
	{
		m_pAppHost->OnResume();
	}

	m_isPaused = false;
}

void AppRunner::ActivateSurface()
{
	Pause();
	bool displayBound = TryBindDisplay();
	Eegeo_ASSERT(displayBound);
	CreateAppHost();
	Resume();
}


void AppRunner::HandleTouchEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
    if(m_pAppHost != NULL)
    {
        m_pAppHost->HandleTouchInputEvent(event);
    }
}

void AppRunner::MagnetTriggered()
{
    if(m_pAppHost != NULL)
    {
        m_pAppHost->MagnetTriggered();
    }
}

void AppRunner::ReleaseDisplay()
{
	if(m_displayService.IsDisplayAvailable())
	{
		const bool teardownEGL = false;
		m_displayService.ReleaseDisplay(teardownEGL);
	}
}

bool AppRunner::TryBindDisplay()
{
	if(m_displayService.TryBindDisplay(*(m_pNativeState->window)))
	{
        
        JNIEnv* env = m_pNativeState->mainThreadEnv;
        jobject activity = m_pNativeState->activity;
        jclass fpl_class = env->GetObjectClass(activity);
        jmethodID undistort = env->GetMethodID(fpl_class, "SetHeadMountedDisplayResolution", "(II)V");
        env->CallVoidMethod(activity, undistort, (jint) (m_displayService.GetDisplayWidth()*2.f), (jint) m_displayService.GetDisplayHeight());
        env->DeleteLocalRef(fpl_class);

        m_pRenderTexture = Eegeo_NEW(Eegeo::Rendering::RenderTexture)(static_cast<u32>(m_displayService.GetDisplayWidth()),
                                                                      static_cast<u32>(m_displayService.GetDisplayHeight()),
                                                                      false);

        
		if(m_pAppHost != NULL)
		{
			m_pAppHost->SetSharedSurface(m_displayService.GetSharedSurface());
			const Eegeo::Rendering::ScreenProperties& screenProperties = Eegeo::Rendering::ScreenProperties::Make(
					m_displayService.GetDisplayWidth(),
					m_displayService.GetDisplayHeight(),
					1.f,
					m_pNativeState->deviceDpi);
			m_pAppHost->NotifyScreenPropertiesChanged(screenProperties);
			m_pAppHost->SetViewportOffset(0, 0);
		}

		return true;
	}

	return false;
}

void AppRunner::Update(float deltaSeconds, float headTansform[])
{
	if(m_pAppHost != NULL && m_displayService.IsDisplayAvailable())
	{
		m_pAppHost->Update(deltaSeconds, headTansform);
        
        // bind your render to texture frame buffer
        glBindFramebuffer(GL_FRAMEBUFFER, m_displayService.GetFrameBufferId());
        
        // swap buffers
		Eegeo_GL(eglSwapBuffers(m_displayService.GetDisplay(), m_displayService.GetSurface()));

        // clear buffers
        Eegeo::Helpers::GLHelpers::ClearBuffers();
        
        // engine draw call
        m_pAppHost->Draw(deltaSeconds, headTansform);
        
        // binding default framebuffer back to render distorted results to screen
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        // set viewport back to full screen from steroscopic viewport for VR
        glViewport(0, 0, m_displayService.GetDisplayWidth()*2.f, m_displayService.GetDisplayHeight());

        
//         jni call to "UndistortTexture()" function of MainActivity which contains CardboardView and calls cardboard view's undistortTexture()
        JNIEnv* env = m_pNativeState->mainThreadEnv;
        jobject activity = m_pNativeState->activity;
        jclass fpl_class = env->GetObjectClass(activity);
        jmethodID undistort = env->GetMethodID(fpl_class, "UndistortTexture", "(I)V");
        env->CallVoidMethod(activity, undistort, (jint)m_displayService.GetTextureId());
        env->DeleteLocalRef(fpl_class);
//        TryRenderFameBufferTexture();
        
	}
}

void AppRunner::TryRenderFameBufferTexture(){
    
    static const GLfloat squareVertices[] = {
        -1.0f, -1.0f,
        1.0f, -1.0f,
        -1.0f,  1.0f,
        1.0f,  1.0f,
    };
    
    static const GLfloat textureVertices[] = {
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f,  1.0f,
        0.0f,  0.0f,
    };
    
    std::string vertextShader("attribute vec4 position;\n"
                              "attribute vec4 inputTextureCoordinate;\n"
                              "varying vec2 textureCoordinate;\n"
                              "void main()\n"
                              "{\n"
                              "gl_Position = position;\n"
                              "textureCoordinate = inputTextureCoordinate.xy;\n"
                              "}");
    
    std::string fragmentShader("varying highp vec2 textureCoordinate;\n"
                               "uniform sampler2D videoFrame;\n"
                               "void main()\n"
                               "{\n"
                               "gl_FragColor = texture2D(videoFrame, textureCoordinate);\n"
                               "}");
    
    const char *vertShaderSrc = vertextShader.c_str();
    const char *fragShaderSrc = fragmentShader.c_str();
    
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);
    
    
    GLint result = GL_FALSE;
    int logLength;
    // Check vertex shader
    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> vertShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(vertShader, logLength, NULL, &vertShaderError[0]);
    
    std::cout << &vertShaderError[0] << std::endl;
    
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);
    
    // Check fragment shader
    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);
    glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> fragShaderError((logLength > 1) ? logLength : 1);
    glGetShaderInfoLog(fragShader, logLength, NULL, &fragShaderError[0]);
    std::cout << &fragShaderError[0] << std::endl;
    
    std::cout << "Linking program" << std::endl;
    GLuint program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    glLinkProgram(program);
    
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
    std::vector<char> programError( (logLength > 1) ? logLength : 1 );
    glGetProgramInfoLog(program, logLength, NULL, &programError[0]);
    std::cout << &programError[0] << std::endl;
    
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    
    glUseProgram(program);
    
    glActiveTexture(GL_TEXTURE0);
    
    glBindTexture(GL_TEXTURE_2D, m_displayService.GetTextureId());
    
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, 0, 0, squareVertices);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, textureVertices);
    
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    

}


