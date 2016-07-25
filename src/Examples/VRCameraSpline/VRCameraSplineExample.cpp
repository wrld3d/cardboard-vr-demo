// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRCameraSplineExample.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "CatmullRomSpline.h"
#include "CameraSplinePlaybackController.h"
#include "ResourceCeilingProvider.h"
#include "GlobeCameraController.h"
#include "EegeoWorld.h"
#include "EarthConstants.h"
#include "ScreenProperties.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModule.h"
#include "IInteriorsExplorerModule.h"
#include "IVRHeadTracker.h"

#define INTERIOR_NEAR_MULTIPLIER 0.025f
#define EXTERIOR_NEAR_MULTIPLIER 0.1f

#include "Logger.h"

namespace Examples
{
    VRCameraSplineExample::VRCameraSplineExample(Eegeo::EegeoWorld& eegeoWorld,
                                                 Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                 IVRHeadTracker& headTracker,
                                                 const Eegeo::Rendering::ScreenProperties& initialScreenProperties,
                                                 InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                                 Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& deadZoneRepository)
    : m_world(eegeoWorld),
      m_interiorsExplorerModule(interiorsExplorerModule),
      m_deadZoneRepository(deadZoneRepository),
      m_onSFSplineSelectedCallback(this, &VRCameraSplineExample::OnSFSplineSelected),
      m_onNYSplineSelectedCallback(this, &VRCameraSplineExample::OnNYSplineSelected),
      m_onWestPortSplineSelectedCallback(this, &VRCameraSplineExample::OnWestPortSplineSelected)
    {
        NotifyScreenPropertiesChanged(initialScreenProperties);
        Eegeo::m44 projectionMatrix = Eegeo::m44(pCameraController->GetRenderCamera().GetProjectionMatrix());
        m_pSplineCameraController = new Eegeo::VR::VRCameraController(initialScreenProperties.GetScreenWidth(), initialScreenProperties.GetScreenHeight(), headTracker);
        m_pSplineCameraController->GetCamera().SetProjectionMatrix(projectionMatrix);
        m_eyeDistance = 0.03f;
    }
    
    VRCameraSplineExample::~VRCameraSplineExample(){
//        delete m_pSplineCameraController;
    }
    
    void VRCameraSplineExample::Start()
    {
        
        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250);
        m_pSplineCameraController->SetStartLatLongAltitude(eyePosLla);
        
        m_pSFSplineButton = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 3, m_onSFSplineSelectedCallback);
        m_pNYSplineButton = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(11, 4, m_onNYSplineSelectedCallback);
        m_pWPSplineButton = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(12, 5, m_onWestPortSplineSelectedCallback);

        m_deadZoneRepository.AddDeadZoneMenuItem(m_pSFSplineButton);
        m_deadZoneRepository.AddDeadZoneMenuItem(m_pNYSplineButton);
        m_deadZoneRepository.AddDeadZoneMenuItem(m_pWPSplineButton);
    }
    
    void VRCameraSplineExample::Suspend()
    {
        m_interiorsExplorerModule.HideInteriors();
        
        m_deadZoneRepository.RemoveDeadZoneMenuItem(m_pSFSplineButton);
        m_deadZoneRepository.RemoveDeadZoneMenuItem(m_pNYSplineButton);
        m_deadZoneRepository.RemoveDeadZoneMenuItem(m_pWPSplineButton);
        
        Eegeo_DELETE m_pSFSplineButton;
        Eegeo_DELETE m_pNYSplineButton;
        Eegeo_DELETE m_pWPSplineButton;
    }
    
    void VRCameraSplineExample::UpdateCardboardProfile(float cardboardProfile[])
    {
        //9th parameter is eye distance in meters.
        m_eyeDistance = cardboardProfile[9]/2.0f;
    }
    
    void VRCameraSplineExample::EarlyUpdate(float dt)
    {
        m_pSplineCameraController->Update(dt);
        
            if (m_pSplineCameraController->GetVRCameraPositionSpline().IsInteriorSpline()) {
                m_pSplineCameraController->SetNearMultiplier(INTERIOR_NEAR_MULTIPLIER);
                
                m_interiorsExplorerModule.ShowInteriors();
                m_interiorsExplorerModule.SelectFloor(2);
            }
            else {
                m_pSplineCameraController->SetNearMultiplier(EXTERIOR_NEAR_MULTIPLIER);
                m_interiorsExplorerModule.HideInteriors();
            }
        
    }
    
    void VRCameraSplineExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
    }
    
    
    const Eegeo::m33& VRCameraSplineExample::getCurrentCameraOrientation()
    {
        return m_pSplineCameraController->GetOrientation();
    }
    
    const Eegeo::m33& VRCameraSplineExample::GetBaseOrientation()
    {
        return m_pSplineCameraController->GetCameraOrientation();
    }
    
    const Eegeo::m33& VRCameraSplineExample::GetHeadTrackerOrientation()
    {
        return m_pSplineCameraController->GetHeadTrackerOrientation();
    }
    
    Eegeo::Camera::RenderCamera& VRCameraSplineExample::GetRenderCamera(){
        return m_pSplineCameraController->GetCamera();
    }
    
    Eegeo::Camera::CameraState VRCameraSplineExample::GetCurrentLeftCameraState(float headTansform[]) const
    {
        
        Eegeo::m33 orientation;
        Eegeo::v3 right = Eegeo::v3(headTansform[0],headTansform[4],headTansform[8]);
        Eegeo::v3 up = Eegeo::v3(headTansform[1],headTansform[5],headTansform[9]);
        Eegeo::v3 forward = Eegeo::v3(-headTansform[2],-headTansform[6],-headTansform[10]);
        orientation.SetRow(0, right);
        orientation.SetRow(1, up);
        orientation.SetRow(2, forward);
        
        m_pSplineCameraController->UpdateFromPose(orientation, -m_eyeDistance);
        
        return m_pSplineCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState VRCameraSplineExample::GetCurrentRightCameraState(float headTansform[]) const
    {
        Eegeo::m33 orientation;
        Eegeo::v3 right = Eegeo::v3(headTansform[0],headTansform[4],headTansform[8]);
        Eegeo::v3 up = Eegeo::v3(headTansform[1],headTansform[5],headTansform[9]);
        Eegeo::v3 forward = Eegeo::v3(-headTansform[2],-headTansform[6],-headTansform[10]);
        orientation.SetRow(0, right);
        orientation.SetRow(1, up);
        orientation.SetRow(2, forward);

        m_pSplineCameraController->UpdateFromPose(orientation, m_eyeDistance);
        
        return m_pSplineCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState VRCameraSplineExample::GetCurrentCameraState() const
    {
        return m_pSplineCameraController->GetCameraState();
    }
    
    void VRCameraSplineExample::OnWestPortSplineSelected()
    {
        m_pSplineCameraController->PlaySpline(4);
    }
    
    void VRCameraSplineExample::OnSFSplineSelected()
    {
        m_pSplineCameraController->PlaySpline(2);
    }
    
    void VRCameraSplineExample::OnNYSplineSelected()
    {
        m_pSplineCameraController->PlaySpline(9);
    }
}
