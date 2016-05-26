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
                                 , const std::string& p_FileName
                                 , const Eegeo::v2& p_Dimension
                                 , const Eegeo::v2& p_uvMin
                                 , const Eegeo::v2& p_uvMax
                                 , const void* pUserData)
            : m_id(id)
            , m_latLongAlt(latLongAlt)
            , m_FileName(p_FileName)
            , m_Dimension(p_Dimension)
            , m_uvMin(p_uvMin)
            , m_uvMax(p_uvMax)
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
            
            const dv3 JumpPoint::GetEcefPosition() const
            {
                return m_latLongAlt.ToECEF();
            }
            
            const v4& JumpPoint::GetColor() const
            {
                return m_color;
            }
            
            const std::string& JumpPoint::GetFileName() const
            {
                return m_FileName;
            }

            const v2& JumpPoint::GetDimensions() const
            {
                return m_Dimension;
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