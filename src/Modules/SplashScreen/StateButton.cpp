// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "StateButton.h"
#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "Logger.h"

#define PROGRESS_SCALE_MULTIPLIER 1.1f

namespace Eegeo
{
    namespace UI
    {
        namespace SplashScreen
        {
            StateButton::StateButton(IUIRenderableFilter& uiRenderableFilter
                                               , Eegeo::UI::IUIQuadFactory& quadFactory
                                               , const std::string& assetPath
                                               , int activeSpriteId
                                               , int deactiveSpriteId
                                               , int spriteSheetSize
                                               , const UIProgressBarConfig& progressBarConfig
                                               , Eegeo::Helpers::ICallback0& onClickedEvent
                                               , const Eegeo::v2& size
                                               , const Eegeo::dv3& ecefPosition
                                               , const Eegeo::v3& scale
                                               , const Eegeo::v4& color)
            : m_onClickedEvent(onClickedEvent)
            {
                m_radius = (size.x > size.y ? size.x : size.y)/2.0f;
                Init(quadFactory, uiRenderableFilter, assetPath, progressBarConfig, size, ecefPosition, scale, color, activeSpriteId, deactiveSpriteId, spriteSheetSize);
            }
            
            StateButton::~StateButton()
            {
                Eegeo_DELETE m_pActiveState;
                Eegeo_DELETE m_pDeactiveState;
                Eegeo_DELETE m_pGazeProgress;
            }
            
            void StateButton::Init(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter, const std::string& assetPath, const UIProgressBarConfig& progressBarConfig, const Eegeo::v2& size, const Eegeo::dv3& ecefPosition, const Eegeo::v3& scale, const Eegeo::v4& color, int activeSpriteId, int deactiveSpriteId, int spriteSheetSize)
            {
                
                Eegeo::v2 minUV;
                Eegeo::v2 maxUV;
                
                calculateUV(activeSpriteId, spriteSheetSize, minUV, maxUV);
                m_pActiveState = Eegeo_NEW(UISprite)(uiRenderableFilter
                                                     , quadFactory.CreateUIQuad(assetPath, size, minUV, maxUV)
                                                     , size
                                                     , ecefPosition
                                                     , scale
                                                     , color
                                                     );
                
                calculateUV(deactiveSpriteId, spriteSheetSize, minUV, maxUV);
                m_pDeactiveState = Eegeo_NEW(UISprite)(uiRenderableFilter
                                                     , quadFactory.CreateUIQuad(assetPath, size, minUV, maxUV)
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
                m_pActiveState->SetItemShouldRender(true);
                m_pDeactiveState->SetItemShouldRender(false);
            }
            
            void StateButton::calculateUV(int position, int spriteSize, Eegeo::v2& outMinUV, Eegeo::v2&outMaxUV)
            {
                int row = position%spriteSize;
                int col = position/spriteSize;
                float fraction = 1.f/spriteSize;
                
                outMinUV = Eegeo::v2(fraction*row, fraction*col);
                outMaxUV = Eegeo::v2(fraction*(row+1), fraction*(col+1));
                
            }
            
            bool StateButton::IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider)
            {
                
                if(!m_pActiveState->GetItemShouldRender())
                    return false;
                
                Eegeo::Camera::RenderCamera& renderCamera = cameraProvider.GetRenderCameraForUI();
                
                if (renderCamera.GetEcefLocation().SquareDistanceTo(m_pActiveState->GetEcefPosition()) < (GetItemRadius() * GetItemRadius())) {
                    return false;
                }
                
                Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
                Eegeo::dv3 rayDirection;
                
                Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPoint.GetX(), screenPoint.GetY(), rayDirection);
                return Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, m_pActiveState->GetEcefPosition(), GetItemRadius());
            }
            
            void StateButton::Update(float dt)
            {
                m_pActiveState->Update(dt);
                m_pDeactiveState->Update(dt);
                m_pGazeProgress->Update(dt);
            }
            
            void StateButton::OnItemClicked()
            {
                SetDeactive();
                m_onClickedEvent();
            }
            
            void StateButton::OnFocusGained()
            {
                m_pGazeProgress->Reset();
                m_pGazeProgress->SetScale(m_pActiveState->GetScale() * PROGRESS_SCALE_MULTIPLIER);
            }
            
            void StateButton::OnFocusLost()
            {
                m_pGazeProgress->SetScale(v3::Zero());
            }
            
            void StateButton::SetActive()
            {
                m_pActiveState->SetItemShouldRender(true);
                m_pDeactiveState->SetItemShouldRender(false);
            }
            
            void StateButton::SetDeactive()
            {
                m_pActiveState->SetItemShouldRender(false);
                m_pDeactiveState->SetItemShouldRender(true);
            }
            
            void StateButton::Hide()
            {
                m_pActiveState->SetItemShouldRender(false);
                m_pDeactiveState->SetItemShouldRender(false);
            }

            void StateButton::Show()
            {
                SetActive();
            }
            
            void StateButton::SetEcefPosition(const Eegeo::dv3& position)
            {
                m_pActiveState->SetEcefPosition(position);
                m_pDeactiveState->SetEcefPosition(position);
                m_pGazeProgress->SetEcefPosition(position);
            }
            
            Eegeo::dv3 StateButton::GetEcefPosition()
            {
                return m_pActiveState->GetEcefPosition();
            }
            
            Eegeo::v2 StateButton::GetSize()
            {
                return m_pActiveState->GetSize();
            }
            
            void StateButton::SetColor(const Eegeo::v4& color)
            {
                m_pActiveState->SetColor(color);
                m_pDeactiveState->SetColor(color);
            }
            
            Eegeo::v4 StateButton::GetColor()
            {
                return m_pActiveState->GetColor();
            }
            
            void StateButton::SetScale(const Eegeo::v3& scale)
            {
                m_pActiveState->SetScale(scale);
                m_pGazeProgress->SetScale(scale * PROGRESS_SCALE_MULTIPLIER);
            }
            
            Eegeo::v3 StateButton::GetScale()
            {
                return m_pActiveState->GetScale();
            }
        }
    }
}
