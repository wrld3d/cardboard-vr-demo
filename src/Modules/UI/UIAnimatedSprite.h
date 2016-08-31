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
            TSpriteFrames m_frames;

            int m_currentFrame;
            float m_timeElapsed;
            float m_frameRate;

            void LoadNextFrame();
            
        public:
            
            UIAnimatedSprite(IUIRenderableFilter& uiRenderableFilter
                             , IUIQuadFactory& uiQuadFactory
                             , const std::string& assetPath
                             , float frameRate
                             , const Eegeo::v2& spriteGridSize = Eegeo::v2::One()
                             , int spriteId = 0
                             , const Eegeo::v2&  size = Eegeo::v2::One()
                             , const Eegeo::dv3& ecefPosition = Eegeo::dv3::Zero()
                             , const Eegeo::v3& scale = Eegeo::v3::One()
                             , const Eegeo::v4& color = Eegeo::v4::One()
                             , const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::Values::AfterWorld);
        
            
            virtual ~UIAnimatedSprite();
            
            void CreateFrames(IUIRenderableFilter& uiRenderableFilter
                              , IUIQuadFactory& uiQuadFactory
                              , const std::string& assetPath
                              , const Eegeo::v2& spriteGridSize
                              , const Eegeo::v2& size
                              , const Eegeo::dv3& ecefPosition
                              , const Eegeo::v3& scale
                              , const Eegeo::v4& color
                              , const Eegeo::Rendering::LayerIds::Values renderLayer);
            void Reset();
            
            virtual void Update(float dt);
            
            void SetEcefPosition(const dv3& ecefPosition);
            void SetScale(const Eegeo::v3& scale);
            void SetColor(const Eegeo::v4& color);
        };
        
    }
}
