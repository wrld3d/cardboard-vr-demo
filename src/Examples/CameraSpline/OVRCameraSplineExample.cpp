// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "OVRCameraSplineExample.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "CatmullRomSpline.h"
#include "CameraSplinePlaybackController.h"
#include "ResourceCeilingProvider.h"
#include "GlobeCameraController.h"
#include "EegeoWorld.h"
#include "EarthConstants.h"
#include "ScreenProperties.h"

namespace Examples
{
    OVRCameraSplineExample::OVRCameraSplineExample(Eegeo::EegeoWorld& eegeoWorld,
                                                   Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                   Eegeo::Camera::GlobeCamera::GlobeCameraController* cameraController,
                                             const Eegeo::Rendering::ScreenProperties& initialScreenProperties)
    : m_world(eegeoWorld)
    {
        NotifyScreenPropertiesChanged(initialScreenProperties);
//        firstCall = true;
        Eegeo::m44 projectionMatrix = Eegeo::m44(cameraController->GetRenderCamera().GetProjectionMatrix());
        m_pSplineCameraController = new Eegeo::OVR::OVREegeoCameraController(initialScreenProperties.GetScreenWidth(), initialScreenProperties.GetScreenHeight());
//        m_pSplineCameraController->GetCamera().SetProjectionMatrix(projectionMatrix);
        m_pSplineCameraController->GetCamera().SetProjection(0.7, 0.1, 4000);
    }
    
    void OVRCameraSplineExample::Start()
    {
        
        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(37.7858,-122.401, 100);
        
        m_pSplineCameraController->SetStartLatLongAltitude(eyePosLla);
//        m_pSplineCameraController->SetSplines(m_pPositionSpline, m_pTargetSpline);
//        
//        // Select a playback speed
//        m_pSplineCameraController->SetPlaybackSpeed(0.005);
//        
//        // Loop the animation
//        m_pSplineCameraController->SetLooped(true);
//        
//        // Start the animation
//        m_pSplineCameraController->Play();
    }
    
    void OVRCameraSplineExample::Suspend()
    {
//        // Stop the animation
//        m_pSplineCameraController->Stop();
//        
//        // Cleanup
//        delete m_pSplineCameraController;
//        delete m_pPositionSpline;
//        delete m_pTargetSpline;
    }
    
    void OVRCameraSplineExample::EarlyUpdate(float dt)
    {
        m_pSplineCameraController->Update(dt);
    }
    
    void OVRCameraSplineExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
//        m_pSplineCameraController->UpdateScreenProperties(screenProperties);
    }
    
    
    Eegeo::Camera::CameraState OVRCameraSplineExample::GetCurrentLeftCameraState(float headTansform[]) const
    {

        
        Eegeo::m33 orientation;
        for(int lop=0; lop<12;lop+=4){
                orientation.SetRow(lop/4, Eegeo::v3(headTansform[lop], headTansform[lop+1], headTansform[lop+2]));
        }
        
//        if(firstCall)
//        {
//            Eegeo::m33 inverse;
//            Eegeo::m33::Inverse(inverse, orientation);
//            firstCall = FALSE;
//        }
        
        Eegeo::dv3 eyeDistanceD = m_pSplineCameraController->GetCameraPosition().Norm()*0.03f;
        Eegeo::v3 eD(eyeDistanceD.GetX(), eyeDistanceD.GetY(), eyeDistanceD.GetZ());
        m_pSplineCameraController->UpdateFromPose(orientation, eD);
        
        return m_pSplineCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState OVRCameraSplineExample::GetCurrentRightCameraState(float headTansform[]) const
    {
        
        Eegeo_TTY("  Projection %.2f, %.2f, %.2f",m_pSplineCameraController->GetCamera().GetFOV(), m_pSplineCameraController->GetCamera().GetNearClip(), m_pSplineCameraController->GetCamera().GetFarClip());
        
        Eegeo::m44 m4;
        Eegeo::m33 orientation;
        
        for(int lop=0; lop<16;lop+=4){
            m4.SetRow(lop/4, Eegeo::v4(headTansform[lop], headTansform[lop+1], headTansform[lop+2], headTansform[lop+3]));
            if(lop<12)
                orientation.SetRow(lop/4, Eegeo::v3(headTansform[lop], headTansform[lop+1], headTansform[lop+2]));
        }
        
        
        Eegeo::dv3 eyeDistanceD = m_pSplineCameraController->GetCameraPosition().Norm()*-0.03f;
        Eegeo::v3 eD(eyeDistanceD.GetX(), eyeDistanceD.GetY(), eyeDistanceD.GetZ());
        m_pSplineCameraController->UpdateFromPose(orientation, eD);
        
        return m_pSplineCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState OVRCameraSplineExample::GetCurrentCameraState() const
    {
        return m_pSplineCameraController->GetCameraState();
    }
}