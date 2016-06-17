//
//  UISprite.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UISprite.h"

#include "UISprite.h"
#include "RenderingModule.h"
#include "IPlatformAbstractionModule.h"

namespace Eegeo
{
    namespace UI
    {
        
        UISprite::UISprite(IUIRenderableFilter& p_UIRenderableFilter
                           , UIQuad* quad
                           , const Eegeo::v2& size
                           , const Eegeo::dv3& ecefPosition
                           , const Eegeo::v3& scale
                           , const Eegeo::v4& color)
        : m_Quad(quad)
        , m_UIRenderableFilter(p_UIRenderableFilter){
            m_Size = size;
            
            m_UIRenderableFilter.RegisterRenderable(m_Quad);
            SetEcefPosition(ecefPosition);
            SetScale(scale);
            SetColor(color);
        }
        
        UISprite::~UISprite()
        {
            m_UIRenderableFilter.UnRegisterRenderable(m_Quad);
            delete m_Quad;
        }
        
        void UISprite::Update(float dt)
        {
        }
        
        void UISprite::SetEcefPosition(const Eegeo::dv3& position)
        {
            m_Quad->SetEcefPosition(position);
        }
        
        Eegeo::dv3 UISprite::GetEcefPosition()
        {
            return m_Quad->GetEcefPosition();
        }
        
        void UISprite::SetSize(const Eegeo::v2& size)
        {
            m_Size = Eegeo::v2(size);
        }
        
        Eegeo::v2 UISprite::GetSize()
        {
            return m_Size;
        }
        
        void UISprite::SetColor(const Eegeo::v4& color)
        {
            m_Quad->SetColor(color);
        }
        
        Eegeo::v4 UISprite::GetColor()
        {
            return m_Quad->GetColor();
        }
        
        void UISprite::SetScale(const Eegeo::v3& scale)
        {
            m_Quad->SetScale(scale);
        }
        
        Eegeo::v3 UISprite::GetScale()
        {
            return m_Quad->GetScale();
        }
        
        
    }
}
