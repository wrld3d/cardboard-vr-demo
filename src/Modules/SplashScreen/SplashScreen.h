// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "UISprite.h"
#include "UIQuad/UIQuad.h"
#include "IUICameraProvider.h"
#include "UIInteraction/IUIInteractableItem.h"
#include "UIAnimatedSprite.h"
#include "UIProgressBarConfig.h"
#include "ICallback.h"
#include "StateButton.h"
#include "UIInteractionController.h"
#include "../UI/UIProgressButton.h"

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            class SplashScreen
            {
            private:
                
                Eegeo::UI::UIInteractionController& m_uiInteractionController;
                Eegeo::UI::SplashScreen::StateButton* m_pStateButtonLocation;
                Eegeo::UI::SplashScreen::StateButton* m_pStateButtonBuilding;
                Eegeo::UI::SplashScreen::StateButton* m_pStateButtonPOI;
                
                Eegeo::UI::UIProgressButton* m_pPlayButton;
                
                void StateButtonClicked();
                void PlayButtonClicked();
                
            public:
                SplashScreen(Eegeo::UI::IUICameraProvider& uICameraProvider
                             , UIInteractionController& uiInteractionController
                             , IUIRenderableFilter& uiRenderableFilter
                             , Eegeo::UI::IUIQuadFactory& quadFactory
                             , const std::string& assetPath
                             , const UIProgressBarConfig& progressBarConfig
                             , Eegeo::Helpers::ICallback0& playButtonCallback);
                
                
                virtual ~SplashScreen();
                
                void Update(float dt);
                
                void Show();
                void Hide();
                
                Eegeo::Helpers::TCallback0<SplashScreen> m_stateButtonClicked;
                Eegeo::Helpers::TCallback0<SplashScreen> m_playButtonClicked;
                Eegeo::Helpers::ICallback0& m_playButtonCallback;
            };
            
        }
    }
}
