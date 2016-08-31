// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "DeadZoneMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuItem::DeadZoneMenuItem(const TDeadZoneMenuItemId id
                                 , const TDeadZoneMenuItemSpriteId spriteId
                                 , Eegeo::Helpers::ICallback0& onClickedEvent
                                 , const void* pUserData)
            : m_id(id)
            , m_spriteId(spriteId)
            , m_OnClickedEvent(onClickedEvent)
            , m_pUserData(pUserData)
            {
            }
            
            TDeadZoneMenuItemId DeadZoneMenuItem::GetId() const
            {
                return m_id;
            }
            
            TDeadZoneMenuItemId DeadZoneMenuItem::GetSpriteId() const
            {
                return m_spriteId;
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
