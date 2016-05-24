// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "JumpPoints.h"
#include "VectorMath.h"
#include "LatLongAltitude.h"

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
                 * \param pUserData An optional piece of application user data to be attached to the Jump Point. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to Jump Point objects.
                 * \return A Jump Point object
                 */
                JumpPoint(const TJumpPointId id, const Space::LatLongAltitude& latLongAlt, const void* pUserData = NULL);
                
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
                
            private:
                TJumpPointId m_id;
                Space::LatLongAltitude m_latLongAlt;
                const void* const m_pUserData;
                
                v4 m_color;
                
            };
        }
    }
}
