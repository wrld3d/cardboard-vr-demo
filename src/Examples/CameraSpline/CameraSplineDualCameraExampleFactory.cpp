// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraSplineDualCameraExampleFactory.h"
#include "CameraSplineDualCameraExample.h"
#include "EegeoWorld.h"
#include "GlobeCameraController.h"
#include "ResourceCeilingProvider.h"

#include "MapModule.h"

namespace Examples
{

CameraSplineDualCameraExampleFactory::CameraSplineDualCameraExampleFactory(Eegeo::EegeoWorld& world,
                                                       const IScreenPropertiesProvider& screenPropertiesProvider)
: m_world(world)
, m_screenPropertiesProvider(screenPropertiesProvider)
{
    
}

IExample* CameraSplineDualCameraExampleFactory::CreateExample() const
{
    Eegeo::Modules::Map::MapModule& mapModule = m_world.GetMapModule();
    
    const Eegeo::Rendering::ScreenProperties& initialScreenProperties = m_screenPropertiesProvider.GetScreenProperties();
    
	return new Examples::CameraSplineDualCameraExample(m_world,
                                             mapModule.GetResourceCeilingProvider(),
                                             initialScreenProperties);
}

std::string CameraSplineDualCameraExampleFactory::ExampleName() const
{
	return Examples::CameraSplineDualCameraExample::GetName();
}
}
