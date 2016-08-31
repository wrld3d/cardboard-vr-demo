// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__JumpPointsExampleFactory__
#define __ExampleApp__JumpPointsExampleFactory__

#include "IExampleFactory.h"
#include "Modules/UI/UIInteraction/UIInteractionController.h"
#include "Modules/UI/IUICameraProvider.h"
#include "Modules/UI/UIQuad/IUIQuadFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"
#include "Modules/UI/Animations/AnimationsController.h"
#include "Modules/WorldMenu/WorldMenuModule.h"
#include "WorldMenuLoaderModel.h"
#include "ApplicationConfiguration.h"

namespace Examples
{
class JumpPointsExampleFactory : public IExampleFactory
{
    Eegeo::UI::IUIQuadFactory& m_uiQuadFactory;
    Eegeo::UI::IUIInteractionObservable& m_uiInteractionObservable;
    Eegeo::UI::IUICameraProvider& m_uiCameraProvider;
    Examples::ApplicationConfig::ApplicationConfiguration m_appConfig;
    
    Eegeo::EegeoWorld& m_world;
    const IScreenPropertiesProvider& m_screenPropertiesProvider;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    InteriorsExplorer::IInteriorsExplorerModule& m_interiorsExplorerModule;
    Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& m_deadZoneMenuRepository;
    Eegeo::UI::WorldMenu::WorldMenuModule& m_worldMenuModule;
    IVRHeadTracker& m_headTracker;
    
    Eegeo::UI::Animations::AnimationsController& m_animationsController;
    WorldMenuLoader::SdkModel::WorldMenuLoaderModel& m_menuLoader;
    
public:
    JumpPointsExampleFactory(Eegeo::EegeoWorld& world,
                             DefaultCameraControllerFactory& defaultCameraControllerFactory,
                             const IScreenPropertiesProvider& screenPropertiesProvider,
                             Eegeo::UI::IUIQuadFactory& quadFactory,
                             Eegeo::UI::IUIInteractionObservable& uiInteractionObservable,
                             Eegeo::UI::IUICameraProvider& uiCameraProvider,
                             InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                             Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& deadZoneMenuRepository,
                             Eegeo::UI::Animations::AnimationsController& animationsController,
                             Eegeo::UI::WorldMenu::WorldMenuModule& worldMenuModule,
                             WorldMenuLoader::SdkModel::WorldMenuLoaderModel& menuLoader,
                             IVRHeadTracker& headTracker,
                             Examples::ApplicationConfig::ApplicationConfiguration& appConfig);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__JumpPointsExampleFactory__) */
