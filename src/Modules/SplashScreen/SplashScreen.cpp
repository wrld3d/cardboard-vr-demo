// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "SplashScreen.h"
#include "LatLongAltitude.h"
#include "ApplicationConfiguration.h"
#include "CameraHelpers.h"
#include "../UI/IUICameraProvider.h"
#include "../UI/UIProgressButton.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            SplashScreen::SplashScreen(Eegeo::Rendering::SceneModels::SceneModelLoader& sceneModelLoader,
                                       Eegeo::Rendering::SceneModels::SceneModelFactory::TMaterialRepo& sceneModelMaterials
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
                
                Eegeo::v2 size(16.f, 16.f);
                
                m_pStateButtonLocation = Eegeo_NEW(Eegeo::UI::SplashScreen::StateButton)(uiRenderableFilter, quadFactory, assetPath, 23, 24, 6, config, m_stateButtonClicked, size);
                m_pStateButtonBuilding = Eegeo_NEW(Eegeo::UI::SplashScreen::StateButton)(uiRenderableFilter, quadFactory, assetPath, 14, 13, 6, config, m_stateButtonClicked, size);
                m_pStateButtonPOI = Eegeo_NEW(Eegeo::UI::SplashScreen::StateButton)(uiRenderableFilter, quadFactory, assetPath, 0, 22, 6, config, m_stateButtonClicked, size);
                
                int row = 16%6;
                int col = 16/6;
                float fraction = 1.f/6;
                
                Eegeo::v2 outMinUV (fraction*row, fraction*col);
                Eegeo::v2 outMaxUV (fraction*(row+1), fraction*(col+1));
                
                m_pPlayButton = Eegeo_NEW(Eegeo::UI::UIProgressButton)(uiRenderableFilter, quadFactory, assetPath, config, m_playButtonClicked, size
                                                                       , Eegeo::Space::LatLongAltitude::FromDegrees(56.4577389, -2.9707447, 250).ToECEF()
                                                                       , Eegeo::v3::One()
                                                                       , Eegeo::v4::One()
                                                                       , outMinUV
                                                                       , outMaxUV
                                                                       );
                
                m_uiInteractionController.RegisterInteractableItem(m_pStateButtonLocation);
                m_uiInteractionController.RegisterInteractableItem(m_pStateButtonBuilding);
                m_uiInteractionController.RegisterInteractableItem(m_pStateButtonPOI);
                m_uiInteractionController.RegisterInteractableItem(m_pPlayButton);
                
                
                
                m_pSplashScreenModelFactory = Eegeo_NEW(SplashScreenModelFactory)(sceneModelLoader, sceneModelMaterials, m_sceneModelRenderableFilter);

                TMaterialNames materialNames;

                materialNames.push_back("vr_splash_screen/WelcomeScreen.POD/materials/alpha_mesh_gradient");
                materialNames.push_back("vr_splash_screen/WelcomeScreen.POD/materials/alpha_eeGeo_logo");
                materialNames.push_back("vr_splash_screen/WelcomeScreen.POD/materials/alpha_alt_text");

                m_pSplashScreenModel = m_pSplashScreenModelFactory->CreateSplashScreenModel("vr_splash_screen/WelcomeScreen.POD", materialNames, Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 250).ToECEF(), 120);
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

                Eegeo_DELETE m_pSplashScreenModel;
            }

            void SplashScreen::SetEcefPosition(const Eegeo::dv3 &ecefPosition)
            {
                m_pSplashScreenModel->SetEcefPosition(ecefPosition);
            }

            void SplashScreen::Update(float dt)
            {
                m_pStateButtonLocation->Update(dt);
                m_pStateButtonBuilding->Update(dt);
                m_pStateButtonPOI->Update(dt);
                m_pPlayButton->Update(dt);
                m_pSplashScreenModel->Update(dt);
            }
            
            void SplashScreen::StateButtonClicked()
            {
            }
            
            void SplashScreen::PlayButtonClicked()
            {
                m_playButtonCallback();
            }
            
            void SplashScreen::Hide()
            {
                m_pStateButtonLocation->Hide();
                m_pStateButtonBuilding->Hide();
                m_pStateButtonPOI->Hide();
                m_pPlayButton->SetItemShouldRender(false);
                m_pSplashScreenModel->SetShouldDisplay(false);
            }
            
            void SplashScreen::Show()
            {
                
                Eegeo::Space::EcefTangentBasis basis;
                Eegeo::dv3 p = Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, 241.5f).ToECEF();
                Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(p, -60.53f, basis);
                
                Eegeo::dv3 top(p.ToSingle().Norm());
                Eegeo::dv3 forward(basis.GetForward().Norm());
                Eegeo::dv3 right(Eegeo::dv3::Cross(top, forward));

                m_pStateButtonBuilding->SetEcefPosition((forward*310.f) + (right*4.f) + p);
                m_pStateButtonPOI->SetEcefPosition((forward*310.f) + (right*-28.f) + p);
                m_pStateButtonLocation->SetEcefPosition((forward*310.f) + (right*37.f) + p);
                m_pPlayButton->SetEcefPosition((forward*270.f) + (right*5.f) + (top*-35.f) + p);
                
                m_pStateButtonLocation->Show();
                m_pStateButtonBuilding->Show();
                m_pStateButtonPOI->Show();
                m_pPlayButton->SetItemShouldRender(true);
                m_pSplashScreenModel->SetShouldDisplay(true);
            }
            
        }
    }
}
