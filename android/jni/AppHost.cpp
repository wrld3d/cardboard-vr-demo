// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "AppHost.h"
#include "LatLongAltitude.h"
#include "EegeoWorld.h"
#include "AppInterface.h"
#include "JpegLoader.h"
#include "EffectHandler.h"
#include "SearchServiceCredentials.h"
#include "AndroidThreadHelper.h"
#include "GlobeCameraController.h"
#include "RenderCamera.h"
#include "CameraHelpers.h"
#include "PlatformConfig.h"
#include "AndroidPlatformConfigBuilder.h"
#include "AndroidLocationService.h"
#include "RouteMatchingExampleFactory.h"
#include "RouteSimulationExampleFactory.h"
#include "JavaHudCrossThreadCommunicationExampleFactory.h"
#include "PinsWithAttachedJavaUIExampleFactory.h"
#include "PositionJavaPinButtonExampleFactory.h"
#include "ExampleCameraJumpController.h"
#include "ShowJavaPlaceJumpUIExampleFactory.h"
#include "AndroidPlatformAbstractionModule.h"
#include "ScreenProperties.h"
#include "BuildingFootprintsModule.h"
#include "CollisionVisualizationModule.h"
#include "AndroidVRHeadTracker.h"
#include "ApplicationConfig/SdkModel/AndroidApplicationConfigurationVersionProvider.h"
#include "ApplicationConfigurationModule.h"
#include "IApplicationConfigurationService.h"
#include "AndroidFileIO.h"
#include "ApiKey.h"

namespace
{
	Examples::ApplicationConfig::ApplicationConfiguration LoadConfiguration(AndroidNativeState& state)
	 {
	    std::set<std::string> customApplicationAssetDirectories;
	    customApplicationAssetDirectories.insert("ApplicationConfigs");

	    Eegeo::Android::AndroidFileIO tempFileIO(&state, customApplicationAssetDirectories);

	    Examples::ApplicationConfig::SdkModel::AndroidApplicationConfigurationVersionProvider versionProvider(state);
	    Examples::ApplicationConfig::SdkModel::ApplicationConfigurationModule applicationConfigurationModule(tempFileIO,
	    		versionProvider.GetProductVersionString(),
	    		versionProvider.GetBuildNumberString());
	   return applicationConfigurationModule.GetApplicationConfigurationService().LoadConfiguration(ApplicationConfigurationPath);
	}

    Eegeo::Modules::BuildingFootprintsModule* CreateBuildingFootprintsModule(Eegeo::EegeoWorld& world, const Eegeo::Modules::CollisionVisualizationModule& collisionVisualizationModule)
    {
        const Eegeo::BuildingFootprints::BuildingFootprintSelectionControllerConfig& buildingFootprintSelectionControllerConfig = Eegeo::Modules::BuildingFootprintsModule::MakeDefaultConfig();

        const Eegeo::Modules::IPlatformAbstractionModule& platformAbstractionModule = world.GetPlatformAbstractionModule();
        const Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
        const Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();
        const Eegeo::Modules::Map::Layers::BuildingStreamingModule& buildingStreamingModule = mapModule.GetBuildingStreamingModule();
        const Eegeo::Modules::Map::CoverageTreeModule& coverageTreeModule = mapModule.GetCoverageTreeModule();

        Eegeo::Modules::BuildingFootprintsModule* pBuildingFootprintsModule =
        Eegeo::Modules::BuildingFootprintsModule::Create(platformAbstractionModule,
                                                         renderingModule,
                                                         collisionVisualizationModule,
                                                         buildingStreamingModule,
                                                         coverageTreeModule,
                                                         buildingFootprintSelectionControllerConfig);
        return pBuildingFootprintsModule;
    }

    Eegeo::Modules::CollisionVisualizationModule* CreateCollisionVisualizationModule(Eegeo::EegeoWorld& world)
    {
        const Eegeo::CollisionVisualization::MaterialSelectionControllerConfig& materialSelectionControllerConfig = Eegeo::Modules::CollisionVisualizationModule::MakeDefaultConfig();


        const Eegeo::Modules::Core::RenderingModule& renderingModule = world.GetRenderingModule();
        const Eegeo::Modules::Map::MapModule& mapModule = world.GetMapModule();

        Eegeo::Modules::CollisionVisualizationModule* pCollisionVisualizationModule = Eegeo::Modules::CollisionVisualizationModule::Create(renderingModule, mapModule, materialSelectionControllerConfig);
        return pCollisionVisualizationModule;
    }
}

using namespace Eegeo::Android;
using namespace Eegeo::Android::Input;

