// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointsExampleFactory.h"
#include "JumpPointsExample.h"
#include "Modules/UI/Animations/AnimationsController.h"


namespace Examples
{

        
    JumpPointsExampleFactory::JumpPointsExampleFactory(Eegeo::EegeoWorld& world,
                                                       DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                       const IScreenPropertiesProvider& screenPropertiesProvider,
                                                       Eegeo::UI::IUIQuadFactory& quadFactory,
                                                       Eegeo::UI::IUIInteractionObservable& uiInteractionObservable,
                                                       Eegeo::UI::IUICameraProvider& uiCameraProvider,
                                                       InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                                       Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& deadZoneMenuRepository,
                                                       Eegeo::UI::Animations::AnimationsController& animationsController,
                                                       IVRHeadTracker& headTracker)
    : m_uiQuadFactory(quadFactory)
    , m_uiInteractionObservable(uiInteractionObservable)
    , m_uiCameraProvider(uiCameraProvider)
    , m_world(world)
    , m_animationsController(animationsController)
    , m_screenPropertiesProvider(screenPropertiesProvider)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_interiorsExplorerModule(interiorsExplorerModule)
    , m_deadZoneMenuRepository(deadZoneMenuRepository)
    , m_headTracker(headTracker)
    {
        
    }
    
    IExample* JumpPointsExampleFactory::CreateExample() const
    {
        
        Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
        const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
        
        return new Examples::JumpPointsExample(m_world,
                                               mapModule.GetResourceCeilingProvider(),
                                               m_defaultCameraControllerFactory.Create(),
                                               initialScreenProperties,
                                               m_uiQuadFactory,
                                               m_uiInteractionObservable,
                                               m_uiCameraProvider,
                                               m_interiorsExplorerModule,
                                               m_deadZoneMenuRepository,
                                               m_animationsController,
                                               m_headTracker
                                               );
    }
    
    std::string JumpPointsExampleFactory::ExampleName() const
    {
        return Examples::JumpPointsExample::GetName();
    }
}
