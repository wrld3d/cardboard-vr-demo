//
//  UISprite.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIBaseItem.h"

#include "UISprite.h"
#include "RenderingModule.h"
#include "IPlatformAbstractionModule.h"

namespace Eegeo
{
    namespace UI
    {
        
        UISprite::UISprite(UIQuad* quad
                           , Eegeo::v2 size
                           , Eegeo::dv3 ecefPosition
                           , Eegeo::v3 scale
                           , Eegeo::v4 color
                           , int spriteId
                           , Eegeo::v2 spriteGridSize)
        : UIBaseItem(ecefPosition, size, scale, color)
        , m_Quad(quad){
            
            m_SpriteId = spriteId;
            m_SpriteGridSize = Eegeo::v2(spriteGridSize);
            
            UpdateUVs();
            

        }
        
        UISprite::~UISprite()
        {
            delete m_Quad;
        }
        
        void UISprite::Update(float dt)
        {
            if(IsDirty())
            {
                m_Quad->SetEcefPosition(GetEcefPosition());
                m_Quad->SetColor(GetColor());
                m_Quad->SetScale(GetScale());
//                m_Quad->SetSize(GetSize()); Not yet incorporated.
                SetDirty(false);
            }
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
            
            SetDirty();
            
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
            return ((int)(m_SpriteGridSize.GetX()+m_SpriteGridSize.GetY()))-1;
        }
        
        
    }
}
