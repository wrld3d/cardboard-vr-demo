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
#include "WorldLocationData.h"

#define INTERIOR_NEAR_MULTIPLIER 0.025f
#define EXTERIOR_NEAR_MULTIPLIER 0.1f

#include "Logger.h"

namespace Examples
{
    const float WelcomeMessageFadeSpeed = 0.5f;
    const float WelcomeMessageFadeDelay = 4.0f;
    const Eegeo::v2 WelcomeMessageSize = Eegeo::v2(48,5);
    const float WelcomeNoteDistanceFromCamera = 50.f;

    VRCameraSplineExample::VRCameraSplineExample(Eegeo::EegeoWorld& eegeoWorld,
                                                 Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                                                 Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                 IVRHeadTracker& headTracker,
                                                 const Eegeo::Rendering::ScreenProperties& initialScreenProperties,
                                                 InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                                                 Eegeo::UI::IUIQuadFactory& quadFactory,
                                                 ScreenFadeEffect::SdkModel::IScreenFadeEffectController& screenFader,
                                                 const ApplicationConfig::ApplicationConfiguration& appConfig)
    : m_world(eegeoWorld),
      m_interiorsExplorerModule(interiorsExplorerModule),
      m_uiQuadFactory(quadFactory),
      m_screenFader(screenFader),
      m_renderableFilters(eegeoWorld.GetRenderingModule().GetRenderableFilters()),
      m_onSplineEndedCallback(this, &VRCameraSplineExample::OnSplineEnded),
      m_screenVisibilityChanged(this, &VRCameraSplineExample::OnScreenVisiblityChanged),
      m_splineChanged(false),
      m_pUIRenderableFilter(NULL),
      m_pWelcomeNoteViewer(NULL),
      m_welcomeNoteEcefPosition(Eegeo::dv3::Zero()),
      m_cameraCachedPosition(Eegeo::dv3::Zero())
    {
        NotifyScreenPropertiesChanged(initialScreenProperties);
        Eegeo::m44 projectionMatrix = Eegeo::m44(pCameraController->GetRenderCamera().GetProjectionMatrix());
        m_pSplineCameraController = new Eegeo::VR::VRCameraController(initialScreenProperties.GetScreenWidth(),
                                                                      initialScreenProperties.GetScreenHeight(),
                                                                      0.03f,
                                                                      headTracker,
                                                                      appConfig.UKWelcomeNotePath(),
                                                                      appConfig.SFWelcomeNotePath(),
                                                                      appConfig.NYWelcomeNotePath(),
                                                                      appConfig.UKSplineWelcomeNotePath(),
                                                                      appConfig.SFSplineWelcomeNotePath(),
                                                                      appConfig.NYSplineWelcomeNotePath());
        m_pSplineCameraController->GetCamera().SetProjectionMatrix(projectionMatrix);

        m_pUIRenderableFilter = Eegeo_NEW(Eegeo::UI::UIRenderableFilter)();
        m_pWelcomeNoteViewer = Eegeo_NEW(WelcomeNoteViewer)(m_uiQuadFactory, *m_pUIRenderableFilter);

        Eegeo::VR::VRCameraPositionSpline& vrCameraPositionSpline = m_pSplineCameraController->GetVRCameraPositionSpline();

        vrCameraPositionSpline.Start();
    }
    
    VRCameraSplineExample::~VRCameraSplineExample()
    {
        Eegeo_DELETE m_pWelcomeNoteViewer;

        Eegeo_DELETE m_pUIRenderableFilter;

        Eegeo_DELETE m_pSplineCameraController;
    }
    
    void VRCameraSplineExample::Start()
    {
        m_renderableFilters.AddRenderableFilter(*m_pUIRenderableFilter);
        
        Eegeo::Space::LatLongAltitude eyePosLla = Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250);
        m_pSplineCameraController->SetStartLatLongAltitude(eyePosLla, 0.f);

        m_pSplineCameraController->RegisterSplineFinishedCallback(m_onSplineEndedCallback);
        m_screenFader.RegisterVisibilityChangedCallback(m_screenVisibilityChanged);

