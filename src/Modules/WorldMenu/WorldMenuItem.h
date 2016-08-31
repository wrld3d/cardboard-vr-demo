// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "WorldMenu.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "string"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            /*!
             * \brief Defines the data model for a World Menu Item.
             *
             *  WorldMenuItem defines a World Menu Item.
             *
             */
            class WorldMenuItem : protected Eegeo::NonCopyable
            {
            public:
                /*! Create a World Menu Item object at a particular position in the world.
                 * \param id A unique identifier for the World Menu Item.
                 * \param id A unique identifier for the Sprite of World Menu Item.
                 * \param latLongAlt The position of the World Menu Item.
                 * \param p_FileName The name texture file to load icon from.
                 * \param p_Dimension The dimensions of the World Menu Item.
                 * \param p_uvMin The min uvs of the World Menu Item sprite.
                 * \param p_uvMax The max uvs of the World Menu Item sprite.
                 * \param pUserData An optional piece of application user data to be attached to the World Menu Item. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to World Menu Item objects.
                 * \return A World Menu Item object
                 */
                WorldMenuItem(const TWorldMenuItemId id
                                 , const TWorldMenuItemSpriteId spriteId
                                 , Eegeo::Helpers::ICallback1<WorldMenuItem&>& onClickedEvent
                                 , const void* pUserData = NULL
                                 , float marginLeft = 0
                                 , float marginRight = 0);
                
                /*! Get the unique identifier for the WorldMenuItem.
                 * \return The WorldMenuItem's unique identifier.
                 */
                TWorldMenuItemId GetId() const;
                
                /*! Get the unique identifier for the WorldMenuItem Sprite.
                 * \return The WorldMenuItem's identifier for Sprite.
                 */
                TWorldMenuItemId GetSpriteId() const;
                
                /*! Get the application supplied user data for the WorldMenuItem.
                 * \return The WorldMenuItem's application supplied user data.
                 */
                const void* GetUserData() const;
                
                Eegeo::Helpers::ICallback1<WorldMenuItem&>& GetCallback() const;
                
                float GetMarginLeft(){ return m_marginLeft;}
                
                float GetMarginRight(){ return m_marginRight;}
                
            private:
                
                float m_marginLeft;
                float m_marginRight;
                
                TWorldMenuItemId m_id;
                TWorldMenuItemSpriteId m_spriteId;
                const void* const m_pUserData;
                Eegeo::Helpers::ICallback1<WorldMenuItem&>& m_onClickedEvent;
            };
        }
    }
}
