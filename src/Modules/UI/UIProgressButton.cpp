// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "UIProgressButton.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

#define PROGRESS_SCALE_MULTIPLIER 1.1f

namespace Eegeo
{
    namespace UI
    {
        UIProgressButton::UIProgressButton(IUIRenderableFilter& uiRenderableFilter
                                     , Eegeo::UI::IUIQuadFactory& quadFactory
                                     , const std::string& assetPath
                                     , const UIProgressBarConfig& progressBarConfig
                                     , Eegeo::Helpers::ICallback0& onClickedEvent
                                     , const Eegeo::v2& size
                                     , const Eegeo::dv3& ecefPosition
                                     , const Eegeo::v3& scale
                                     , const Eegeo::v4& color
                                     , const Eegeo::v2& uvMin
                                     , const Eegeo::v2& uvMax)
        : m_onClickedEvent(onClickedEvent)
        {
            m_radius = (size.x > size.y ? size.x : size.y)/2.0f;
            Init(quadFactory, uiRenderableFilter, assetPath, progressBarConfig, size, ecefPosition, scale, color, uvMin, uvMax);
        }
        
        UIProgressButton::~UIProgressButton()
        {
            Eegeo_DELETE m_pGazeProgress;
            Eegeo_DELETE m_pSprite;
        }
        
        void UIProgressButton::Init(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter, const std::string& assetPath, const UIProgressBarConfig& progressBarConfig, const Eegeo::v2& size, const Eegeo::dv3& ecefPosition, const Eegeo::v3& scale, const Eegeo::v4& color, const Eegeo::v2& uvMin, const Eegeo::v2& uvMax)
        {
            m_pSprite = Eegeo_NEW(UISprite)(uiRenderableFilter
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
        
        bool UIProgressButton::IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider)
        {
            
            if(!m_pSprite->GetItemShouldRender())
                return false;
            
            Eegeo::Camera::RenderCamera& renderCamera = cameraProvider.GetRenderCameraForUI();
            
            if (renderCamera.GetEcefLocation().SquareDistanceTo(m_pSprite->GetEcefPosition()) < (GetItemRadius() * GetItemRadius())) {
                return false;
            }
            
            Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
            Eegeo::dv3 rayDirection;
            
            Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPoint.GetX(), screenPoint.GetY(), rayDirection);
            return Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, m_pSprite->GetEcefPosition(), GetItemRadius());
        }
        
        void UIProgressButton::Update(float dt)
        {
            m_pGazeProgress->Update(dt);
            m_pSprite->Update(dt);
        }
        
        void UIProgressButton::OnItemClicked()
        {
            m_onClickedEvent();
        }
        
        void UIProgressButton::OnFocusGained()
        {
            m_pGazeProgress->Reset();
            m_pGazeProgress->SetScale(m_pSprite->GetScale() * PROGRESS_SCALE_MULTIPLIER);
        }
        
        void UIProgressButton::OnFocusLost()
        {
            m_pGazeProgress->SetScale(v3::Zero());
        }
        
        void UIProgressButton::SetEcefPosition(const Eegeo::dv3& position)
        {
            m_pSprite->SetEcefPosition(position);
            m_pGazeProgress->SetEcefPosition(position);
        }
        
        Eegeo::dv3 UIProgressButton::GetEcefPosition()
        {
            return m_pSprite->GetEcefPosition();
        }
        
        Eegeo::v2 UIProgressButton::GetSize()
        {
            return m_pSprite->GetSize();
        }
        
        void UIProgressButton::SetColor(const Eegeo::v4& color)
        {
            m_pSprite->SetColor(color);
        }
        
        Eegeo::v4 UIProgressButton::GetColor()
        {
            return m_pSprite->GetColor();
        }
        
        void UIProgressButton::SetScale(const Eegeo::v3& scale)
        {
            m_pSprite->SetScale(scale);
            m_pGazeProgress->SetScale(scale * PROGRESS_SCALE_MULTIPLIER);
        }
        
        Eegeo::v3 UIProgressButton::GetScale()
        {
            return m_pSprite->GetScale();
        }
        
    }
}