        ShowWelcomeNote();
    }
    
    void VRCameraSplineExample::Suspend()
    {
        m_screenFader.UnregisterVisibilityChangedCallback(m_screenVisibilityChanged);
        m_pSplineCameraController->UnregisterSplineFinishedCallback(m_onSplineEndedCallback);

        m_interiorsExplorerModule.ForceLeaveInterior();

        m_renderableFilters.RemoveRenderableFilter(*m_pUIRenderableFilter);

    }

    void VRCameraSplineExample::OnSplineEnded()
    {
        m_screenFader.SetShouldFadeToBlack(true);
        m_splineChanged = true;
    }

    void VRCameraSplineExample::ShowWelcomeNote()
    {
        if (m_pSplineCameraController->GetVRCameraPositionSpline().GetCurrentSplineHasWelcomeNote())
        {
            m_pWelcomeNoteViewer->ShowWelcomeNote(m_pSplineCameraController->GetVRCameraPositionSpline().GetCurrentSplineWelcomeNote(),
                                                  WelcomeMessageFadeSpeed,
                                                  WelcomeMessageFadeDelay,
                                                  WelcomeMessageSize);
            Eegeo::v3 forward = Eegeo::v3::Cross(m_pSplineCameraController->GetOrientation().GetRow(0), m_pSplineCameraController->GetCameraPosition().ToSingle().Norm());
            m_cameraCachedPosition = m_pSplineCameraController->GetCameraPosition();
            m_welcomeNoteEcefPosition = (m_pSplineCameraController->GetCameraPosition() + (forward*WelcomeNoteDistanceFromCamera));
            m_pWelcomeNoteViewer->SetPosition(m_welcomeNoteEcefPosition);
        }
    }
    
    void VRCameraSplineExample::UpdateCardboardProfile(const float cardboardProfile[])
    {
        //9th parameter is eye distance in meters.
        m_pSplineCameraController->SetEyeDistance(cardboardProfile[9]/2.0f);
    }
    
    void VRCameraSplineExample::EarlyUpdate(float dt)
    {
        m_pSplineCameraController->Update(dt);

        if (m_pSplineCameraController->GetVRCameraPositionSpline().IsInteriorSpline())
        {
            m_pSplineCameraController->SetNearMultiplier(INTERIOR_NEAR_MULTIPLIER);
            m_interiorsExplorerModule.ForceEnterInterior(2);
        }
        else
        {
            m_pSplineCameraController->SetNearMultiplier(EXTERIOR_NEAR_MULTIPLIER);
            m_interiorsExplorerModule.ForceLeaveInterior();
        }

    }

    void VRCameraSplineExample::Update(float dt)
    {
        m_pWelcomeNoteViewer->Update(dt);
        m_cameraCachedPosition = m_pSplineCameraController->GetCameraPosition();
        Eegeo::v3 forward = m_pSplineCameraController->GetOrientation().GetRow(2);
        m_welcomeNoteEcefPosition = (m_pSplineCameraController->GetCameraPosition() + (forward*WelcomeNoteDistanceFromCamera));
        m_pWelcomeNoteViewer->SetPosition(m_welcomeNoteEcefPosition);
    }

    void VRCameraSplineExample::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
    }
    
    Eegeo::Camera::RenderCamera& VRCameraSplineExample::GetRenderCamera(){
        return m_pSplineCameraController->GetCamera();
    }

    void VRCameraSplineExample::UpdateHeadOrientation(const float headTansform[])
    {
        m_pSplineCameraController->UpdateHeadOrientation(headTansform);
    }
    
    Eegeo::Camera::CameraState VRCameraSplineExample::GetCurrentCameraState() const
    {
        return m_pSplineCameraController->GetCameraState();
    }

    const Eegeo::VRCamera::VRCameraState& VRCameraSplineExample::GetCurrentVRCameraState()
    {
        return m_pSplineCameraController->GetVRCameraState();
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

    void VRCameraSplineExample::OnScreenVisiblityChanged(ScreenFadeEffect::SdkModel::IScreenFadeEffectController::VisibilityState& visbilityState)
    {
        if (visbilityState == ScreenFadeEffect::SdkModel::IScreenFadeEffectController::VisibilityState::FullyFaded && m_splineChanged)
        {
            m_screenFader.SetShouldFadeToBlack(false);
            m_splineChanged = false;

            m_pSplineCameraController->PlayNextSpline();
        }
        else if (visbilityState == ScreenFadeEffect::SdkModel::IScreenFadeEffectController::VisibilityState::FullyVisible)
        {
            ShowWelcomeNote();
        }
    }
}
