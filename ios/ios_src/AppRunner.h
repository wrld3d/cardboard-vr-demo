// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef APPRUNNER_H_
#define APPRUNNER_H_

#import <UIKit/UIKit.h>
#include "Graphics.h"
#include "AppHost.h"
#include "GlDisplayService.h"
#include "Types.h"

@class ViewController;

class AppRunner : Eegeo::NonCopyable
{
public:
	AppRunner(
        ViewController& pView,
        Examples::ApplicationConfig::ApplicationConfiguration& applicationConfiguration
    );
	~AppRunner();

	void Pause();
	void Resume();
	void Update(float deltaSeconds);
    
    bool ShouldAutoRotateToInterfaceOrientation(UIInterfaceOrientation interfaceOrientation);

    void NotifyViewLayoutChanged();
private:
    Examples::ApplicationConfig::ApplicationConfiguration& m_applicationConfiguration;
    ViewController& m_viewController;

	GlDisplayService m_displayService;
	void ReleaseDisplay();
	bool TryBindDisplay();

	AppHost* m_pAppHost;
	void CreateAppHost();
};

#endif
