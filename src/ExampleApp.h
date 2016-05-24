// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__ExampleApp__
#define __ExampleApp__ExampleApp__

#include "GlobeCamera.h"
#include "EegeoWorld.h"
#include "ExampleController.h"
#include "ScreenProperties.h"
#include "DefaultCameraControllerFactory.h"
#include "Modules.h"
#include "IIdentity.h"
#include "Modules/VRDistortionModule/VRDistortionModule.h"
#include "Modules/SkyboxModule/SkyboxModule.h"
#include "Modules/InteriorsExplorerModule/InteriorsExplorerModule.h"
#include "Modules/UI/UIImageButton.h"
#include "Modules/UI/UIInteractionModule.h"
#include "Modules/UI/IUICameraProvider.h"
#include "Logger.h"
#include "Modules/GazeUI/GazeUI.h"
#include "Modules/JumpPoints/JumpPoint.h"
#include "Modules/JumpPoints/JumpPointsModule.h"
#include "Modules/JumpPoints/JumpPointRepository.h"

class ExampleApp : private Eegeo::NonCopyable, Eegeo::UI::IUICameraProvider
{
private:
    
    Eegeo::UI::JumpPoints::JumpPoint *m_JumpPoint1, *m_JumpPoint2, *m_JumpPoint3;
    Eegeo::UI::JumpPoints::JumpPointsModule* m_JumpPointsModule;
    Examples::DefaultCameraControllerFactory* m_pCameraControllerFactory;
	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController* m_pCameraTouchController;
	Eegeo::EegeoWorld* m_pWorld;
    Eegeo::Rendering::LoadingScreen* m_pLoadingScreen;
	Examples::ExampleController* m_pExampleController;
    Examples::ScreenPropertiesProvider m_screenPropertiesProvider;
    Eegeo::Streaming::CameraFrustumStreamingVolume* m_pStreamingVolume;
    
    Eegeo::VR::Distortion::VRDistortionModule* m_VRDistortion;
    Eegeo::Skybox::SkyboxModule *m_VRSkybox;
    Eegeo::UI::UIImageButton *m_UIButton;
    Eegeo::UI::UIInteractionModule *m_UIInteractionModule;
    Eegeo::GazeUI::GazeUIModule* m_GazeUIModule;
    
    Eegeo::Helpers::IdentityProvider m_identityProvider;
    InteriorsExplorer::InteriorsExplorerModule* m_interiorExplorerModule;
    
    bool m_night;
    float m_foggingFar;
    float m_nightTParam;
    
    Eegeo::v3 m_currentClearColor;
    Eegeo::v3 m_startClearColor;
    Eegeo::v3 m_destClearColor;

	Eegeo::EegeoWorld& World()
	{
		return * m_pWorld;
	}
    
    void UpdateLoadingScreen(float dt);
    
    Eegeo::UI::TUIImageButtonClickedCallback<ExampleApp> m_ClickCallback;

public:
	ExampleApp(Eegeo::EegeoWorld* pWorld,
               Eegeo::Config::DeviceSpec deviceSpecs,
               Examples::IExampleControllerView& view,
               Eegeo::GazeUI::IGazeUIView& gazeUIView,
               const Eegeo::Rendering::ScreenProperties& screenProperties,
               Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule,
               Eegeo::Modules::BuildingFootprintsModule& buildingFootprintsModule);

	~ExampleApp();

	void OnPause();

	void OnResume();

    
	void Update (float dt, float headTansform[]);
    
    void Draw (float dt, float headTansform[]);
    void DrawLeftEye (float dt, float headTansform[], Eegeo::EegeoWorld& eegeoWorld);
    void DrawRightEye (float dt, float headTansform[], Eegeo::EegeoWorld& eegeoWorld);
    
    void DrawLoadingScreen ();
    
    void UpdateNightTParam(float dt);
    void ToggleNight();
    void UpdateFogging();
    
    
    void UpdateCardboardProfile(float cardboardProfile[]);
    void MagnetTriggered();
    
    void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
    
    Examples::ExampleController& GetExampleController() const { return *m_pExampleController; }
    
    Examples::DefaultCameraControllerFactory& GetDefaultCameraControllerFactory() const { return *m_pCameraControllerFactory; }

	Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController()
	{
		return *m_pCameraTouchController;
	}
    
    const Examples::IScreenPropertiesProvider& GetScreenPropertiesProvider() const { return m_screenPropertiesProvider; }

	void Event_TouchRotate 			(const AppInterface::RotateData& data);
	void Event_TouchRotate_Start	(const AppInterface::RotateData& data);
	void Event_TouchRotate_End 		(const AppInterface::RotateData& data);

	void Event_TouchPinch 			(const AppInterface::PinchData& data);
	void Event_TouchPinch_Start 	(const AppInterface::PinchData& data);
	void Event_TouchPinch_End 		(const AppInterface::PinchData& data);

	void Event_TouchPan				(const AppInterface::PanData& data);
	void Event_TouchPan_Start		(const AppInterface::PanData& data);
	void Event_TouchPan_End 		(const AppInterface::PanData& data);

	void Event_TouchTap 			(const AppInterface::TapData& data);
	void Event_TouchDoubleTap		(const AppInterface::TapData& data);

	void Event_TouchDown 			(const AppInterface::TouchData& data);
	void Event_TouchMove 			(const AppInterface::TouchData& data);
	void Event_TouchUp 				(const AppInterface::TouchData& data);
    
    Eegeo::Camera::RenderCamera* GetRenderCameraForUI();
};

#endif /* defined(__ExampleApp__ExampleApp__) */
