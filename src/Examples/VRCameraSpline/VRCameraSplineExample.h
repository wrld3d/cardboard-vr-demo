// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraTransitionExample__
#define __ExampleApp__CameraTransitionExample__

#include <iostream>
#include "GlobeCameraExampleBase.h"
#include "OVRCameraPositionSpline.h"


namespace Examples
{
/*!
 *  CameraTransitionExample demonstrates the ability to ease the camera position from it's current location to a destination and back again
 */
class VRCameraSplineExample : public GlobeCameraExampleBase
{
private:

    Eegeo::Camera::GlobeCamera::GlobeCameraController* m_CameraController;
    Eegeo::OVR::OVRCameraPositionSpline m_OVRCameraPositionSpline;
    
public:
	VRCameraSplineExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                            Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController);

	static std::string GetName()
	{
		return "VRCameraSplineExample";
	}
	std::string Name() const
	{
		return GetName();
	}

    virtual Eegeo::Camera::CameraState GetCurrentLeftCameraState(float headTansform[]) const;
    virtual Eegeo::Camera::CameraState GetCurrentRightCameraState(float headTansform[]) const;

    void Start();
	void EarlyUpdate(float dt) { }
    void Update(float dt);
	void Draw() {}
	void Suspend() {}
};
}

#endif /* defined(__ExampleApp__CameraTransitionExample__) */
