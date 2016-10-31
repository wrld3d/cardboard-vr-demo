// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRCameraSplineExampleFactory.h"
#include "VRCameraSplineExample.h"
#include "EegeoWorld.h"
#include "ResourceCeilingProvider.h"
#include "DefaultCameraControllerFactory.h"
#include "MapModule.h"

namespace Examples
{

    VRCameraSplineExampleFactory::VRCameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                                               DefaultCameraControllerFactory&defaultCameraControllerFactory,
                                                               IVRHeadTracker& headTracker,
                                                               const IScreenPropertiesProvider& screenPropertiesProvider,
                                                               InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                                               Eegeo::UI::IUIQuadFactory& quadFactory,
                                                               ScreenFadeEffect::SdkModel::IScreenFadeEffectController& screenFader,
                                                               const ApplicationConfig::ApplicationConfiguration& appConfig)
    : m_world(world)
    , m_headTracker(headTracker)
    , m_screenPropertiesProvider(screenPropertiesProvider)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_interiorsExplorerModule(interiorsExplorerModule)
    , m_quadFactory(quadFactory)
    , m_screenFader(screenFader)
    , m_appConfig(appConfig)
{
    
}

IExample* VRCameraSplineExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
    return new Examples::VRCameraSplineExample(m_world,
                                                mapModule.GetResourceCeilingProvider(),
                                                m_defaultCameraControllerFactory.Create(),
                                                m_headTracker,
                                                initialScreenProperties,
                                                m_interiorsExplorerModule,
                                                m_quadFactory,
                                                m_screenFader,
                                                m_appConfig);
}

std::string VRCameraSplineExampleFactory::ExampleName() const
{
	return Examples::VRCameraSplineExample::GetName();
}
}
