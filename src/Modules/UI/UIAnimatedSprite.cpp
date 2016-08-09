// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "UIAnimatedSprite.h"
#include "Logger.h"

#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        void DeleteFrame(UISprite* pFrame)
        {
            Eegeo_DELETE pFrame;
        }
        
        UIAnimatedSprite::UIAnimatedSprite(IUIRenderableFilter& uiRenderableFilter
                         , IUIQuadFactory& uiQuadFactory
                         , const std::string& assetPath
                         , float frameRate
                         , const Eegeo::v2& spriteGridSize
                         , int spriteId
                         , const Eegeo::v2& size
                         , const Eegeo::dv3& ecefPosition
                         , const Eegeo::v3& scale
                         , const Eegeo::v4& color
                         , const Eegeo::Rendering::LayerIds::Values renderLayer)
        : m_frameRate(frameRate)
        , m_timeElapsed(0)
        , m_currentFrame(0)
        {
            m_frames.reserve(spriteGridSize.GetX() * spriteGridSize.GetY());
            CreateFrames(uiRenderableFilter, uiQuadFactory, assetPath, spriteGridSize, size, ecefPosition, scale, color, renderLayer);
        }
        
        UIAnimatedSprite::~UIAnimatedSprite()
        {
            std::for_each(m_frames.begin(), m_frames.end(), DeleteFrame);
            m_frames.clear();
        }
        
        void UIAnimatedSprite::CreateFrames(Eegeo::UI::IUIRenderableFilter &uiRenderableFilter
                                            , IUIQuadFactory& uiQuadFactory
                                            , const std::string& assetPath
                                            , const Eegeo::v2& spriteGridSize
                                            , const Eegeo::v2& size
                                            , const Eegeo::dv3& ecefPosition
                                            , const Eegeo::v3& scale
                                            , const Eegeo::v4& color
                                            , const Eegeo::Rendering::LayerIds::Values renderLayer)
        {
            int count = (int) (spriteGridSize.GetX() * spriteGridSize.GetY());
            
            for (int i=0; i<count; i++) {
                Eegeo::v2 outMin;
                Eegeo::v2 outMax;
                Eegeo::UI::CalculateUV(spriteGridSize, i, outMin, outMax);
                
                UISprite* pFrame = Eegeo_NEW(UISprite)( uiRenderableFilter
                                                     , uiQuadFactory.CreateUIQuad(assetPath
                                                                                  , size
                                                                                  , outMin
                                                                                  , outMax
                                                                                  , renderLayer)
                                                     , size
                                                     , ecefPosition
                                                     , scale
                                                     , color);
                
                pFrame->SetItemShouldRender(false);
                pFrame->SetShouldFade(false);
                m_frames.push_back(pFrame);
            }
            
            m_frames[m_currentFrame]->SetItemShouldRender(true);
        }
        
        void UIAnimatedSprite::Reset()
        {
            m_timeElapsed = 0.0f;
            m_currentFrame = 0;
        }
        
        void UIAnimatedSprite::Update(float dt)
        {
            m_timeElapsed += dt;
            if(m_timeElapsed>(1.0f/m_frameRate)) {
                m_timeElapsed = 0.0f;
                LoadNextFrame();
            }
            
            m_frames[m_currentFrame]->Update(dt);
        }
        
        void UIAnimatedSprite::LoadNextFrame()
        {
            UISprite* pOldFrame = m_frames[m_currentFrame];
            pOldFrame->SetItemShouldRender(false);
            
            m_currentFrame = (m_currentFrame + 1) % m_frames.size();
            UISprite* pNewFrame = m_frames[m_currentFrame];
            
            pNewFrame->SetItemShouldRender(true);
            pNewFrame->SetEcefPosition(pOldFrame->GetEcefPosition());
            pNewFrame->SetScale(pOldFrame->GetScale());
            pNewFrame->SetColor(pOldFrame->GetColor());
        }
        
        void UIAnimatedSprite::SetEcefPosition(const Eegeo::dv3 &ecefPosition)
        {
            m_frames[m_currentFrame]->SetEcefPosition(ecefPosition);
        }
        
        void UIAnimatedSprite::SetScale(const Eegeo::v3 &scale)
        {
            m_frames[m_currentFrame]->SetScale(scale);
        }
        
        void UIAnimatedSprite::SetColor(const Eegeo::v4 &color)
        {
            m_frames[m_currentFrame]->SetColor(color);
        }
    }
}
