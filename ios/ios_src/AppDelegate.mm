// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "ApiKey.h"
#include "iOSFileIO.h"
#import "AppDelegate.h"
#include "ViewController.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"

namespace
{
    typedef Examples::ApplicationConfig::ApplicationConfiguration ApplicationConfiguration;
    ApplicationConfiguration LoadConfiguration()
    {
        // create file IO instance (iOSPlatformAbstractionModule not yet available in app lifetime)
        Eegeo::iOS::iOSFileIO tempFileIO;
        //ApplicationConfig::SdkModel::iOSApplicationConfigurationVersionProvider iOSVersionProvider;
        Examples::ApplicationConfig::SdkModel::ApplicationConfigurationModule applicationConfigurationModule(tempFileIO,"2.0","1.0");
        return applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration(Examples::ApplicationConfigurationPath);
    }
}

@implementation AppDelegate

@synthesize window = _window;

-(void) dealloc
{
    Eegeo_DELETE _m_pApplicationConfiguration;
    [super dealloc];
}


-(BOOL) application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    const ApplicationConfiguration& appConfig = LoadConfiguration();
    _m_pApplicationConfiguration = Eegeo_NEW(ApplicationConfiguration)(appConfig);
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
    // Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later.
    // If your application supports background execution, this method is called instead of applicationWillTerminate: when the user quits.
    
    [[NSNotificationCenter defaultCenter] postNotificationName: @"handlePause"
                                                        object: nil
                                                      userInfo: nil];
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
    // Called as part of the transition from the background to the inactive state; here you can undo many of the changes made on entering the background.
    
    [[NSNotificationCenter defaultCenter] postNotificationName: @"handleResume"
                                                        object: nil
                                                      userInfo: nil];
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}

- (void)applicationWillTerminate:(UIApplication *)application
{
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
    
    [UIApplication sharedApplication].delegate = nil;
}



- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url  sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
    return false;
}


@end
