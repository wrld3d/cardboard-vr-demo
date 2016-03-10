// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "OVRCameraSplineExampleFactory.h"
#include "OVRCameraSplineExample.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ResourceCeilingProvider.h"

#include "MapModule.h"

namespace Examples
{

OVRCameraSplineExampleFactory::OVRCameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                                       const IScreenPropertiesProvider& screenPropertiesProvider)
: m_world(world)
, m_screenPropertiesProvider(screenPropertiesProvider)
{
    
}

IExample* OVRCameraSplineExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
	return new Examples::OVRCameraSplineExample(m_world,
                                             mapModule.GetResourceCeilingProvider(),
                                             initialScreenProperties);
}

std::string OVRCameraSplineExampleFactory::ExampleName() const
{
	return Examples::OVRCameraSplineExample::GetName();
}
}
