//
//  UIAnimatedQuad.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIAnimatedSprite.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        
        UIAnimatedSprite::UIAnimatedSprite(UIQuad* quad
                                           , Eegeo::Helpers::ICallback0& onClickedEvent
                                           , const Eegeo::v2& dimension
                                           , Eegeo::v2& framesGridSize
                                           , float frameRate
        ):
        m_Quad(quad),
        m_FramesGridSize(framesGridSize),
        m_FrameRate(frameRate),
        m_OnClickedEvent(onClickedEvent)
        {
            m_TimeElapsed = 0;
            m_CurrentFrameNumber = 0;
            m_Radius = (dimension.x > dimension.y ? dimension.x : dimension.y)/2.0f;
        }
        
        UIAnimatedSprite::~UIAnimatedSprite(){
            Eegeo_DELETE m_Quad;
        }
        
        void UIAnimatedSprite::Reset()
        {
            m_TimeElapsed = 0.0f;
            m_CurrentFrameNumber = 0;
        }
        
        void UIAnimatedSprite::SetScale(Eegeo::v3 p_scale) {
            m_Quad->SetScale(p_scale);
            m_scale = p_scale;
        }
        
        void UIAnimatedSprite::Update(float dt)
        {
            m_TimeElapsed += dt;
            if(m_TimeElapsed>(1.0f/m_FrameRate)){
                
                m_TimeElapsed = 0.0f;
                
                m_CurrentFrameNumber+=1;
                
                if(m_CurrentFrameNumber>=(int) (m_FramesGridSize.GetX()*m_FramesGridSize.GetY()))
                    m_CurrentFrameNumber = 0;
                
                int x = m_CurrentFrameNumber % ((int) m_FramesGridSize.GetX());
                int y = m_CurrentFrameNumber / ((int) m_FramesGridSize.GetY());
                float xSize = 1.f/m_FramesGridSize.GetX();
                float ySize = 1.f/m_FramesGridSize.GetY();
                                
                Eegeo::v2 min(x*xSize, y*ySize);
                Eegeo::v2 max((x+1)*xSize, (y+1)*ySize);
                m_Quad->UpdateUVs(min, max);
                m_Quad->SetScale(m_scale);
                
            }
            
            
        }
        
        void UIAnimatedSprite::OnItemClicked()
        {
            m_OnClickedEvent();
        }
        
        void UIAnimatedSprite::OnFocusGained()
        {
            m_Quad->SetScale(Eegeo::v3::One() * 1.1f);
        }
        
        void UIAnimatedSprite::OnFocusLost()
        {
            m_Quad->SetScale(Eegeo::v3::One());
        }
        
    }
}