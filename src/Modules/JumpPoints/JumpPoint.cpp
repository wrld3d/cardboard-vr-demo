//
//  JumpPoint.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

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
                                 , const void* pUserData)
            : m_id(id)
            , m_latLongAlt(latLongAlt)
            , m_ecefPosition(latLongAlt.ToECEF())
            , m_fileName(fileName)
            , m_dimension(dimension)
            , m_uvMin(uvMin)
            , m_uvMax(uvMax)
            , m_pUserData(pUserData)
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
            
            const v4& JumpPoint::GetColor() const
            {
                return m_color;
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
        }
    }
}