// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointsExample.h"
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
#include "InteriorsExplorerModel.h"
#include "IVRHeadTracker.h"
#include "CameraHelpers.h"

#define INTERIOR_NEAR_MULTIPLIER 0.025f
#define EXTERIOR_NEAR_MULTIPLIER 0.1f

#include "Logger.h"

namespace Examples
{
    JumpPointsExample::JumpPointsExample(Eegeo::EegeoWorld& eegeoWorld,
                                         Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                         const Eegeo::Rendering::ScreenProperties& initialScreenProperties,
                                         Eegeo::UI::IUIQuadFactory& quadFactory,
                                         Eegeo::UI::IUIInteractionObservable& uiInteractionObservable,
                                         Eegeo::UI::IUICameraProvider& uiCameraProvider,
                                         InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                         Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& deadZoneMenuRepository,
                                         IVRHeadTracker& headTracker)
    : m_world(eegeoWorld)
    , m_uiQuadFactory(quadFactory)
    , m_uiInteractionObservable(uiInteractionObservable)
    , m_uiCameraProvider(uiCameraProvider)
    , m_renderableFilters(eegeoWorld.GetRenderingModule().GetRenderableFilters())
    , m_interiorsExplorerModule(interiorsExplorerModule)
    , m_deadZoneMenuRepository(deadZoneMenuRepository)
    , m_headTracker(headTracker)
    , m_onSP1SelectedCallback(this, &JumpPointsExample::OnStopPoint1Selected)
    , m_onSP2SelectedCallback(this, &JumpPointsExample::OnStopPoint2Selected)
    , m_onSP3SelectedCallback(this, &JumpPointsExample::OnStopPoint3Selected)
    , m_onSP4SelectedCallback(this, &JumpPointsExample::OnStopPoint4Selected)
    , m_onSP5SelectedCallback(this, &JumpPointsExample::OnStopPoint5Selected)
    , m_onSP6SelectedCallback(this, &JumpPointsExample::OnStopPoint6Selected)
    , m_onSP7SelectedCallback(this, &JumpPointsExample::OnStopPoint7Selected)
    , m_isInInterior(false)
    {
        
        NotifyScreenPropertiesChanged(initialScreenProperties);
        Eegeo::m44 projectionMatrix = Eegeo::m44(pCameraController->GetRenderCamera().GetProjectionMatrix());
        m_pSplineCameraController = new Eegeo::VR::JumpPointsCameraController(initialScreenProperties.GetScreenWidth(), initialScreenProperties.GetScreenHeight());
        m_pSplineCameraController->GetCamera().SetProjectionMatrix(projectionMatrix);
        m_eyeDistance = 0.03f;
        
        m_pUIRenderableFilter = Eegeo_NEW(Eegeo::UI::UIRenderableFilter)();
        m_renderableFilters.AddRenderableFilter(*m_pUIRenderableFilter);
    }
    
    JumpPointsExample::~JumpPointsExample()
    {
    }
    
    void JumpPointsExample::Start()
    {
        
        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250);
        m_pSplineCameraController->SetStartLatLongAltitude(eyePosLla);
        m_pSplineCameraController->SetNearMultiplier(INTERIOR_NEAR_MULTIPLIER);
        
        Eegeo::v2 dimension = Eegeo::v2(50,50);
        Eegeo::v2 size(4,4);
        
        Eegeo::v2 outMin;
        Eegeo::v2 outMax;
        Eegeo::UI::CalculateUV(size, 0, outMin, outMax);
        dimension = Eegeo::v2(50,50);
        
        m_pWPJumpPoint1 = new Eegeo::UI::JumpPoints::JumpPoint(1,
                                                               Eegeo::Space::LatLongAltitude::FromDegrees(56.459935, -2.974200, 250),
                                                               "mesh_example/PinIconTexturePage.png",
                                                               dimension,
                                                               outMin,
                                                               outMax
                                                               );
        