AppHost::AppHost(
    AndroidNativeState& nativeState,
    float displayWidth,
    float displayHeight,
    EGLDisplay display,
    EGLSurface shareSurface,
    EGLContext resourceBuildShareContext
)
	: m_isPaused(false)
	,m_pJpegLoader(NULL)
	,m_pAndroidLocationService(NULL)
	,m_pWorld(NULL)
	,m_nativeState(nativeState)
	,m_androidInputBoxFactory(&nativeState)
	,m_androidKeyboardInputFactory(&nativeState, m_inputHandler)
	,m_androidAlertBoxFactory(&nativeState)
	,m_androidNativeUIFactories(m_androidAlertBoxFactory, m_androidInputBoxFactory, m_androidKeyboardInputFactory)
	,m_pApp(NULL)
	,m_pAndroidExampleControllerView(NULL)
	,m_pInputProcessor(NULL)
	,m_pAndroidPlatformAbstractionModule(NULL)
	,m_pCollisionVisualizationModule(NULL)
	,m_pBuildingFootprintsModule(NULL)
{
	Eegeo::TtyHandler::TtyEnabled = false;
	Eegeo::AssertHandler::BreakOnAssert = true;

	Eegeo_ASSERT(resourceBuildShareContext != EGL_NO_CONTEXT);

	m_pAndroidLocationService = new AndroidLocationService(&nativeState);

	Eegeo::Rendering::ScreenProperties screenProperties(Eegeo::Rendering::ScreenProperties::Make(displayWidth, displayHeight, 1.f, nativeState.deviceDpi));

	std::set<std::string> customApplicationAssetDirectories;
	customApplicationAssetDirectories.insert("heatmap_example");
	customApplicationAssetDirectories.insert("load_model_example");
	customApplicationAssetDirectories.insert("mesh_example");
	customApplicationAssetDirectories.insert("pin_over_model_example");
	customApplicationAssetDirectories.insert("pins_example");
	customApplicationAssetDirectories.insert("pins_with_attached_java_ui_example");
	customApplicationAssetDirectories.insert("pod_animation_example");
	customApplicationAssetDirectories.insert("route_simulation_example");
	customApplicationAssetDirectories.insert("route_simulation_animation_example");
	customApplicationAssetDirectories.insert("ApplicationConfigs");
	customApplicationAssetDirectories.insert("vr_splash_screen");

	Examples::ApplicationConfig::ApplicationConfiguration appConfig(LoadConfiguration(nativeState));

	m_pJpegLoader = new Eegeo::Helpers::Jpeg::JpegLoader();

	m_pAndroidPlatformAbstractionModule = new Eegeo::Android::AndroidPlatformAbstractionModule(nativeState,
																							   *m_pJpegLoader,
																							   display,
																							   resourceBuildShareContext,
																							   shareSurface,
																							   appConfig.EegeoApiKey(),
																							   customApplicationAssetDirectories);

	Eegeo::EffectHandler::Initialise();

	const Eegeo::EnvironmentCharacterSet::Type environmentCharacterSet = Eegeo::EnvironmentCharacterSet::JapanPlaceNames;
	std::string deviceModel = std::string(nativeState.deviceModel, strlen(nativeState.deviceModel));
	Eegeo::Config::PlatformConfig config = Eegeo::Android::AndroidPlatformConfigBuilder(deviceModel).Build();

	config.GraphicsConfig.AlwaysUseHighFidelityWaterShader = true;
    config.OptionsConfig.GenerateCollisionForAllResources = true;
	config.CityThemesConfig.EmbeddedThemeManifestFile = "embedded_manifest.bin";
	config.CityThemesConfig.EmbeddedThemeTexturePath = "Textures";
	config.CityThemesConfig.EmbeddedThemeNameContains = "Summer";
	config.CityThemesConfig.EmbeddedThemeStateName = "DayDefault";

	config.CoverageTreeConfig.ManifestUrl = appConfig.CoverageTreeManifestURL();
	config.CityThemesConfig.StreamedManifestUrl = appConfig.ThemeManifestURL();

	// Remove the selected floor scaling.
	config.MapLayersConfig.Interiors.FloorAnimatorConfiguration.FloorScaleWhenSelected = 1.0f;

	// Reduce the gap between floors while keeping the floors above the selected one high enough to 'fall' into place.
	config.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedFloorSpacingFactor = 0.01f;
	config.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedSelectedFloorGapFactor = 100.0f;

	// Remove the brightness changing.
	config.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedSelectedFloorBrightness = 1.0f;
	config.MapLayersConfig.Interiors.FloorAnimatorConfiguration.ExpandedUnselectedFloorBrightness = 1.0f;

	m_pWorld = new Eegeo::EegeoWorld(
		appConfig.EegeoApiKey(),
	    *m_pAndroidPlatformAbstractionModule,
	    *m_pJpegLoader,
	    screenProperties,
	    *m_pAndroidLocationService,
	    m_androidNativeUIFactories,
	    environmentCharacterSet,
	    config);

    m_pCollisionVisualizationModule = CreateCollisionVisualizationModule(*m_pWorld);
    m_pBuildingFootprintsModule = CreateBuildingFootprintsModule(*m_pWorld, *m_pCollisionVisualizationModule);

	m_pInputProcessor = new Eegeo::Android::Input::AndroidInputProcessor(&m_inputHandler, screenProperties.GetScreenWidth(), screenProperties.GetScreenHeight());

	ConfigureExamples(screenProperties, config.PerformanceConfig.DeviceSpecification, appConfig);

	m_pAppInputDelegate = new AppInputDelegate(*m_pApp);
	m_inputHandler.AddDelegateInputHandler(m_pAppInputDelegate);
    
    
}

