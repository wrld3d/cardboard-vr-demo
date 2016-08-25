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
#include "WorldMenuScreenFader.h"

namespace Examples
{
    class VRCameraSplineExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        InteriorsExplorer::IInteriorsExplorerModule& m_interiorsExplorerModule;
        Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& m_deadZoneRepository;
        IVRHeadTracker& m_headTracker;
        Eegeo::UI::IUIQuadFactory& m_quadFactory;
        WorldMenuLoader::SdkModel::WorldMenuScreenFader& m_screenFader;
        
    public:
        VRCameraSplineExampleFactory( Eegeo::EegeoWorld& world,
                                      DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                      IVRHeadTracker& headTracker,
                                      const IScreenPropertiesProvider& screenPropertiesProvider,
                                      InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                      Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& deadZoneRepository,
                                      Eegeo::UI::IUIQuadFactory& quadFactory,
                                      WorldMenuLoader::SdkModel::WorldMenuScreenFader& screenFader);

        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__VRCameraSplineExampleFactory__) */
