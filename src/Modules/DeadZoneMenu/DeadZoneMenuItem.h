// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "DeadZoneMenu.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "string"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            /*!
             * \brief Defines the data model for a Deadzone Menu Item.
             *
             *  DeadZoneMenuItem defines a Deadzone Menu Item.
             *
             */
            class DeadZoneMenuItem : protected Eegeo::NonCopyable
            {
            public:
                /*! Create a Deadzone Menu Item object at a particular position in the world.
                 * \param id A unique identifier for the Deadzone Menu Item.
                 * \param id A unique identifier for the Sprite of Deadzone Menu Item.
                 * \param latLongAlt The position of the Deadzone Menu Item.
                 * \param p_FileName The name texture file to load icon from.
                 * \param p_Dimension The dimensions of the Deadzone Menu Item.
                 * \param p_uvMin The min uvs of the Deadzone Menu Item sprite.
                 * \param p_uvMax The max uvs of the Deadzone Menu Item sprite.
                 * \param pUserData An optional piece of application user data to be attached to the Deadzone Menu Item. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to Deadzone Menu Item objects.
                 * \return A Deadzone Menu Item object
                 */
                DeadZoneMenuItem(const TDeadZoneMenuItemId id
                          , const TDeadZoneMenuItemSpriteId spriteId
                          , Eegeo::Helpers::ICallback0& onClickedEvent
                          , const void* pUserData = NULL);
                
                /*! Get the unique identifier for the DeadZoneMenuItem.
                 * \return The DeadZoneMenuItem's unique identifier.
                 */
                TDeadZoneMenuItemId GetId() const;
                
                /*! Get the unique identifier for the DeadZoneMenuItem Sprite.
                 * \return The DeadZoneMenuItem's identifier for Sprite.
                 */
                TDeadZoneMenuItemId GetSpriteId() const;
                
                /*! Get the application supplied user data for the DeadZoneMenuItem.
                 * \return The DeadZoneMenuItem's application supplied user data.
                 */
                const void* GetUserData() const;
                
            
                Eegeo::Helpers::ICallback0& GetCallback() const;
                
            private:
                TDeadZoneMenuItemId m_id;
                TDeadZoneMenuItemSpriteId m_spriteId;
                const void* const m_pUserData;
                Eegeo::Helpers::ICallback0& m_OnClickedEvent;
            };
        }
    }
}
