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
            typedef std::vector<JumpPoint*> TJumpPointsVector;

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
                 * \param isInInterior The Jump Point exists in interior or not.
                 * \param pUserData An optional piece of application user data to be attached to the Jump Point. N.B. It is the application's responsibility to manage the lifetime of any user data it attaches to Jump Point objects.
                 * \return A Jump Point object
                 */
                JumpPoint(const TJumpPointId id
                          , const Space::LatLongAltitude& latLongAlt
                          , const std::string& fileName
                          , const Eegeo::v2& dimension
                          , const Eegeo::v2& uvMin = Eegeo::v2::Zero()
                          , const Eegeo::v2& uvMax = Eegeo::v2::One()
                          , const bool isInInterior = false
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
                const dv3& GetEcefPosition() const;
                
                /*! Set the ECEF position of the JumpPoint.
                 */
                void SetEcefPosition(const dv3& ecefPosition);
                
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
                
                /*! Get is JumpPoint is in interior.
                 * \return The if JumpPoint's is in interior.
                 */
                const bool GetIsInInterior() const;
                
                /*! Get the interior floor for jump point.
                 * \return The interior floor.
                 */
                const int GetInteriorFloor() const;
                
                /*! Set the interior floor for jump point.
                 */
                void SetInteriorFloor(int floor);

                /*! Set the jump point visiblity status.
                 */
                void SetVisibilityStatus(bool isVisible);

                /*! Get JumpPoint visibility status.
                 * \return True if JumpPoint's is visible.
                 */
                bool GetVisibility() const;

                /*! Set the JumpPoint's children.
                 */
                void SetChildJumpPoints(const TJumpPointsVector& childJumpPoint);

                /*! Get JumpPoint's children.
                 * \return JumpPoint's children.
                 */
                const TJumpPointsVector& GetChildJumpPoints() const;
                
            private:
                TJumpPointId m_id;
                Space::LatLongAltitude m_latLongAlt;
                dv3 m_ecefPosition;
                const void* const m_pUserData;
                
                v4 m_color;
                const std::string m_fileName;
                const Eegeo::v2 m_dimension;
                const Eegeo::v2 m_uvMin;
                const Eegeo::v2 m_uvMax;
                const bool m_isInInterior;
                int m_interiorFloor;
                bool m_visiblityStatus;

                typedef std::vector<JumpPoint*> TJumpPoints;
                TJumpPoints m_childJumpPoints;
            };
        }
    }
}