        m_pWPJumpPoint2 = new Eegeo::UI::JumpPoints::JumpPoint(2,
                                                               Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250),
                                                               "mesh_example/PinIconTexturePage.png",
                                                               dimension,
                                                               outMin,
                                                               outMax
                                                               );
        
        m_pWPJumpPoint3 = new Eegeo::UI::JumpPoints::JumpPoint(3,
                                                               Eegeo::Space::LatLongAltitude::FromDegrees(56.451235, -2.976600, 250),
                                                               "mesh_example/PinIconTexturePage.png",
                                                               dimension,
                                                               outMin,
                                                               outMax
                                                               );
        
        m_pJumpPointsModule = new Eegeo::UI::JumpPoints::JumpPointsModule(*m_pUIRenderableFilter,
                                                                          m_uiQuadFactory,
                                                                          m_uiInteractionObservable,
                                                                          m_uiCameraProvider,
                                                                          m_interiorsExplorerModule);
        m_pJumpPointsModule->GetRepository().AddJumpPoint(m_pWPJumpPoint1);
        m_pJumpPointsModule->GetRepository().AddJumpPoint(m_pWPJumpPoint2);
        m_pJumpPointsModule->GetRepository().AddJumpPoint(m_pWPJumpPoint3);
        
        m_pSPButton1 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 3, m_onSP1SelectedCallback);
        m_pSPButton2 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 4, m_onSP2SelectedCallback);
        m_pSPButton3 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 5, m_onSP3SelectedCallback);
        m_pSPButton4 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 6, m_onSP4SelectedCallback);
        m_pSPButton5 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 7, m_onSP5SelectedCallback);
        m_pSPButton6 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 8, m_onSP6SelectedCallback);
        m_pSPButton7 = new Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem(10, 9, m_onSP7SelectedCallback);
        
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton1);
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton2);
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton3);
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton4);
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton5);
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton6);
        m_deadZoneMenuRepository.AddDeadZoneMenuItem(m_pSPButton7);
    }
    
    void JumpPointsExample::Suspend(){
        m_pJumpPointsModule->GetRepository().RemoveJumpPoint(m_pWPJumpPoint1);
        m_pJumpPointsModule->GetRepository().RemoveJumpPoint(m_pWPJumpPoint2);
        m_pJumpPointsModule->GetRepository().RemoveJumpPoint(m_pWPJumpPoint3);
        
        Eegeo_DELETE m_pWPJumpPoint1;
        Eegeo_DELETE m_pWPJumpPoint2;
        Eegeo_DELETE m_pWPJumpPoint3;
        Eegeo_DELETE m_pJumpPointsModule;
        
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton1);
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton2);
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton3);
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton4);
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton5);
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton6);
        m_deadZoneMenuRepository.RemoveDeadZoneMenuItem(m_pSPButton7);
        
        Eegeo_DELETE m_pSPButton1;
        Eegeo_DELETE m_pSPButton2;
        Eegeo_DELETE m_pSPButton3;
        Eegeo_DELETE m_pSPButton4;
        Eegeo_DELETE m_pSPButton5;
        Eegeo_DELETE m_pSPButton6;
        Eegeo_DELETE m_pSPButton7;
        
        Eegeo_DELETE m_pSplineCameraController;
        
        m_renderableFilters.RemoveRenderableFilter(*m_pUIRenderableFilter);
        Eegeo_DELETE m_pUIRenderableFilter;
    }
    
    void JumpPointsExample::UpdateCardboardProfile(float cardboardProfile[])
    {
        //9th parameter is eye distance in meters.
        m_eyeDistance = cardboardProfile[9]/2.0f;
    }
    
    void JumpPointsExample::EarlyUpdate(float dt)
    {
        
    }
    
    void JumpPointsExample::Update(float dt)
    {
        m_pJumpPointsModule->Update(dt);
        
        if (m_isInInterior)
        {
            m_interiorsExplorerModule.GetInteriorsExplorerModel().SelectFloor(2);
        }
    }
    
    
    void JumpPointsExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
    }
    
    
    const Eegeo::m33& JumpPointsExample::getCurrentCameraOrientation()
    {
        return m_pSplineCameraController->GetOrientation();
    }
    
    const Eegeo::m33& JumpPointsExample::GetBaseOrientation()
    {
        return m_pSplineCameraController->GetCameraOrientation();
    }
    
    const Eegeo::m33& JumpPointsExample::GetHeadTrackerOrientation()
    {
        return m_pSplineCameraController->GetHeadTrackerOrientation();
    }
    
    Eegeo::Camera::RenderCamera& JumpPointsExample::GetRenderCamera(){
        return m_pSplineCameraController->GetCamera();
    }
    
    Eegeo::Camera::CameraState JumpPointsExample::GetCurrentLeftCameraState(float headTansform[]) const
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
    
    Eegeo::Camera::CameraState JumpPointsExample::GetCurrentRightCameraState(float headTansform[]) const
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
    
    Eegeo::Camera::CameraState JumpPointsExample::GetCurrentCameraState() const
    {
        return m_pSplineCameraController->GetCameraState();
    }
    
    void JumpPointsExample::MoveCameraToStopPoint(const Eegeo::dv3 &cameraPoint, const Eegeo::dv3 &cameraLookat)
    {
        Eegeo::dv3 point = cameraLookat - cameraPoint;
        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(cameraPoint, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
        Eegeo::m33 orientation;
        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
        m_uiCameraProvider.GetRenderCameraForUI().SetEcefLocation(cameraPoint);
        m_pSplineCameraController->SetCameraOrientation(orientation);
        m_headTracker.ResetTracker();
    }
    
    void JumpPointsExample::MoveCameraToStopPoint(const Eegeo::dv3 &cameraPoint, float cameraHeading)
    {
        Eegeo::m33 orientation;
        Eegeo::Space::EcefTangentBasis basis;
        Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(cameraPoint, cameraHeading, basis);
        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
        m_uiCameraProvider.GetRenderCameraForUI().SetEcefLocation(cameraPoint);
        m_pSplineCameraController->SetCameraOrientation(orientation);
        m_headTracker.ResetTracker();
    }
    
    void JumpPointsExample::OnStopPoint1Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        if (visibilityUpdater.GetInteriorShouldDisplay())
        {
            visibilityUpdater.SetInteriorShouldDisplay(false);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = false;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(37.795185, -122.402780, 305).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(37.791775, -122.402423, 305).ToECEF();
        
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
    }
    
    void JumpPointsExample::OnStopPoint2Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        if (visibilityUpdater.GetInteriorShouldDisplay())
        {
            visibilityUpdater.SetInteriorShouldDisplay(false);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = false;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(37.7955670, -122.3806140, 250).ToECEF();
        MoveCameraToStopPoint(cameraPoint, 246.88382);
    }
    
    void JumpPointsExample::OnStopPoint3Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        if (visibilityUpdater.GetInteriorShouldDisplay())
        {
            visibilityUpdater.SetInteriorShouldDisplay(false);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = false;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.456870, -2.957510, 304).ToECEF();
        MoveCameraToStopPoint(cameraPoint, 294.33133);
    }
    
    void JumpPointsExample::OnStopPoint4Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        if (visibilityUpdater.GetInteriorShouldDisplay())
        {
            visibilityUpdater.SetInteriorShouldDisplay(false);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = false;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(40.699799, -74.021058, 380).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(40.702531, -74.015483, 380).ToECEF();
        
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
    }
    
    void JumpPointsExample::OnStopPoint5Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        if (visibilityUpdater.GetInteriorShouldDisplay())
        {
            visibilityUpdater.SetInteriorShouldDisplay(false);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = false;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(40.763647, -73.973468, 25).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(40.764722, -73.972690, 25).ToECEF();
        
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
    }
    
    void JumpPointsExample::OnStopPoint6Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        m_interiorsExplorerModule.GetInteriorsExplorerModel().SelectFloor(2);
        
        if (!visibilityUpdater.GetInteriorShouldDisplay()) {
            visibilityUpdater.SetInteriorShouldDisplay(true);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = true;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459928, -2.978063, 28.5).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(56.459921, -2.978145, 28.5).ToECEF();
            
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
        
    }
    
    void JumpPointsExample::OnStopPoint7Selected()
    {
        InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
        
        m_interiorsExplorerModule.GetInteriorsExplorerModel().SelectFloor(2);
        
        if (!visibilityUpdater.GetInteriorShouldDisplay()) {
            visibilityUpdater.SetInteriorShouldDisplay(true);
            visibilityUpdater.UpdateVisiblityImmediately();
        }
        
        m_isInInterior = true;
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459908, -2.978208, 28.5).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(56.460026, -2.978270, 28.5).ToECEF();
            
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
        
    }
}
