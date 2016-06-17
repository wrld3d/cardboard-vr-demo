// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "UIAnimatedSprite.h"
#include "Logger.h"

#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        void DeleteFrame(UISprite* frame)
        {
            Eegeo_DELETE frame;
        }
        
        UIAnimatedSprite::UIAnimatedSprite(IUIRenderableFilter& p_UIRenderableFilter
                         , IUIQuadFactory& p_IUIQuadFactory
                         , const std::string& assetPath
                         , float frameRate
                         , const Eegeo::v2& spriteGridSize
                         , int spriteId
                         , const Eegeo::v2& size
                         , const Eegeo::dv3& ecefPosition
                         , const Eegeo::v3& scale
                         , const Eegeo::v4& color)
        : m_FrameRate(frameRate)
        , m_TimeElapsed(0)
        , m_CurrentFrame(0)
        {
            m_Frames.reserve(spriteGridSize.GetX() * spriteGridSize.GetY());
            CreateFrames(p_UIRenderableFilter, p_IUIQuadFactory, assetPath, spriteGridSize, size, ecefPosition, scale, color);
        }
        
        UIAnimatedSprite::~UIAnimatedSprite()
        {
            std::for_each(m_Frames.begin(), m_Frames.end(), DeleteFrame);
            m_Frames.clear();
        }
        
        void UIAnimatedSprite::CreateFrames(Eegeo::UI::IUIRenderableFilter &p_UIRenderableFilter
                                            , IUIQuadFactory& p_IUIQuadFactory
                                            , const std::string& assetPath
                                            , const Eegeo::v2& spriteGridSize
                                            , const Eegeo::v2& size
                                            , const Eegeo::dv3& ecefPosition
                                            , const Eegeo::v3& scale
                                            , const Eegeo::v4& color)
        {
            int count = (int) (spriteGridSize.GetX() * spriteGridSize.GetY());
            
            for (int i=0; i<count; i++) {
                Eegeo::v2 outMin;
                Eegeo::v2 outMax;
                Eegeo::UI::CalculateUV(spriteGridSize, i, outMin, outMax);
                
                UISprite* frame = Eegeo_NEW(UISprite)( p_UIRenderableFilter
                                                     , p_IUIQuadFactory.CreateUIQuad(assetPath, size, outMin, outMax)
                                                     , size
                                                     , ecefPosition
                                                     , scale
                                                     , color);
                
                frame->SetItemShouldRender(false);
                m_Frames.push_back(frame);
            }
            
            m_Frames[m_CurrentFrame]->SetItemShouldRender(true);
        }
        
        void UIAnimatedSprite::Reset()
        {
            m_TimeElapsed = 0.0f;
        }
        
        void UIAnimatedSprite::Update(float dt)
        {
            m_TimeElapsed += dt;
            if(m_TimeElapsed>(1.0f/m_FrameRate)) {
                Reset();
                LoadNextFrame();
            }
            
            m_Frames[m_CurrentFrame]->Update(dt);
        }
        
        void UIAnimatedSprite::LoadNextFrame()
        {
            UISprite* oldFrame = m_Frames[m_CurrentFrame];
            oldFrame->SetItemShouldRender(false);
            
            m_CurrentFrame = (m_CurrentFrame + 1) % m_Frames.size();
            UISprite* newFrame = m_Frames[m_CurrentFrame];
            
            newFrame->SetItemShouldRender(true);
            newFrame->SetEcefPosition(oldFrame->GetEcefPosition());
            newFrame->SetScale(oldFrame->GetScale());
            newFrame->SetColor(oldFrame->GetColor());
        }
        
        void UIAnimatedSprite::SetEcefPosition(const Eegeo::dv3 &ecefPosition)
        {
            m_Frames[m_CurrentFrame]->SetEcefPosition(ecefPosition);
        }
        
        void UIAnimatedSprite::SetScale(const Eegeo::v3 &scale)
        {
            m_Frames[m_CurrentFrame]->SetScale(scale);
        }
        
        void UIAnimatedSprite::SetColor(const Eegeo::v4 &color)
        {
            m_Frames[m_CurrentFrame]->SetColor(color);
        }
    }
}
