//
//  UIBaseItem.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIBaseItem.h"

namespace Eegeo
{
    namespace UI
    {
        
        UIBaseItem::UIBaseItem(Eegeo::dv3 position, Eegeo::v2 size, Eegeo::v3 scale, Eegeo::v4 color)
        {
            m_EcefPosition = Eegeo::dv3(position);
            m_Size = Eegeo::v2(size);
            m_Scale = Eegeo::v3(scale);
            m_Color = Eegeo::v4(color);
            
            m_IsDirty = true;
        }
        
        UIBaseItem::~UIBaseItem()
        {
        }
        
        bool UIBaseItem::IsDirty()
        {
            return m_IsDirty;
        }
        
        void UIBaseItem::SetDirty(bool isDirty)
        {
            m_IsDirty = isDirty;
        }
        
        void UIBaseItem::SetEcefPosition(Eegeo::dv3 position)
        {
            m_EcefPosition = Eegeo::dv3(position);
            SetDirty();
        }
        
        const Eegeo::dv3& UIBaseItem::GetEcefPosition()
        {
            return m_EcefPosition;
        }
        
        void UIBaseItem::SetSize(Eegeo::v2 size)
        {
            m_Size = Eegeo::v2(size);
            SetDirty();
        }
        
        const Eegeo::v2& UIBaseItem::GetSize()
        {
            return m_Size;
        }
        
        void UIBaseItem::SetColor(Eegeo::v4 color)
        {
            m_Color = Eegeo::v4(color);
            SetDirty();
        }
        
        const Eegeo::v4& UIBaseItem::GetColor()
        {
            return m_Color;
        }
        
        void UIBaseItem::SetScale(Eegeo::v3 scale)
        {
            m_Scale = Eegeo::v3(scale);
            SetDirty();
        }
        
        const Eegeo::v3& UIBaseItem::GetScale()
        {
            return m_Scale;
        }

        
    }
}