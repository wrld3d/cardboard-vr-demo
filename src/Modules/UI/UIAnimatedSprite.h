// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "UISprite.h"
#include "ICallback.h"
#include "UIQuad/UIQuadFactory.h"
#include <vector>

namespace Eegeo
{
    namespace UI
    {
        class UIAnimatedSprite
        {
            
        private:
            typedef std::vector<UISprite*> TSpriteFrames;
            TSpriteFrames m_Frames;

            int m_CurrentFrame;
            float m_TimeElapsed;
            float m_FrameRate;

            void LoadNextFrame();
            
        public:
            
            UIAnimatedSprite(IUIRenderableFilter& p_UIRenderableFilter
                             , IUIQuadFactory& p_IUIQuadFactory
                             , const std::string& assetPath
                             , float frameRate
                             , const Eegeo::v2& spriteGridSize = Eegeo::v2::One()
                             , int spriteId = 0
                             , const Eegeo::v2&  size = Eegeo::v2::One()
                             , const Eegeo::dv3& ecefPosition = Eegeo::dv3::Zero()
                             , const Eegeo::v3& scale = Eegeo::v3::One()
                             , const Eegeo::v4& color = Eegeo::v4::One()
                             );
        
            
            virtual ~UIAnimatedSprite();
            
            void CreateFrames(IUIRenderableFilter& p_UIRenderableFilter
                              , IUIQuadFactory& p_IUIQuadFactory
                              , const std::string& assetPath
                              , const Eegeo::v2& spriteGridSize
                              , const Eegeo::v2& size
                              , const Eegeo::dv3& ecefPosition
                              , const Eegeo::v3& scale
                              , const Eegeo::v4& color);
            void Reset();
            
            virtual void Update(float dt);
            
            void SetEcefPosition(const dv3& ecefPosition);
            void SetScale(const Eegeo::v3& scale);
            void SetColor(const Eegeo::v4& color);
        };
        
    }
}
