// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "WorldMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            
            WorldMenuItem::WorldMenuItem(const TWorldMenuItemId id
                                         , const TWorldMenuItemSpriteId spriteId
                                         , Eegeo::Helpers::ICallback1<WorldMenuItem&>& onClickedEvent
                                         , const void* pUserData
                                         , float marginLeft
                                         , float marginRight)
            : m_id(id)
            , m_spriteId(spriteId)
            , m_onClickedEvent(onClickedEvent)
            , m_pUserData(pUserData)
            , m_marginLeft(marginLeft)
            , m_marginRight(marginRight)
            {
            }
            
            TWorldMenuItemId WorldMenuItem::GetId() const
            {
                return m_id;
            }
            
            TWorldMenuItemId WorldMenuItem::GetSpriteId() const
            {
                return m_spriteId;
            }
            
            const void* WorldMenuItem::GetUserData() const
            {
                return m_pUserData;
            }
            
            
            Eegeo::Helpers::ICallback1<WorldMenuItem&>& WorldMenuItem::GetCallback() const
            {
                return m_onClickedEvent;
            }
        }
    }
    
}