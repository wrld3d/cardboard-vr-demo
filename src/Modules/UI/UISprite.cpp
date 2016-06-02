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
                           , Eegeo::v2 spriteGridSize
                           , int spriteId
                           , Eegeo::dv3 ecefPosition
                           , Eegeo::v2 size
                           , Eegeo::v3 scale
                           , Eegeo::v4 color)
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
        
        void UISprite::Update()
        {
            if(IsDirty())
            {
                m_Quad->SetEcefPosition(GetEcefPosition());
                m_Quad->SetColor(GetColor());
                m_Quad->SetScale(GetScale());
//                m_Quad->SetSize(GetSize()); Not yet incorporated.
                SetDirty();
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
        }
        
        int UISprite::getSpriteId()
        {
            return m_SpriteId;
        }
        
        
        
    }
}
