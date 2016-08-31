// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "InteriorMenuItem.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        
        InteriorMenuItem::InteriorMenuItem(const TInteriorMenuItemId id
                                           , const TInteriorMenuItemSpriteId spriteId
                                           , Eegeo::Helpers::ICallback1<InteriorMenuItem&>& onClickedEvent
                                           , const void* pUserData)
        : m_id(id)
        , m_spriteId(spriteId)
        , m_onClickedEvent(onClickedEvent)
        , m_pUserData(pUserData)
        {
        }
        
        TInteriorMenuItemId InteriorMenuItem::GetId() const
        {
            return m_id;
        }
        
        TInteriorMenuItemId InteriorMenuItem::GetSpriteId() const
        {
            return m_spriteId;
        }
        
        const void* InteriorMenuItem::GetUserData() const
        {
            return m_pUserData;
        }
        
        
        Eegeo::Helpers::ICallback1<InteriorMenuItem&>& InteriorMenuItem::GetCallback() const
        {
            return m_onClickedEvent;
        }
    }
}
