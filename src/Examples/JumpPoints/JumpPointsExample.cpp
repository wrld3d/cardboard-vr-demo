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

#define INTERIOR_NEAR_MULTIPLIER 0.025f
#define EXTERIOR_NEAR_MULTIPLIER 0.1f

#include "Logger.h"

namespace Examples
{
    JumpPointsExample::JumpPointsExample(Eegeo::EegeoWorld& eegeoWorld,
                                         Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraController* cameraController,
                                         const Eegeo::Rendering::ScreenProperties& initialScreenProperties,
                                         Eegeo::UI::IUIQuadFactory& quadFactory,
                                         Eegeo::UI::IUIInteractionObservable& uIInteractionObservable,
                                         Eegeo::UI::IUICameraProvider& uICameraProvider)
    : m_world(eegeoWorld)
    , m_UIQuadFactory(quadFactory)
    , m_UIInteractionObservable(uIInteractionObservable)
    , m_UICameraProvider(uICameraProvider)
    {
        
        NotifyScreenPropertiesChanged(initialScreenProperties);
        Eegeo::m44 projectionMatrix = Eegeo::m44(cameraController->GetRenderCamera().GetProjectionMatrix());
        m_pSplineCameraController = new Eegeo::VR::JumpPointsCameraController(initialScreenProperties.GetScreenWidth(), initialScreenProperties.GetScreenHeight());
        m_pSplineCameraController->GetCamera()->SetProjectionMatrix(projectionMatrix);
        m_eyeDistance = 0.03f;
        
        
        
    }
    
    JumpPointsExample::~JumpPointsExample(){
        Eegeo_DELETE m_JumpPoint1;
        Eegeo_DELETE m_JumpPoint2;
        Eegeo_DELETE m_JumpPoint3;
        Eegeo_DELETE m_JumpPointsModule;
    }
    
    void JumpPointsExample::Start()
    {
        
        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250);
        m_pSplineCameraController->SetStartLatLongAltitude(eyePosLla);
        
        Eegeo::v2 dimension = Eegeo::v2(50,50);
        Eegeo::v2 size(4,4);
        
        Eegeo::v2 outMin;
        Eegeo::v2 outMax;
        Eegeo::UI::CalculateUV(size, 0, outMin, outMax);
        dimension = Eegeo::v2(50,50);
        
        m_JumpPoint1 = new Eegeo::UI::JumpPoints::JumpPoint(1,
                                                            Eegeo::Space::LatLongAltitude::FromDegrees(56.459935, -2.974200, 250),
                                                            "mesh_example/PinIconTexturePage.png",
                                                            dimension,
                                                            outMin,
                                                            outMax
                                                            );
        
        m_JumpPoint2 = new Eegeo::UI::JumpPoints::JumpPoint(2,
                                                            Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250),
                                                            "mesh_example/PinIconTexturePage.png",
                                                            dimension,
                                                            outMin,
                                                            outMax
                                                            );
        
        m_JumpPoint3 = new Eegeo::UI::JumpPoints::JumpPoint(3,
                                                            Eegeo::Space::LatLongAltitude::FromDegrees(56.451235, -2.976600, 250),
                                                            "mesh_example/PinIconTexturePage.png",
                                                            dimension,
                                                            outMin,
                                                            outMax
                                                            );
        
        m_JumpPointsModule = new Eegeo::UI::JumpPoints::JumpPointsModule(m_UIQuadFactory,
                                                                         m_UIInteractionObservable,
                                                                         m_UICameraProvider);
        m_JumpPointsModule->GetRepository().AddJumpPoint(m_JumpPoint1);
        m_JumpPointsModule->GetRepository().AddJumpPoint(m_JumpPoint2);
        m_JumpPointsModule->GetRepository().AddJumpPoint(m_JumpPoint3);
        
        
    }
    
    void JumpPointsExample::Suspend(){}
    
    void JumpPointsExample::UpdateCardboardProfile(float cardboardProfile[])
    {
        //9th parameter is eye distance in meters.
        m_eyeDistance = cardboardProfile[9]/2.0f;
    }
    
    void JumpPointsExample::EarlyUpdate(float dt)
    {
        
    }
    
    void JumpPointsExample::Update(float dt) {
    
        m_JumpPointsModule->Update(dt);
    }
    
    
    void JumpPointsExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
    }
    
    
    Eegeo::m33& JumpPointsExample::getCurrentCameraOrientation()
    {
        return m_pSplineCameraController->GetOrientation();
    }
    
    Eegeo::Camera::RenderCamera* JumpPointsExample::GetRenderCamera(){
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
}
