// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRCameraSplineExampleFactory.h"
#include "VRCameraSplineExample.h"
#include "DefaultCameraControllerFactory.h"

namespace Examples
{

VRCameraSplineExampleFactory::VRCameraSplineExampleFactory(Eegeo::EegeoWorld& world,
        DefaultCameraControllerFactory& defaultCameraControllerFactory,
        Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& globeCameraTouchController)
	: m_world(world)
	, m_defaultCameraControllerFactory(defaultCameraControllerFactory)
    , m_globeCameraTouchController(globeCameraTouchController)
{

}

IExample* VRCameraSplineExampleFactory::CreateExample() const
{
	return new Examples::VRCameraSplineExample(m_defaultCameraControllerFactory.Create(), m_globeCameraTouchController);
}

std::string VRCameraSplineExampleFactory::ExampleName() const
{
	return Examples::VRCameraSplineExample::GetName();
}

}

