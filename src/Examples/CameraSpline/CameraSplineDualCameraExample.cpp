// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraSplineDualCameraExample.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "CatmullRomSpline.h"
#include "CameraSplinePlaybackController.h"
#include "ResourceCeilingProvider.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "EegeoWorld.h"
#include "EarthConstants.h"
#include "ScreenProperties.h"

namespace Examples
{
    CameraSplineDualCameraExample::CameraSplineDualCameraExample(Eegeo::EegeoWorld& eegeoWorld,
                                             Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                             const Eegeo::Rendering::ScreenProperties& initialScreenProperties)
    : m_world(eegeoWorld)
    , m_resourceCeilingProvider(resourceCeilingProvider)
    {
        m_pSplineCameraController = new Eegeo::Camera::SplinePlayback::CameraSplinePlaybackController(m_resourceCeilingProvider);
        NotifyScreenPropertiesChanged(initialScreenProperties);
    }
    
    void CameraSplineDualCameraExample::Start()
    {
        // Initialise our spline paths
        m_pPositionSpline = new Eegeo::Geometry::CatmullRomSpline();
        m_pTargetSpline = new Eegeo::Geometry::CatmullRomSpline();
        
        // The CameraSplineDualCameraPlaybackController takes in two splines
        // One defines the camera's movement, the other defines what it looks at
        // For this example, we'll do a simple path around San Francisco.
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.777145, -122.402181, 50).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.789423, -122.392311, 70).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.804480, -122.412223, 100).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.804276, -122.428188, 60).ToECEF());
        m_pPositionSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.808141, -122.448787, 30).ToECEF());
        
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.781215, -122.407116, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.789389, -122.395658, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.802886, -122.412995, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.802241, -122.429776, 0).ToECEF());
        m_pTargetSpline->AddPoint(Eegeo::Space::LatLongAltitude::FromDegrees(37.803461, -122.447843, 0).ToECEF());
        
        // Initialise the camera controller and assign which splines we want to use for the animation
        
        m_pSplineCameraController->SetSplines(m_pPositionSpline, m_pTargetSpline);
        
        // Select a playback speed
        m_pSplineCameraController->SetPlaybackSpeed(0.005);
        
        // Loop the animation
        m_pSplineCameraController->SetLooped(true);
        
        // Start the animation
        m_pSplineCameraController->Play();
    }
    
    void CameraSplineDualCameraExample::Suspend()
    {
        // Stop the animation
        m_pSplineCameraController->Stop();
        
        // Cleanup
        delete m_pSplineCameraController;
        delete m_pPositionSpline;
        delete m_pTargetSpline;
    }
    
    void CameraSplineDualCameraExample::EarlyUpdate(float dt)
    {
        m_pSplineCameraController->Update(dt);
    }
    
    void CameraSplineDualCameraExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        m_pSplineCameraController->UpdateScreenProperties(screenProperties);
    }
    
    
    Eegeo::Camera::CameraState CameraSplineDualCameraExample::GetCurrentLeftCameraState() const
    {
        
//        m_pSplineCameraController->GetRenderCamera().GetEcefLocation()
        Eegeo::dv3 interestPoint(m_pSplineCameraController->GetRenderCamera().GetEcefLocation().Norm() * Eegeo::Space::EarthConstants::Radius);
        
        Eegeo::Camera::RenderCamera renderCamera(m_pSplineCameraController->GetRenderCamera());
        
        Eegeo_TTY("%.2f   %.2f    %.2f",renderCamera.GetEcefLocation().Norm().GetX()
                  ,renderCamera.GetEcefLocation().Norm().GetY()
                  ,renderCamera.GetEcefLocation().Norm().GetZ()
                  );
        
        renderCamera.SetEcefLocation(Eegeo::dv3::Add(renderCamera.GetEcefLocation(), renderCamera.GetEcefLocation().Norm()*0.3f));
//        Eegeo_TTY("Model matrix") ;
//        for(int lop=0; lop<4;lop++){
//            Eegeo_TTY("%.2f   %.2f    %.2f   %.2f",renderCamera.GetModelMatrix().GetRow(lop).Norm(). GetX()
//                      ,renderCamera.GetModelMatrix().GetRow(lop).GetY()
//                      ,renderCamera.GetModelMatrix().GetRow(lop).GetZ()
//                      ,renderCamera.GetModelMatrix().GetRow(lop).GetW()) ;
//        }
        return Eegeo::Camera::CameraState(renderCamera.GetEcefLocation(),
                                          interestPoint,
                                          renderCamera.GetViewMatrix(),
                                          renderCamera.GetProjectionMatrix());
    }
    
    Eegeo::Camera::CameraState CameraSplineDualCameraExample::GetCurrentRightCameraState() const
    {
        Eegeo::dv3 interestPoint(m_pSplineCameraController->GetRenderCamera().GetEcefLocation().Norm() * Eegeo::Space::EarthConstants::Radius);
        
        Eegeo::Camera::RenderCamera renderCamera(m_pSplineCameraController->GetRenderCamera());
        
        renderCamera.SetEcefLocation(Eegeo::dv3::Add(renderCamera.GetEcefLocation(), renderCamera.GetEcefLocation().Norm()*-0.3f));
        
        return Eegeo::Camera::CameraState(renderCamera.GetEcefLocation(),
                                          interestPoint,
                                          renderCamera.GetViewMatrix(),
                                          renderCamera.GetProjectionMatrix());
    }
    Eegeo::Camera::CameraState CameraSplineDualCameraExample::GetCurrentCameraState() const
    {
        Eegeo::dv3 interestPoint(m_pSplineCameraController->
                                 GetRenderCamera().GetEcefLocation().Norm() * Eegeo::Space::EarthConstants::Radius);
        Eegeo::Camera::RenderCamera renderCamera(m_pSplineCameraController->GetRenderCamera());
        
//        Eegeo_TTY("Model matrix") ;
//        Eegeo::m44 mat = renderCamera.GetProjectionMatrix();
//        for(int lop=0; lop<4;lop++){
//            Eegeo_TTY("%.2f   %.2f    %.2f   %.2f",mat.GetRow(lop).GetX()
//                      ,mat.GetRow(lop).GetY()
//                      ,mat.GetRow(lop).GetZ()
//                      ,mat.GetRow(lop).GetW());
//        }
        
        Eegeo_TTY("DIRECTION") ;

            Eegeo_TTY("%.2f   %.2f    %.2f",renderCamera.GetEcefLocation().GetX()
                      ,renderCamera.GetEcefLocation().GetY()
                      ,renderCamera.GetEcefLocation().GetZ()
                      );

        
        return Eegeo::Camera::CameraState(renderCamera.GetEcefLocation(),
                                          interestPoint,
                                          renderCamera.GetViewMatrix(),
                                          renderCamera.GetProjectionMatrix());
    }
}