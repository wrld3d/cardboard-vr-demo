//
//  DeadZoneMenu.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

#include "DeadZoneMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuItem::DeadZoneMenuItem(const TDeadZoneMenuItemId id
                                 , const TDeadZoneMenuItemSpriteId spriteId
                                 , Eegeo::Helpers::ICallback0& p_OnClickedEvent
                                 , const void* pUserData)
            : m_id(id)
            , m_SpriteId(spriteId)
            , m_OnClickedEvent(p_OnClickedEvent)
            , m_pUserData(pUserData)
            {
            }
            
            TDeadZoneMenuItemId DeadZoneMenuItem::GetId() const
            {
                return m_id;
            }
            
            TDeadZoneMenuItemId DeadZoneMenuItem::GetSpriteId() const
            {
                return m_SpriteId;
            }
            
            const void* DeadZoneMenuItem::GetUserData() const
            {
                return m_pUserData;
            }
            
            
            Eegeo::Helpers::ICallback0& DeadZoneMenuItem::GetCallback() const
            {
                return m_OnClickedEvent;
            }
        }
    }
}