// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "JumpPoints.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"
#include "string"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            /*!
             * \brief Defines the data model for a Jump point placed in the 3D world.
             *
             *  JumpPoint defines a Jump Point placed in the 3D world.
             *
             */
            class JumpPoint : protected Eegeo::NonCopyable
            {
            public:
                /*! Create a Jump Point object at a particular position in the world.
                 * \param id A unique identifier for the Jump Point.
                 * \param latLongAlt The position of the Jump Point.
                 * \param p_FileName The name texture file to load icon from.
                 * \param p_Dimension The dimensions of the Jump Point.
                 * \param p_uvMin The min uvs of the Jump Point sprite.
                 * \param p_uvMax The max uvs of the Jump Point sprite.
                 * \param pUserData An optional piece of application user data to be attached to the Jump Point. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to Jump Point objects.
                 * \return A Jump Point object
                 */
                JumpPoint(const TJumpPointId id
                          , const Space::LatLongAltitude& latLongAlt
                          , const std::string& p_FileName
                          , const Eegeo::v2& p_Dimension
                          , const Eegeo::v2& p_uvMin = Eegeo::v2::Zero()
                          , const Eegeo::v2& p_uvMax = Eegeo::v2::One()
                          , const void* pUserData = NULL);
                
                /*! Get the unique identifier for the JumpPoint.
                 * \return The JumpPoint's unique identifier.
                 */
                TJumpPointId GetId() const;
                
                /*! Get the application supplied user data for the JumpPoint.
                 * \return The JumpPoint's application supplied user data.
                 */
                const void* GetUserData() const;
                
                /*! Get the ECEF position of the JumpPoint.
                 * \return The JumpPoint's position.
                 */
                const dv3 GetEcefPosition() const;
                
                /*! Get the color tint of the JumpPoint. The X,Y,Z, and W components refer to Red, Green, Blue and Alpha values between 0 and 1.
                 * \return The color vector applied to the JumpPoint.
                 */
                const v4& GetColor() const;
                
                /*! Get the File name of the JumpPoint icon.
                 * \return The JumpPoint's icon file name.
                 */
                const std::string& GetFileName() const;
                
                /*! Get the Dimensions of the JumpPoint icon.
                 * \return The JumpPoint's dimensions.
                 */
                const v2& GetDimensions() const;
                
                /*! Get the min UVs of the JumpPoint icon.
                 * \return The JumpPoint's min UVs.
                 */
                const v2& GetUVMin() const;
                
                /*! Get the max UVs of the JumpPoint icon.
                 * \return The JumpPoint's max UVs.
                 */
                const v2& GetUVMax() const;
                
            private:
                TJumpPointId m_id;
                Space::LatLongAltitude m_latLongAlt;
                const void* const m_pUserData;
                
                v4 m_color;
                const std::string m_FileName;
                const Eegeo::v2 m_Dimension;
                const Eegeo::v2 m_uvMin;
                const Eegeo::v2 m_uvMax;
            };
        }
    }
}