AppHost::~AppHost()
{
	m_inputHandler.RemoveDelegateInputHandler(m_pAppInputDelegate);

	delete m_pAppInputDelegate;
	m_pAppInputDelegate = NULL;

	delete m_pApp;
	m_pApp = NULL;

	DestroyExamples();

    delete m_pBuildingFootprintsModule;
    m_pBuildingFootprintsModule = NULL;

    delete m_pCollisionVisualizationModule;
    m_pCollisionVisualizationModule = NULL;

	delete m_pWorld;
	m_pWorld = NULL;

	Eegeo::EffectHandler::Reset();
	Eegeo::EffectHandler::Shutdown();

	delete m_pAndroidLocationService;
	m_pAndroidLocationService = NULL;

	delete m_pJpegLoader;
	m_pJpegLoader = NULL;

	delete m_pAndroidPlatformAbstractionModule;
	m_pAndroidPlatformAbstractionModule = NULL;
}

void AppHost::OnResume()
{
	m_pApp->OnResume();
}

void AppHost::OnPause()
{
	m_pApp->OnPause();
	m_pAndroidLocationService->StopListening();
}

void AppHost::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
{
    m_pApp->NotifyScreenPropertiesChanged(screenProperties);
}

void AppHost::SetSharedSurface(EGLSurface sharedSurface)
{
	m_pAndroidPlatformAbstractionModule->UpdateSurface(sharedSurface);
}

void AppHost::SetViewportOffset(float x, float y)
{
	m_inputHandler.SetViewportOffset(x, y);
}

void AppHost::HandleTouchInputEvent(const Eegeo::Android::Input::TouchInputEvent& event)
{
	m_pInputProcessor->HandleInput(event);
}

void AppHost::UpdateCardboardProfile(const float cardboardProfile[])
{
    m_pApp->UpdateCardboardProfile(cardboardProfile);
}

void AppHost::MagnetTriggered()
{
    m_pApp->MagnetTriggered();
}

void AppHost::ToggleNightMode(const bool turnOn)
{
    m_pApp->ToggleNightMode(turnOn);
}

void AppHost::Update(float dt, const float headTansform[])
{
	m_pInputProcessor->Update(dt);
	m_pApp->Update(dt, headTansform);
}

void AppHost::Draw(float dt)
{
	m_pApp->Draw(dt);
}

void AppHost::ConfigureExamples(const Eegeo::Rendering::ScreenProperties& screenProperties, Eegeo::Config::DeviceSpec deviceSpecs, Examples::ApplicationConfig::ApplicationConfiguration appConfig)
{
	m_pAndroidExampleControllerView = new Examples::AndroidExampleControllerView(m_nativeState);
    	m_pHeadTracker = new Examples::AndroidVRHeadTracker(m_nativeState);
    
	m_pApp = new ExampleApp(m_pWorld, deviceSpecs, *m_pAndroidExampleControllerView, *m_pHeadTracker, screenProperties, *m_pCollisionVisualizationModule, *m_pBuildingFootprintsModule, appConfig);

	m_pAndroidExampleControllerView->PopulateExampleList(m_pApp->GetExampleController().GetExampleNames());

	m_pApp->GetExampleController().ActivatePrevious();
}

void AppHost::DestroyExamples()
{
    delete m_pHeadTracker;
	delete m_pAndroidExampleControllerView;
}




