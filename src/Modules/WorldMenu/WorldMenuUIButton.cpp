// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "WorldMenuUIButton.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

#define PROGRESS_SCALE_MULTIPLIER 1.1f

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            WorldMenuUIButton::WorldMenuUIButton(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                                       , Eegeo::UI::IUIQuadFactory& quadFactory
                                                       , const std::string& assetPath
                                                       , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                                       , const Eegeo::v2& size
                                                       , const Eegeo::dv3& ecefPosition
                                                       , const Eegeo::v3& scale
                                                       , const Eegeo::v4& color
                                                       , const Eegeo::v2& uvMin
                                                       , const Eegeo::v2& uvMax)
            : m_radius((size.x > size.y ? size.x : size.y)/2.0f)
            , m_isFocused(false)
            , m_isItemSelected(false)
            , m_scale(scale)
            {
                Init(quadFactory, uiRenderableFilter, assetPath, progressBarConfig, size, ecefPosition, scale, color, uvMin, uvMax);
            }
            
            WorldMenuUIButton::~WorldMenuUIButton()
            {
                Eegeo_DELETE m_pGazeProgress;
                Eegeo_DELETE m_pSprite;
            }
            
            void WorldMenuUIButton::Init(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter, const std::string& assetPath, const Eegeo::UI::UIProgressBarConfig& progressBarConfig, const Eegeo::v2& size, const Eegeo::dv3& ecefPosition, const Eegeo::v3& scale, const Eegeo::v4& color, const Eegeo::v2& uvMin, const Eegeo::v2& uvMax)
            {
                m_isFocused = false;
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
            
            void WorldMenuUIButton::Update(float dt)
            {
                m_pGazeProgress->Update(dt);
                m_pSprite->Update(dt);
            }
            
            
            void WorldMenuUIButton::OnFocusGained()
            {
                if(m_isItemSelected)
                {
                    m_pGazeProgress->SetScale(Eegeo::v3::Zero());
                }
                else
                {
                    m_pGazeProgress->Reset();
                    m_pGazeProgress->SetScale(m_pSprite->GetScale() * PROGRESS_SCALE_MULTIPLIER);
                    m_isFocused = true;
                }
            }
            
            void WorldMenuUIButton::OnFocusLost()
            {
                m_isFocused = false;
                m_pGazeProgress->SetScale(Eegeo::v3::Zero());
            }
            
            void WorldMenuUIButton::SetEcefPosition(const Eegeo::dv3& position)
            {
                m_pSprite->SetEcefPosition(position);
                m_pGazeProgress->SetEcefPosition(position);
            }
            
            Eegeo::dv3 WorldMenuUIButton::GetEcefPosition()
            {
                return m_pSprite->GetEcefPosition();
            }
            
            Eegeo::v2 WorldMenuUIButton::GetSize()
            {
                return m_pSprite->GetSize();
            }
            
            void WorldMenuUIButton::SetColor(const Eegeo::v4& color)
            {
                m_pSprite->SetColor(color);
                m_pGazeProgress->SetColor(color);
            }
            
            Eegeo::v4 WorldMenuUIButton::GetColor()
            {
                return m_pSprite->GetColor();
            }
            
            void WorldMenuUIButton::SetScale(const Eegeo::v3& scale)
            {
                m_scale = scale;
                m_pSprite->SetScale(m_scale);
                m_pGazeProgress->SetScale(m_scale * PROGRESS_SCALE_MULTIPLIER);
            }
            
            Eegeo::v3 WorldMenuUIButton::GetScale()
            {
                return m_pSprite->GetScale();
            }
            
            void WorldMenuUIButton::SetItemSelected()
            {
                m_isItemSelected = true;
                
                float scale = 1.23f;
                m_scale = Eegeo::v3(scale, scale, scale);
                m_pSprite->SetScale(m_scale);
                m_pGazeProgress->SetScale(Eegeo::v3::Zero());
                
            }
            
            void WorldMenuUIButton::SetItemUnselected()
            {
                m_isItemSelected = false;
                float scale = 1.f;
                m_scale = Eegeo::v3(scale, scale, scale);
                
                m_pSprite->SetScale(m_scale);
                if(m_isFocused)
                    m_pGazeProgress->SetScale(m_scale * PROGRESS_SCALE_MULTIPLIER);
                else
                    m_pGazeProgress->SetScale(Eegeo::v3::Zero());
            }
            
        }
    }
    
}