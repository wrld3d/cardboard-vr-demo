// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "InteriorMenu.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "string"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        /*!
         * \brief Defines the data model for a Interior Menu Item.
         *
         *  InteriorMenuItem defines a Interior Menu Item.
         *
         */
        class InteriorMenuItem : protected Eegeo::NonCopyable
        {
        public:
            /*! Create a Interior Menu Item object at a particular position in the world.
             * \param id A unique identifier for the Interior Menu Item.
             * \param id A unique identifier for the Sprite of Interior Menu Item.
             * \param latLongAlt The position of the Interior Menu Item.
             * \param p_FileName The name texture file to load icon from.
             * \param p_Dimension The dimensions of the Interior Menu Item.
             * \param p_uvMin The min uvs of the Interior Menu Item sprite.
             * \param p_uvMax The max uvs of the Interior Menu Item sprite.
             * \param pUserData An optional piece of application user data to be attached to the Interior Menu Item. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to Interior Menu Item objects.
             * \return A Interior Menu Item object
             */
            InteriorMenuItem(const TInteriorMenuItemId id
                             , const TInteriorMenuItemSpriteId spriteId
                             , Eegeo::Helpers::ICallback1<InteriorMenuItem&>& onClickedEvent
                             , const void* pUserData = NULL);
            
            /*! Get the unique identifier for the InteriorMenuItem.
             * \return The InteriorMenuItem's unique identifier.
             */
            TInteriorMenuItemId GetId() const;
            
            /*! Get the unique identifier for the InteriorMenuItem Sprite.
             * \return The InteriorMenuItem's identifier for Sprite.
             */
            TInteriorMenuItemId GetSpriteId() const;
            
            /*! Get the application supplied user data for the InteriorMenuItem.
             * \return The InteriorMenuItem's application supplied user data.
             */
            const void* GetUserData() const;
            
            
            Eegeo::Helpers::ICallback1<InteriorMenuItem&>& GetCallback() const;
            
        private:
            TInteriorMenuItemId m_id;
            TInteriorMenuItemSpriteId m_spriteId;
            const void* const m_pUserData;
            Eegeo::Helpers::ICallback1<InteriorMenuItem&>& m_onClickedEvent;
        };
    }
}
