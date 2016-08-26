// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once
#import <UIKit/UIKit.h>

namespace Examples
{
    namespace ApplicationConfig
    {
        class ApplicationConfiguration;
    }
}


@interface AppDelegate : UIResponder <UIApplicationDelegate>
{

}
@property (strong, nonatomic) UIWindow *window;
@property (nonatomic) Examples::ApplicationConfig::ApplicationConfiguration* m_pApplicationConfiguration;

@end
