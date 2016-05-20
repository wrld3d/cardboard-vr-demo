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
            
            JumpPoint::JumpPoint(const TJumpPointId id, const Space::LatLongAltitude& latLongAlt, const void* pUserData) : m_id(id)
            , m_latLongAlt(latLongAlt)
            , m_pUserData(pUserData)
            {
                UpdateEcefPosition();
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
                return m_ecefLocation;
            }
            
            const v4& JumpPoint::GetColor() const
            {
                return m_color;
            }
            
            void JumpPoint::UpdateEcefPosition()
            {
                m_ecefLocation = m_latLongAlt.ToECEF();
            }
        }
    }
}