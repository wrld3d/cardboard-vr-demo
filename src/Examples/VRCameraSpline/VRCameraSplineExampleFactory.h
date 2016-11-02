// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__VRCameraSplineExampleFactory__
#define __ExampleApp__VRCameraSplineExampleFactory__

#include "IExampleFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"
#include "IInteriorsExplorerModule.h"
#include "IVRHeadTracker.h"
#include "Modules/DeadZoneMenu/DeadZoneMenuItemRepository.h"
#include "IUIQuadFactory.h"
#include "IScreenFadeEffectController.h"
#include "ApplicationConfiguration.h"
#include "ConfigSections.h"

namespace Examples
{
    class VRCameraSplineExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        InteriorsExplorer::IInteriorsExplorerModule& m_interiorsExplorerModule;
        IVRHeadTracker& m_headTracker;
        Eegeo::UI::IUIQuadFactory& m_quadFactory;
        ScreenFadeEffect::SdkModel::IScreenFadeEffectController& m_screenFader;
        const ApplicationConfig::ApplicationConfiguration m_appConfig;
        const Eegeo::Config::DeviceSpec m_deviceSpecs;

    public:
        VRCameraSplineExampleFactory( Eegeo::EegeoWorld& world,
                                      DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                      IVRHeadTracker& headTracker,
                                      const IScreenPropertiesProvider& screenPropertiesProvider,
                                      InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                      Eegeo::UI::IUIQuadFactory& quadFactory,
                                     ScreenFadeEffect::SdkModel::IScreenFadeEffectController& screenFader,
                                     const ApplicationConfig::ApplicationConfiguration& appConfig,
                                     const Eegeo::Config::DeviceSpec& deviceSpecs);

        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__VRCameraSplineExampleFactory__) */
