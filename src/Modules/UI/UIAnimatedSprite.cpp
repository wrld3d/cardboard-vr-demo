//
//  UIAnimatedQuad.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIAnimatedSprite.h"
#include "UISprite.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        
        UIAnimatedSprite::UIAnimatedSprite( UIQuad* quad
                         , float frameRate
                         , Eegeo::v2 spriteGridSize
                         , int spriteId
                         , Eegeo::v2 size
                         , Eegeo::dv3 ecefPosition
                         , Eegeo::v3 scale
                         , Eegeo::v4 color)
        : UISprite(quad, size, ecefPosition, scale, color, spriteId, spriteGridSize)
        , m_FrameRate(frameRate)
        {
            Init();
        }
        
        void UIAnimatedSprite::Init()
        {
            m_TimeElapsed = 0;
            m_Radius = (GetSize().x > GetSize().y ? GetSize().x : GetSize().y)/2.0f;
        }
        
        UIAnimatedSprite::~UIAnimatedSprite(){
        }
        
        void UIAnimatedSprite::Reset()
        {
            m_TimeElapsed = 0.0f;
        }
        
        void UIAnimatedSprite::Update(float dt)
        {
            
            UISprite::Update(dt);
            
            m_TimeElapsed += dt;
            if(m_TimeElapsed>(1.0f/m_FrameRate))
            {
                Reset();
                SetNextSprite();
            }
            
        }
        
        
    }
}