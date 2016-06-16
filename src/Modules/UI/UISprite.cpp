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
                           , Eegeo::v2 size
                           , Eegeo::dv3 ecefPosition
                           , Eegeo::v3 scale
                           , Eegeo::v4 color
                           , int spriteId
                           , Eegeo::v2 spriteGridSize)
        : m_Quad(quad)
        , m_UIRenderableFilter(p_UIRenderableFilter){
          
            m_EcefPosition = ecefPosition;
            m_Scale = scale;
            m_Size = size;
            m_Color = color;
            m_SpriteId = spriteId;
            m_SpriteGridSize = Eegeo::v2(spriteGridSize);
            
            UpdateUVs();
            
            m_UIRenderableFilter.RegisterRenderable(m_Quad);
        }
        
        UISprite::~UISprite()
        {
            m_UIRenderableFilter.UnRegisterRenderable(m_Quad);
            delete m_Quad;
        }
        
        void UISprite::Update(float dt)
        {
        }
        
        void UISprite::SetEcefPosition(Eegeo::dv3 position)
        {
            m_EcefPosition = Eegeo::dv3(position);
            m_Quad->SetEcefPosition(m_EcefPosition);
        }
        
        const Eegeo::dv3& UISprite::GetEcefPosition()
        {
            return m_EcefPosition;
        }
        
        void UISprite::SetSize(Eegeo::v2 size)
        {
            m_Size = Eegeo::v2(size);
        }
        
        const Eegeo::v2& UISprite::GetSize()
        {
            return m_Size;
        }
        
        void UISprite::SetColor(Eegeo::v4 color)
        {
            m_Color = Eegeo::v4(color);
            m_Quad->SetColor(m_Color);
        }
        
        const Eegeo::v4& UISprite::GetColor()
        {
            return m_Color;
        }
        
        void UISprite::SetScale(Eegeo::v3 scale)
        {
            m_Scale = Eegeo::v3(scale);
            m_Quad->SetScale(m_Scale);
        }
        
        const Eegeo::v3& UISprite::GetScale()
        {
            return m_Scale;
        }
        
        void UISprite::UpdateUVs(){
            
            int x = m_SpriteId % ((int) m_SpriteGridSize.GetX());
            int y = m_SpriteId / ((int) m_SpriteGridSize.GetY());
            float xSize = 1.f/m_SpriteGridSize.GetX();
            float ySize = 1.f/m_SpriteGridSize.GetY();
            
            m_MinUV = Eegeo::v2(x*xSize, y*ySize);
            m_MaxUV = Eegeo::v2((x+1)*xSize, (y+1)*ySize);
        }
        
        void UISprite::SetSpriteId(int spriteId)
        {
            m_SpriteId = spriteId;
            UpdateUVs();
            m_Quad->UpdateUVs(m_MinUV, m_MaxUV);
            m_Quad->SetScale(m_Scale);
            m_Quad->SetColor(m_Color);
            m_Quad->SetEcefPosition(m_EcefPosition);
            
            
        }
        
        int UISprite::GetSpriteId()
        {
            return m_SpriteId;
        }
        
        void UISprite::SetNextSprite()
        {
            int spriteId = GetSpriteId()+1;
            if(spriteId > GetMaxSpriteId())
            {
                spriteId = 0;
            }
            SetSpriteId(spriteId);
        }
        
        void UISprite::SetPreviousSprite()
        {
            int spriteId = GetSpriteId()-1;
            if(spriteId < 0)
            {
                spriteId = GetMaxSpriteId();
            }
            SetSpriteId(spriteId);
        }
        
        int UISprite::GetMaxSpriteId()
        {
            return ((int)(m_SpriteGridSize.GetX()*m_SpriteGridSize.GetY()))-1;
        }
        
        
    }
}
