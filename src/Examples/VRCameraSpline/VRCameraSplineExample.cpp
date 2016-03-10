// Copyright eeGeo Ltd (2012-2014), All Rights Reserved


#include "VRCameraSplineExample.h"
#include "GlobeCameraController.h"
#include "EarthConstants.h"

namespace Examples
{

VRCameraSplineExample::VRCameraSplineExample(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
	: GlobeCameraExampleBase(pCameraController, cameraTouchController)
    {
        m_CameraController = pCameraController;
        m_OVRCameraPositionSpline.Start();
    }
    
    
    void VRCameraSplineExample::Start() {
    }

    void VRCameraSplineExample::Update(float dt)
    {
        
        m_OVRCameraPositionSpline.Update(dt);
        if (!m_OVRCameraPositionSpline.IsPlaying())
        {
            m_OVRCameraPositionSpline.NextSpline();
            m_OVRCameraPositionSpline.Start();
        }
    }
    
    Eegeo::Camera::CameraState VRCameraSplineExample::GetCurrentLeftCameraState(float headTansform[]) const
    {
        
        
        
        Eegeo::m33 orientation;
        Eegeo::dv3 position;
        
        m_OVRCameraPositionSpline.GetCurrentCameraPosition(position, orientation);
        
        Eegeo_TTY(" Update Left %.2f, %.2f, %.2f", position.GetX(), position.GetY(), position.GetZ());
        
        for(int lop=0; lop<12;lop+=4){
            orientation.SetRow(lop/4, Eegeo::v3(headTansform[lop], headTansform[lop+1], headTansform[lop+2]));
        }
        
        Eegeo::dv3 eyeSeparation = Eegeo::dv3::Mul(position.Norm()*0.013, orientation);
//        Eegeo::m44 projectionMatrix(m_CameraController->GetRenderCamera().GetProjectionMatrix());

        
        Eegeo::Camera::RenderCamera renderCamera(m_CameraController->GetRenderCamera());
//        renderCamera.SetProjectionMatrix(projectionMatrix);
        renderCamera.SetEcefLocation(position+eyeSeparation);
        renderCamera.SetOrientationMatrix(orientation);
        
        return Eegeo::Camera::CameraState(position+eyeSeparation,
                                   (position+eyeSeparation).Norm() * Eegeo::Space::EarthConstants::Radius,
                                   renderCamera.GetViewMatrix(),
                                   renderCamera.GetProjectionMatrix());
        
    }
    
    Eegeo::Camera::CameraState VRCameraSplineExample::GetCurrentRightCameraState(float headTansform[]) const
    {
        Eegeo::m33 orientation;
        Eegeo::dv3 position;
        
        m_OVRCameraPositionSpline.GetCurrentCameraPosition(position, orientation);
        
        for(int lop=0; lop<12;lop+=4){
            orientation.SetRow(lop/4, Eegeo::v3(headTansform[lop], headTansform[lop+1], headTansform[lop+2]));
        }
        
        Eegeo::dv3 eyeSeparation = Eegeo::dv3::Mul(position.Norm()*-0.013, orientation);
        Eegeo::m44 projectionMatrix(m_CameraController->GetRenderCamera().GetProjectionMatrix());
        
        Eegeo::Camera::RenderCamera renderCamera;
        renderCamera.SetProjectionMatrix(projectionMatrix);
        renderCamera.SetEcefLocation(position+eyeSeparation);
        renderCamera.SetOrientationMatrix(orientation);
        
        return Eegeo::Camera::CameraState(renderCamera.GetEcefLocation(),
                                          renderCamera.GetEcefLocation().Norm() * Eegeo::Space::EarthConstants::Radius,
                                          renderCamera.GetViewMatrix(),
                                          renderCamera.GetProjectionMatrix());
    }
    



}
