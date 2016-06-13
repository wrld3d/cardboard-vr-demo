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
                 * \param latLongAlt The position of the Deadzone Menu Item.
                 * \param p_FileName The name texture file to load icon from.
                 * \param p_Dimension The dimensions of the Deadzone Menu Item.
                 * \param p_uvMin The min uvs of the Deadzone Menu Item sprite.
                 * \param p_uvMax The max uvs of the Deadzone Menu Item sprite.
                 * \param pUserData An optional piece of application user data to be attached to the Deadzone Menu Item. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to Deadzone Menu Item objects.
                 * \return A Deadzone Menu Item object
                 */
                DeadZoneMenuItem(const TDeadZoneMenuItemId id
                          , const Space::LatLongAltitude& latLongAlt
                          , const std::string& p_FileName
                          , Eegeo::Helpers::ICallback0& p_OnClickedEvent
                          , const Eegeo::v2& p_Dimension
                          , const Eegeo::v2& p_uvMin = Eegeo::v2::Zero()
                          , const Eegeo::v2& p_uvMax = Eegeo::v2::One()
                          , const void* pUserData = NULL);
                
                /*! Get the unique identifier for the DeadZoneMenuItem.
                 * \return The DeadZoneMenuItem's unique identifier.
                 */
                TDeadZoneMenuItemId GetId() const;
                
                /*! Get the application supplied user data for the DeadZoneMenuItem.
                 * \return The DeadZoneMenuItem's application supplied user data.
                 */
                const void* GetUserData() const;
                
                /*! Get the ECEF position of the DeadZoneMenuItem.
                 * \return The DeadZoneMenuItem's position.
                 */
                const dv3 GetEcefPosition() const;
                
                /*! Get the color tint of the DeadZoneMenuItem. The X,Y,Z, and W components refer to Red, Green, Blue and Alpha values between 0 and 1.
                 * \return The color vector applied to the DeadZoneMenuItem.
                 */
                const v4& GetColor() const;
                
                /*! Get the File name of the DeadZoneMenuItem icon.
                 * \return The DeadZoneMenuItem's icon file name.
                 */
                const std::string& GetFileName() const;
                
                /*! Get the Dimensions of the DeadZoneMenuItem icon.
                 * \return The DeadZoneMenuItem's dimensions.
                 */
                const v2& GetDimensions() const;
                
                /*! Get the min UVs of the DeadZoneMenuItem icon.
                 * \return The DeadZoneMenuItem's min UVs.
                 */
                const v2& GetUVMin() const;
                
                /*! Get the max UVs of the DeadZoneMenuItem icon.
                 * \return The DeadZoneMenuItem's max UVs.
                 */
                const v2& GetUVMax() const;
                
                Eegeo::Helpers::ICallback0& GetCallback() const;
                
            private:
                TDeadZoneMenuItemId m_id;
                Space::LatLongAltitude m_latLongAlt;
                const void* const m_pUserData;
                
                v4 m_color;
                const std::string m_FileName;
                const Eegeo::v2 m_Dimension;
                const Eegeo::v2 m_uvMin;
                const Eegeo::v2 m_uvMax;
                Eegeo::Helpers::ICallback0& m_OnClickedEvent;
            };
        }
    }
}
