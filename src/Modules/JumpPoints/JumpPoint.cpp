// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "JumpPoint.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            
            JumpPoint::JumpPoint(const TJumpPointId id
                                 , const Space::LatLongAltitude& latLongAlt
                                 , const std::string& fileName
                                 , const Eegeo::v2& dimension
                                 , const Eegeo::v2& uvMin
                                 , const Eegeo::v2& uvMax
                                 , const bool isInInterior
                                 , const void* pUserData)
            : m_id(id)
            , m_latLongAlt(latLongAlt)
            , m_ecefPosition(latLongAlt.ToECEF())
            , m_fileName(fileName)
            , m_dimension(dimension)
            , m_uvMin(uvMin)
            , m_uvMax(uvMax)
            , m_isInInterior(isInInterior)
            , m_interiorFloor(0)
            , m_pUserData(pUserData)
            , m_visiblityStatus(true)
            {
                m_color = Eegeo::v4::One();
            }
            
            TJumpPointId JumpPoint::GetId() const
            {
                return m_id;
            }
            
            const void* JumpPoint::GetUserData() const
            {
                return m_pUserData;
            }
            
            const dv3& JumpPoint::GetEcefPosition() const
            {
                return m_ecefPosition;
            }
            
            void JumpPoint::SetEcefPosition(const dv3& ecefPosition)
            {
                m_ecefPosition = ecefPosition;
            }
            
            const std::string& JumpPoint::GetFileName() const
            {
                return m_fileName;
            }

            const v2& JumpPoint::GetDimensions() const
            {
                return m_dimension;
            }
            
            const v2& JumpPoint::GetUVMin() const
            {
                return m_uvMin;
            }
            
            const v2& JumpPoint::GetUVMax() const
            {
                return m_uvMax;
            }
            
            const bool JumpPoint::GetIsInInterior() const
            {
                return m_isInInterior;
            }
            
            const int JumpPoint::GetInteriorFloor() const
            {
                return m_interiorFloor;
            }
            
            void JumpPoint::SetInteriorFloor(int floor)
            {
                m_interiorFloor = floor;
            }

            void JumpPoint::SetVisibilityStatus(bool isVisible)
            {
                m_visiblityStatus = isVisible;
            }

            bool JumpPoint::GetVisibility() const
            {
                return m_visiblityStatus;
            }

            void JumpPoint::SetChildJumpPoints(const TJumpPoints& childJumpPoints)
            {
                m_childJumpPoints = childJumpPoints;
            }

            const TJumpPointsVector& JumpPoint::GetChildJumpPoints() const
            {
                return m_childJumpPoints;
            }
        }
    }
}
