// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointsExampleFactory.h"
#include "JumpPointsExample.h"


namespace Examples
{

        
    JumpPointsExampleFactory::JumpPointsExampleFactory(Eegeo::EegeoWorld& world,
                                                       DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                                       const IScreenPropertiesProvider& screenPropertiesProvider,
                                                       Eegeo::UI::IUIQuadFactory& quadFactory,
                                                       Eegeo::UI::IUIInteractionObservable& uIInteractionObservable,
                                                       Eegeo::UI::IUICameraProvider& uICameraProvider)
	: m_UIQuadFactory(quadFactory)
    , m_UIInteractionObservable(uIInteractionObservable)
    , m_UICameraProvider(uICameraProvider)
    , m_world(world)
    , m_screenPropertiesProvider(screenPropertiesProvider)
    , m_defaultCameraControllerFactory(defaultCameraControllerFactory)
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
                                           m_UIQuadFactory,
                                           m_UIInteractionObservable,
                                           m_UICameraProvider
                                           );
}

std::string JumpPointsExampleFactory::ExampleName() const
{
	return Examples::JumpPointsExample::GetName();
}
}
