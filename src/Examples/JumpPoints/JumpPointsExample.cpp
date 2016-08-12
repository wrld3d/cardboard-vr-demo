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
#include "Modules/UI/Animations/AnimationsController.h"
#include "Modules/UI/Animations/IDv3Animateable.h"
#include "Modules/UI/Animations/Dv3PropertyAnimation.h"
#include "Modules/UI/Animations/AnimationEase.h"
#include "Modules/InteriorsExplorerModule/InteriorsExplorerModule.h"
#include "Modules/WorldMenu/WorldMenuModule.h"

#include "WorldMenuController.h"
#include "JumpPointConfigData.h"

#define INTERIOR_NEAR_MULTIPLIER 0.025f
#define EXTERIOR_NEAR_MULTIPLIER 0.1f

const float WelcomeMessageFadeSpeed = 0.5f;

const float InteriorMenuFloorAngleThreshold = 70.f;
const float InteriorMenuHighPositionAngleThreshold = 100.f;

const float WelcomeNoteDistanceFromCamera = 50.f;

#include "Logger.h"

namespace Examples
{
    void DeleteJumpPoint(Eegeo::UI::JumpPoints::JumpPoint* pJumpPoint)
    {
        Eegeo_DELETE pJumpPoint;
    }

    Eegeo::UI::JumpPoints::JumpPoint* GetJumpPointFromConfigData(const ApplicationConfig::JumpPointConfigData& jumpPointData, const std::string& spriteSheetPath, const Eegeo::v2& spriteSheetSize, bool isInInterior)
    {
        Eegeo::v2 outMin;
        Eegeo::v2 outMax;
        Eegeo::UI::CalculateUV(spriteSheetSize, jumpPointData.GetIconID(), outMin, outMax);

        Eegeo::UI::JumpPoints::TJumpPointsVector jpVector;

        for (ApplicationConfig::TJumpPointVector::const_iterator it = jumpPointData.GetChildJumpPoints().begin(); it != jumpPointData.GetChildJumpPoints().end(); ++it)
        {
            jpVector.push_back(GetJumpPointFromConfigData(*it, spriteSheetPath, spriteSheetSize, isInInterior));
        }

        Eegeo::UI::JumpPoints::JumpPoint* pJumpPoint = Eegeo_NEW(Eegeo::UI::JumpPoints::JumpPoint)(jumpPointData.GetID(),
                                                                                                  jumpPointData.GetJumpPointLocation(),
                                                                                                  spriteSheetPath,
                                                                                                  Eegeo::v2(jumpPointData.GetSize(),jumpPointData.GetSize()),
                                                                                                  outMin,
                                                                                                  outMax,
                                                                                                  isInInterior
                                                                                                  );
        pJumpPoint->SetChildJumpPoints(jpVector);
        return pJumpPoint;
    }

