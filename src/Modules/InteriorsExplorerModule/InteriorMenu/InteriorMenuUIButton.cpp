// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "InteriorMenuUIButton.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

#define PROGRESS_SCALE_MULTIPLIER 1.5f

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        InteriorMenuUIButton::InteriorMenuUIButton(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                     , Eegeo::UI::IUIQuadFactory& quadFactory
                                     , const std::string& assetPath
                                     , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                     , const Eegeo::v2& size
                                     , const Eegeo::dv3& ecefPosition
                                     , const Eegeo::v3& scale
                                     , const Eegeo::v4& color
                                     , const Eegeo::v2& uvMin
                                     , const Eegeo::v2& uvMax)
        {
            m_radius = (size.x > size.y ? size.x : size.y)/2.0f;
            Init(quadFactory, uiRenderableFilter, assetPath, progressBarConfig, size, ecefPosition, scale, color, uvMin, uvMax);
        }
        
        InteriorMenuUIButton::~InteriorMenuUIButton()
        {
            Eegeo_DELETE m_pGazeProgress;
            Eegeo_DELETE m_pSprite;
        }
        
        void InteriorMenuUIButton::Init(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter, const std::string& assetPath, const Eegeo::UI::UIProgressBarConfig& progressBarConfig, const Eegeo::v2& size, const Eegeo::dv3& ecefPosition, const Eegeo::v3& scale, const Eegeo::v4& color, const Eegeo::v2& uvMin, const Eegeo::v2& uvMax)
        {
            m_pSprite = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter
                                            , quadFactory.CreateUIQuad(assetPath, size, uvMin, uvMax)
                                            , size
                                            , ecefPosition
                                            , scale
                                            , color
                                            );
            
            m_pGazeProgress = Eegeo_NEW(Eegeo::UI::UIAnimatedSprite)(uiRenderableFilter,
                                                                     quadFactory,
                                                                     progressBarConfig.textureFilename,
                                                                     progressBarConfig.frameRate,
                                                                     progressBarConfig.spriteGridSize,
                                                                     progressBarConfig.spriteId,
                                                                     size,
                                                                     ecefPosition,
                                                                     progressBarConfig.scale,
                                                                     progressBarConfig.color,
                                                                     progressBarConfig.renderLayer);
        }
        
        void InteriorMenuUIButton::Update(float dt)
        {
            m_pGazeProgress->Update(dt);
            m_pSprite->Update(dt);
        }
        
        
        void InteriorMenuUIButton::OnFocusGained()
        {
            m_pGazeProgress->Reset();
            m_pGazeProgress->SetScale(m_pSprite->GetScale() * PROGRESS_SCALE_MULTIPLIER);
        }
        
        void InteriorMenuUIButton::OnFocusLost()
        {
            m_pGazeProgress->SetScale(Eegeo::v3::Zero());
        }
        
        void InteriorMenuUIButton::SetEcefPosition(const Eegeo::dv3& position)
        {
            m_pSprite->SetEcefPosition(position);
            m_pGazeProgress->SetEcefPosition(position);
        }
        
        Eegeo::dv3 InteriorMenuUIButton::GetEcefPosition()
        {
            return m_pSprite->GetEcefPosition();
        }
        
        Eegeo::v2 InteriorMenuUIButton::GetSize()
        {
            return m_pSprite->GetSize();
        }
        
        void InteriorMenuUIButton::SetColor(const Eegeo::v4& color)
        {
            m_pSprite->SetColor(color);
            m_pGazeProgress->SetColor(color);
        }
        
        Eegeo::v4 InteriorMenuUIButton::GetColor()
        {
            return m_pSprite->GetColor();
        }
        
        void InteriorMenuUIButton::SetScale(const Eegeo::v3& scale)
        {
            m_pSprite->SetScale(scale);
            m_pGazeProgress->SetScale(scale * PROGRESS_SCALE_MULTIPLIER);
        }
        
        Eegeo::v3 InteriorMenuUIButton::GetScale()
        {
            return m_pSprite->GetScale();
        }
        
    }
}
