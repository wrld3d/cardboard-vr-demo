// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef GLDISPLAYSERVICE_H_
#define GLDISPLAYSERVICE_H_

#include "Types.h"
#include "Graphics.h"

class GlDisplayService
{
public:
	GlDisplayService();
	~GlDisplayService();

	bool TryBindDisplay(ANativeWindow& window);
	void ReleaseDisplay(bool destroyEGL);

	bool IsDisplayAvailable() const;
	int GetDisplayWidth() const;
	int GetDisplayHeight() const;
	EGLDisplay GetDisplay() const;
	EGLSurface GetSurface() const;
	EGLSurface GetSharedSurface() const;
	EGLContext GetContext() const;
	EGLContext GetResourceBuildSharedContext() const;
    
    void InitializeUndistortFramebuffer(int width, int height);
    void BeginUndistortFramebuffer();
    GLuint FinishUndistortFramebuffer();

private:
    
    GLuint g_undistort_framebuffer_id = 0;
    GLuint g_undistort_texture_id = 0;
    GLuint g_undistort_renderbuffer_id = 0;
	EGLDisplay m_display;
	EGLSurface m_surface;
	EGLSurface m_sharedSurface;
	EGLContext m_context;
	EGLContext m_resourceBuildSharedContext;
	int m_displayWidth;
	int m_displayHeight;
	bool m_displayBound;
};

#endif
