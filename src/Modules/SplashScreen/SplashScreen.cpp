// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SplashScreen.h"
#include "LatLongAltitude.h"
#include "ApplicationConfiguration.h"
#include "../UI/UIProgressButton.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            SplashScreen::SplashScreen(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader
                                       , Eegeo::Rendering::Filters::SceneModelRenderableFilter& sceneModelRenderableFilter
                                       , Eegeo::UI::IUICameraProvider& uICameraProvider
                                       , UIInteractionController& uiInteractionController
                                       , IUIRenderableFilter& uiRenderableFilter
                                       , Eegeo::UI::IUIQuadFactory& quadFactory
                                       , const std::string& assetPath
                                       , const UIProgressBarConfig& progressBarConfig
                                       , Eegeo::Helpers::ICallback0& playButtonCallback)
            : m_sceneModelRenderableFilter(sceneModelRenderableFilter)
            , m_uiInteractionController(uiInteractionController)
            , m_playButtonCallback(playButtonCallback)
            , m_stateButtonClicked(this, &SplashScreen::StateButtonClicked)
            , m_playButtonClicked(this, &SplashScreen::PlayButtonClicked)
            , m_pSplashScreenModel(NULL)
            , m_pSplashScreenModelFactory(NULL)
            {
                
                UIProgressBarConfig config = progressBarConfig;
                config.frameRate = progressBarConfig.frameRate*2.8f;
                
                m_pStateButtonLocation = Eegeo_NEW(Eegeo::UI::SplashScreen::StateButton)(uiRenderableFilter, quadFactory, assetPath, 23, 24, 5, config, m_stateButtonClicked, Eegeo::v2(50.f, 50.f));
                m_pStateButtonBuilding = Eegeo_NEW(Eegeo::UI::SplashScreen::StateButton)(uiRenderableFilter, quadFactory, assetPath, 14, 13, 5, config, m_stateButtonClicked, Eegeo::v2(50.f, 50.f));
                m_pStateButtonPOI = Eegeo_NEW(Eegeo::UI::SplashScreen::StateButton)(uiRenderableFilter, quadFactory, assetPath, 0, 22, 5, config, m_stateButtonClicked, Eegeo::v2(50.f, 50.f));
                m_pStateButtonLocation->SetEcefPosition(Eegeo::Space::LatLongAltitude::FromDegrees(56.4577389, -2.9707447, 200).ToECEF());
                m_pStateButtonBuilding->SetEcefPosition(Eegeo::Space::LatLongAltitude::FromDegrees(56.4577389, -2.9707447, 250).ToECEF());
                m_pStateButtonPOI->SetEcefPosition(Eegeo::Space::LatLongAltitude::FromDegrees(56.4577389, -2.9707447, 150).ToECEF());
                
                int row = 1%5;
                int col = 1/5;
                float fraction = 1.f/5;
                
                Eegeo::v2 outMinUV (fraction*row, fraction*col);
                Eegeo::v2 outMaxUV (fraction*(row+1), fraction*(col+1));
                
                m_pPlayButton = Eegeo_NEW(Eegeo::UI::UIProgressButton)(uiRenderableFilter, quadFactory, assetPath, config, m_playButtonClicked, Eegeo::v2(50.f, 50.f)
                                                                       , Eegeo::Space::LatLongAltitude::FromDegrees(56.4577389, -2.9707447, 100).ToECEF()
                                                                       , Eegeo::v3::One()
                                                                       , Eegeo::v4::One()
                                                                       , outMinUV
                                                                       , outMaxUV
                                                                       );
                
                m_uiInteractionController.RegisterInteractableItem(m_pStateButtonLocation);
                m_uiInteractionController.RegisterInteractableItem(m_pStateButtonBuilding);
                m_uiInteractionController.RegisterInteractableItem(m_pStateButtonPOI);
                m_uiInteractionController.RegisterInteractableItem(m_pPlayButton);
                
                
                
                m_pSplashScreenModelFactory = Eegeo_NEW(SplashScreenModelFactory)(sceneModelLoader);

                m_pSplashScreenModel = m_pSplashScreenModelFactory->CreateSplashScreenModel("vr_splash_screen/WelcomeScreen.POD", Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 100).ToECEF(), 110);
                m_pSplashScreenModel->SetScale(100);

                m_sceneModelRenderableFilter.AddSceneModel(m_pSplashScreenModel->GetSceneModel());
            }
            
            SplashScreen::~SplashScreen()
            {
                m_uiInteractionController.UnRegisterInteractableItem(m_pStateButtonLocation);
                m_uiInteractionController.UnRegisterInteractableItem(m_pStateButtonBuilding);
                m_uiInteractionController.UnRegisterInteractableItem(m_pStateButtonPOI);
                m_uiInteractionController.UnRegisterInteractableItem(m_pPlayButton);
                
                Eegeo_DELETE(m_pStateButtonLocation);
                Eegeo_DELETE(m_pStateButtonBuilding);
                Eegeo_DELETE(m_pStateButtonPOI);
                Eegeo_DELETE(m_pPlayButton);

                Eegeo_DELETE m_pSplashScreenModelFactory;

                m_sceneModelRenderableFilter.RemoveSceneModel(m_pSplashScreenModel->GetSceneModel());
                Eegeo_DELETE m_pSplashScreenModel;
            }
            
            void SplashScreen::Update(float dt)
            {
                m_pStateButtonLocation->Update(dt);
                m_pStateButtonBuilding->Update(dt);
                m_pStateButtonPOI->Update(dt);
                m_pPlayButton->Update(dt);
            }
            
            void SplashScreen::StateButtonClicked()
            {
            }
            
            void SplashScreen::PlayButtonClicked()
            {
                Hide();
                m_playButtonCallback();
            }
            
            void SplashScreen::Hide()
            {
                m_pStateButtonLocation->Hide();
                m_pStateButtonBuilding->Hide();
                m_pStateButtonPOI->Hide();
                m_pPlayButton->SetItemShouldRender(false);
            }
            
            void SplashScreen::Show()
            {
                m_pStateButtonLocation->Show();
                m_pStateButtonBuilding->Show();
                m_pStateButtonPOI->Show();
                m_pPlayButton->SetItemShouldRender(true);
            }
            
        }
    }
}