    JumpPointsExample::JumpPointsExample(Eegeo::EegeoWorld& eegeoWorld,
                                         Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                         Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                         const Eegeo::Rendering::ScreenProperties& initialScreenProperties,
                                         Eegeo::UI::IUIQuadFactory& quadFactory,
                                         Eegeo::UI::IUIInteractionObservable& uiInteractionObservable,
                                         Eegeo::UI::IUICameraProvider& uiCameraProvider,
                                         InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                         Eegeo::UI::DeadZoneMenu::DeadZoneMenuItemRepository& deadZoneMenuRepository,
                                         Eegeo::UI::Animations::AnimationsController& animationsController,
                                         Eegeo::UI::WorldMenu::WorldMenuModule& worldMenuModule,
                                         WorldMenuLoader::SdkModel::WorldMenuLoaderModel& menuLoader,
                                         IVRHeadTracker& headTracker,
                                         const Examples::ApplicationConfig::ApplicationConfiguration& appConfig)
    : m_world(eegeoWorld)
    , m_uiQuadFactory(quadFactory)
    , m_uiInteractionObservable(uiInteractionObservable)
    , m_uiCameraProvider(uiCameraProvider)
    , m_renderableFilters(eegeoWorld.GetRenderingModule().GetRenderableFilters())
    , m_interiorsExplorerModule(interiorsExplorerModule)
    , m_deadZoneMenuRepository(deadZoneMenuRepository)
    , m_animationsController(animationsController)
    , m_worldMenuModule(worldMenuModule)
    , m_menuLoader(menuLoader)
    , m_headTracker(headTracker)
    , m_appConfig(appConfig)
    , m_onSP1SelectedCallback(this, &JumpPointsExample::OnStopPoint1Selected)
    , m_onSP2SelectedCallback(this, &JumpPointsExample::OnStopPoint2Selected)
    , m_onSP3SelectedCallback(this, &JumpPointsExample::OnStopPoint3Selected)
    , m_onSP4SelectedCallback(this, &JumpPointsExample::OnStopPoint4Selected)
    , m_onSP5SelectedCallback(this, &JumpPointsExample::OnStopPoint5Selected)
    , m_onSP6SelectedCallback(this, &JumpPointsExample::OnStopPoint6Selected)
    , m_onSP7SelectedCallback(this, &JumpPointsExample::OnStopPoint7Selected)
    , m_onWestPortEntryButtonCallback(this, &JumpPointsExample::OnWestportInteriorButtonSelected)
    , m_onInteriorFloorChanged(this, &JumpPointsExample::OnInteriorFloorChanged)
    , m_onJumpPointSelected(this, &JumpPointsExample::OnJumpPointSelected)
    , m_locationChangedCallback(this, &JumpPointsExample::OnLocationChanged)
    , m_interiorMenuItemSelected(this, &JumpPointsExample::OnFloorMenuItemSelected)
    , m_isInInterior(false)
    , m_isAtFloorLevel(false)
    {
        
        NotifyScreenPropertiesChanged(initialScreenProperties);
        Eegeo::m44 projectionMatrix = Eegeo::m44(pCameraController->GetRenderCamera().GetProjectionMatrix());
        m_pSplineCameraController = Eegeo_NEW(Eegeo::VR::JumpPointsCameraController)(initialScreenProperties.GetScreenWidth(), initialScreenProperties.GetScreenHeight());
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
        m_isCameraAnimating = false;
        
        m_progressBarConfig.textureFilename = "mesh_example/gaze_loader.png";
        m_progressBarConfig.frameRate = 49.f/2.f;
        m_progressBarConfig.spriteGridSize = Eegeo::v2(7,7);
        m_progressBarConfig.spriteId = 0;
        m_progressBarConfig.color = Eegeo::v4::One();
        m_progressBarConfig.renderLayer = Eegeo::Rendering::LayerIds::Values::AfterAll;

        m_pSplineCameraController->SetNearMultiplier(INTERIOR_NEAR_MULTIPLIER);
        
        Eegeo::v2 dimension = Eegeo::v2(50,50);
        const Eegeo::v2 size(m_appConfig.JumpPointsSpriteSheetSize(), m_appConfig.JumpPointsSpriteSheetSize());
        
        Eegeo::v2 outMin;
        Eegeo::v2 outMax;
        Eegeo::UI::CalculateUV(size, 0, outMin, outMax);
        dimension = Eegeo::v2(50,50);
        
        m_pJumpPointsModule = Eegeo_NEW(Eegeo::UI::JumpPoints::JumpPointsModule)(*m_pUIRenderableFilter,
                                                                          m_uiQuadFactory,
                                                                          m_uiInteractionObservable,
                                                                          m_uiCameraProvider,
                                                                          m_progressBarConfig,
                                                                          m_onJumpPointSelected);
        
        LoadInteriorJumpPoints(m_appConfig.GetInteriorJumpPoints());
        LoadExteriorJumpPoints(m_appConfig.GetExteriorJumpPoints());

        m_pJumpPointSwitcher = Eegeo_NEW(JumpPointsSwitcher)(m_pJumpPointsModule->GetRepository(), m_interiorsExplorerModule, m_exteriorJumpPoints, m_interiorJumpPoints);

        m_pSPButton1 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 3, m_onSP1SelectedCallback);
        m_pSPButton2 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 4, m_onSP2SelectedCallback);
        m_pSPButton3 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 5, m_onSP3SelectedCallback);
        m_pSPButton4 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 6, m_onSP4SelectedCallback);
        m_pSPButton5 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 7, m_onSP5SelectedCallback);
        m_pSPButton6 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 8, m_onSP6SelectedCallback);
        m_pSPButton7 = Eegeo_NEW(Eegeo::UI::DeadZoneMenu::DeadZoneMenuItem)(10, 9, m_onSP7SelectedCallback);
        
        Eegeo::UI::CalculateUV(size, 14, outMin, outMax);
        m_pWestPortInteriorButton = Eegeo_NEW(Eegeo::UI::UIProgressButton)(*m_pUIRenderableFilter,
                                                                           m_uiQuadFactory,
                                                                           m_appConfig.JumpPointsSpriteSheet(),
                                                                           m_progressBarConfig,
                                                                           m_onWestPortEntryButtonCallback,
                                                                           dimension / 2.0f,
                                                                           Eegeo::Space::LatLongAltitude::FromDegrees(56.459928, -2.978063, 28.5).ToECEF(),
                                                                           Eegeo::v3::One(),
                                                                           Eegeo::v4::One(),
                                                                           outMin,
                                                                           outMax);
        
        m_uiInteractionObservable.RegisterInteractableItem(m_pWestPortInteriorButton);

        m_menuLoader.RegisterLocationChangedCallback(m_locationChangedCallback);
        ChangeLocation(m_menuLoader.GetCurrentSelectedLocation());

        m_pWelcomeNoteViewer = Eegeo_NEW(WelcomeNoteViewer)(m_uiQuadFactory, *m_pUIRenderableFilter);

        m_interiorsExplorerModule.RegisterMenuItemGazedCallback(m_interiorMenuItemSelected);
    }
    
    void JumpPointsExample::Suspend()
    {
        Eegeo_DELETE m_pWelcomeNoteViewer;

        if(m_isInInterior)
        {
            m_interiorsExplorerModule.UnregisterVisibilityChangedCallback(m_onInteriorFloorChanged);
        }

        m_interiorsExplorerModule.UnregisterMenuItemGazedCallback(m_interiorMenuItemSelected);
        m_menuLoader.UnregisterLocationChangedCallback(m_locationChangedCallback);

        Eegeo_DELETE m_pJumpPointSwitcher;
        m_uiInteractionObservable.UnRegisterInteractableItem(m_pWestPortInteriorButton);
        Eegeo_DELETE m_pWestPortInteriorButton;
        
        m_pJumpPointsModule->GetRepository().RemoveAllJumpPoints();
        for (TInteriorJumpPointsData::const_iterator itInterior = m_interiorJumpPoints.begin(); itInterior != m_interiorJumpPoints.end(); ++itInterior)
        {
            const TInteriorFloorJumpPointsData& jpFloorData = itInterior->second;

            for (TInteriorFloorJumpPointsData::const_iterator itFloorData = jpFloorData.begin(); itFloorData != jpFloorData.end(); ++itFloorData)
            {
                std::for_each(itFloorData->second.begin(), itFloorData->second.end(), DeleteJumpPoint);
            }
        }
        m_interiorJumpPoints.clear();

        for (TExteriorJumpPointsData::const_iterator itExterior = m_exteriorJumpPoints.begin(); itExterior != m_exteriorJumpPoints.end(); ++itExterior)
        {
            const TJumpPointsDataVector& jpVector = itExterior->second;
            std::for_each(jpVector.begin(), jpVector.end(), DeleteJumpPoint);
        }

        m_exteriorJumpPoints.clear();

        Eegeo_DELETE m_pJumpPointsModule;
        
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

    void JumpPointsExample::Draw()
    {

    }
    
    void JumpPointsExample::Update(float dt)
    {
        m_pJumpPointsModule->Update(dt);
        
        m_pWestPortInteriorButton->Update(dt);

        m_pWelcomeNoteViewer->Update(dt);

        m_pJumpPointSwitcher->Update(dt);
    }

    void JumpPointsExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
    }

    void JumpPointsExample::LoadInteriorJumpPoints(const ApplicationConfig::TInteriorJumpPoints& interiorJumpPoints)
    {
        Eegeo::v2 spriteSheetSize(m_appConfig.JumpPointsSpriteSheetSize(), m_appConfig.JumpPointsSpriteSheetSize());

        for (ApplicationConfig::TInteriorJumpPoints::const_iterator itJumpPoints = interiorJumpPoints.begin(); itJumpPoints != interiorJumpPoints.end(); ++itJumpPoints)
        {
            TInteriorFloorJumpPointsData floorData;

            const ApplicationConfig::TInteriorFloorJumpPoints& floorJumpPointsConfigData = (itJumpPoints->second);

            for (ApplicationConfig::TInteriorFloorJumpPoints::const_iterator itFloorJPs = floorJumpPointsConfigData.begin(); itFloorJPs != floorJumpPointsConfigData.end(); ++itFloorJPs)
            {
                TJumpPointsDataVector dataVector;

                const ApplicationConfig::TJumpPointVector& jumpPointConfigVector = itFloorJPs->second;

                for (ApplicationConfig::TJumpPointVector::const_iterator it = jumpPointConfigVector.begin(); it != jumpPointConfigVector.end(); ++it)
                {
                    dataVector.push_back(GetJumpPointFromConfigData(*it, m_appConfig.JumpPointsSpriteSheet(), spriteSheetSize, true));
                }

                floorData[itFloorJPs->first] = dataVector;
            }

            m_interiorJumpPoints[itJumpPoints->first] = floorData;
        }
    }

    void JumpPointsExample::LoadExteriorJumpPoints(const ApplicationConfig::TExteriorJumpPoints &exteriorJumpPoints)
    {
        Eegeo::v2 spriteSheetSize(m_appConfig.JumpPointsSpriteSheetSize(), m_appConfig.JumpPointsSpriteSheetSize());

        for (ApplicationConfig::TExteriorJumpPoints::const_iterator itLocationJPs = exteriorJumpPoints.begin(); itLocationJPs != exteriorJumpPoints.end(); ++itLocationJPs)
        {
            TJumpPointsDataVector dataVector;

            const ApplicationConfig::TJumpPointVector& jumpPointConfigVector = itLocationJPs->second;

            for (ApplicationConfig::TJumpPointVector::const_iterator it = jumpPointConfigVector.begin(); it != jumpPointConfigVector.end(); ++it)
            {
                dataVector.push_back(GetJumpPointFromConfigData(*it, m_appConfig.JumpPointsSpriteSheet(), spriteSheetSize, false));
            }

            m_exteriorJumpPoints[itLocationJPs->first] = dataVector;
        }
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
        HideInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(37.795185, -122.402780, 305).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(37.791775, -122.402423, 305).ToECEF();
        
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
    }
    
    void JumpPointsExample::OnStopPoint2Selected()
    {
        HideInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(37.7955670, -122.3806140, 250).ToECEF();
        MoveCameraToStopPoint(cameraPoint, 246.88382);
    }
    
    void JumpPointsExample::OnStopPoint3Selected()
    {
        HideInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.456870, -2.957510, 304).ToECEF();
        MoveCameraToStopPoint(cameraPoint, 294.33133);
    }
    
    void JumpPointsExample::OnStopPoint4Selected()
    {
        HideInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(40.699799, -74.021058, 380).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(40.702531, -74.015483, 380).ToECEF();
        
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
    }
    
    void JumpPointsExample::OnStopPoint5Selected()
    {
        HideInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(40.763647, -73.973468, 25).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(40.764722, -73.972690, 25).ToECEF();
        
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
    }
    
    void JumpPointsExample::OnStopPoint6Selected()
    {
        ShowInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459928, -2.978063, 28.5).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(56.459921, -2.978145, 28.5).ToECEF();
            
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
        
    }
    
    void JumpPointsExample::OnStopPoint7Selected()
    {
        ShowInteriors();
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459908, -2.978208, 28.5).ToECEF();
        Eegeo::dv3 cameraLookat = Eegeo::Space::LatLongAltitude::FromDegrees(56.460026, -2.978270, 28.5).ToECEF();
            
        MoveCameraToStopPoint(cameraPoint, cameraLookat);
        
    }
    
    void JumpPointsExample::OnWestportInteriorButtonSelected()
    {
        ShowInteriors();
        
        Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459809, -2.977735, 40).ToECEF();
        
        m_animationsController.RemoveAnimationsForTag(0);
        Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Eegeo::UI::Animations::Dv3PropertyAnimation)(*m_pSplineCameraController, this, m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), cameraPoint, 5.0f, &Eegeo::UI::AnimationEase::EaseInOutCubic);
        animation->SetTag(0);
        m_animationsController.AddAnimation(animation);
        
        m_interiorsExplorerModule.RegisterVisibilityChangedCallback(m_onInteriorFloorChanged);
    }
    
    void JumpPointsExample::ShowInteriors()
    {
        if(m_isInInterior)
            return;
        
        m_isInInterior = true;
        m_interiorsExplorerModule.ShowInteriors();
        m_pWestPortInteriorButton->SetItemShouldRender(false);
        m_worldMenuModule.SetMenuShouldDisplay(false);
        m_interiorsExplorerModule.SetMenuVisibilityThresholdAngle(InteriorMenuHighPositionAngleThreshold);
    }
    
    void JumpPointsExample::HideInteriors()
    {
        if(!m_isInInterior)
            return;
        
        m_isInInterior = false;
        m_interiorsExplorerModule.HideInteriors();
        m_pWestPortInteriorButton->SetItemShouldRender(true);
    }
    
    void JumpPointsExample::OnAnimationProgress(Eegeo::UI::Animations::IAnimation& animation){}
    void JumpPointsExample::OnAnimationAdded(Eegeo::UI::Animations::IAnimation& animation)
    {
        m_isCameraAnimating = true;
    }
    
    void JumpPointsExample::OnAnimationRemoved(Eegeo::UI::Animations::IAnimation& animation)
    {
        m_isCameraAnimating = false;
    }
    
    void JumpPointsExample::OnJumpPointSelected(Eegeo::UI::JumpPoints::JumpPoint& jumpPoint)
    {
        
        if(m_isCameraAnimating)
            return;
        
        float time = 5.f;
        if(m_isInInterior)
            time = 1.5f;

        m_pWestPortInteriorButton->SetItemShouldRender(!jumpPoint.GetIsInInterior());

        m_pJumpPointsModule->GetController().ResetVisibility();
        jumpPoint.SetVisibilityStatus(false);

        m_animationsController.RemoveAnimationsForTag(0);
        Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Eegeo::UI::Animations::Dv3PropertyAnimation)(*m_pSplineCameraController, this,m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), jumpPoint.GetEcefPosition(), time, &Eegeo::UI::AnimationEase::EaseInOutCubic);
        animation->SetTag(0);
        m_animationsController.AddAnimation(animation);

        if (m_isInInterior && !m_isAtFloorLevel)
        {
            m_pJumpPointSwitcher->SwitchJumpPoints(jumpPoint.GetChildJumpPoints(), time/2.f);
        }

        m_isAtFloorLevel = m_isInInterior;

        if (m_isAtFloorLevel)
        {
            m_interiorsExplorerModule.SetMenuVisibilityThresholdAngle(InteriorMenuFloorAngleThreshold);

        }
        else
        {
            m_interiorsExplorerModule.SetMenuVisibilityThresholdAngle(InteriorMenuHighPositionAngleThreshold);
        }
    }
    
    void JumpPointsExample::OnInteriorFloorChanged()
    {
    }

    void JumpPointsExample::ChangeLocation(const std::string &location)
    {
        const ApplicationConfig::WorldLocationData& currentLocation = m_appConfig.GetLocations().at(location);
        m_pSplineCameraController->SetStartLatLongAltitude(currentLocation.GetLocationCameraPosition(), currentLocation.GetOrientation());
        m_pJumpPointSwitcher->SwitchLocation(location);
    }

    void JumpPointsExample::OnLocationChanged(std::string &location)
    {
        m_pWelcomeNoteViewer->ShowWelcomeNote(m_appConfig.GetLocations().at(location).GetWelcomeMessage(), WelcomeMessageFadeSpeed, 2.f, Eegeo::v2(15,5));
        ChangeLocation(location);

        Eegeo::v3 forward = Eegeo::v3::Cross(m_pSplineCameraController->GetOrientation().GetRow(0), m_pSplineCameraController->GetCameraPosition().ToSingle().Norm());
        Eegeo::dv3 position(m_pSplineCameraController->GetCameraPosition() + (forward*WelcomeNoteDistanceFromCamera));
        m_pWelcomeNoteViewer->SetPosition(position);
    }

    void JumpPointsExample::OnFloorMenuItemSelected(InteriorsExplorer::InteriorMenu::InteriorMenuItem& menuItem)
    {
        if (menuItem.GetId() < 0)
        {
            if (m_isAtFloorLevel)
            {
                Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459809, -2.977735, 40+(5*m_interiorsExplorerModule.GetSelectedFloor())).ToECEF();
                m_animationsController.RemoveAnimationsForTag(0);
                Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Eegeo::UI::Animations::Dv3PropertyAnimation)(*m_pSplineCameraController, this, m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), cameraPoint, 3.5f, &Eegeo::UI::AnimationEase::EaseInOutCubic);
                animation->SetTag(0);
                m_animationsController.AddAnimation(animation);
                m_isAtFloorLevel = false;
                m_interiorsExplorerModule.SetMenuVisibilityThresholdAngle(InteriorMenuHighPositionAngleThreshold);
                m_pJumpPointSwitcher->ReloadJumpPoints();
            }
            else
            {
                m_isAtFloorLevel = false;
                m_isInInterior = false;
                m_pWestPortInteriorButton->SetItemShouldRender(true);

                m_worldMenuModule.SetMenuShouldDisplay(true);

                Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459156, -2.975320, 300).ToECEF();

                m_animationsController.RemoveAnimationsForTag(0);
                Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Eegeo::UI::Animations::Dv3PropertyAnimation)(*m_pSplineCameraController, this, m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), cameraPoint, 3.5f, &Eegeo::UI::AnimationEase::EaseInOutExpo);
                animation->SetTag(0);
                m_animationsController.AddAnimation(animation);
                m_interiorsExplorerModule.UnregisterVisibilityChangedCallback(m_onInteriorFloorChanged);
                m_interiorsExplorerModule.HideInteriors();
            }
        }
        else
        {
            m_interiorsExplorerModule.SelectFloor(menuItem.GetId());

            if(m_interiorsExplorerModule.GetSelectedFloor()>=0)
            {
                Eegeo::dv3 cameraPoint = Eegeo::Space::LatLongAltitude::FromDegrees(56.459809, -2.977735, 40+(5*m_interiorsExplorerModule.GetSelectedFloor())).ToECEF();
                m_animationsController.RemoveAnimationsForTag(0);
                Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Eegeo::UI::Animations::Dv3PropertyAnimation)(*m_pSplineCameraController, this, m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), cameraPoint, 1.5f, &Eegeo::UI::AnimationEase::EaseInOutExpo);
                animation->SetTag(0);
                m_animationsController.AddAnimation(animation);
                m_isAtFloorLevel = false;
                m_interiorsExplorerModule.SetMenuVisibilityThresholdAngle(InteriorMenuHighPositionAngleThreshold);
            }
        }

        m_pJumpPointsModule->GetController().ResetVisibility();
    }

}
