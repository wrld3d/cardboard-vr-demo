//
//  DeadZoneMenu.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

#include "DeadZoneMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuItem::DeadZoneMenuItem(const TDeadZoneMenuItemId id
                                 , const Space::LatLongAltitude& latLongAlt
                                 , const std::string& p_FileName
                                 , Eegeo::Helpers::ICallback0& p_OnClickedEvent
                                 , const Eegeo::v2& p_Dimension
                                 , const Eegeo::v2& p_uvMin
                                 , const Eegeo::v2& p_uvMax
                                 , const void* pUserData)
            : m_id(id)
            , m_latLongAlt(latLongAlt)
            , m_FileName(p_FileName)
            , m_OnClickedEvent(p_OnClickedEvent)
            , m_Dimension(p_Dimension)
            , m_uvMin(p_uvMin)
            , m_uvMax(p_uvMax)
            , m_pUserData(pUserData)
            {
                m_color = Eegeo::v4::One();
            }
            
            TDeadZoneMenuItemId DeadZoneMenuItem::GetId() const
            {
                return m_id;
            }
            
            const void* DeadZoneMenuItem::GetUserData() const
            {
                return m_pUserData;
            }
            
            const dv3 DeadZoneMenuItem::GetEcefPosition() const
            {
                return m_latLongAlt.ToECEF();
            }
            
            const v4& DeadZoneMenuItem::GetColor() const
            {
                return m_color;
            }
            
            const std::string& DeadZoneMenuItem::GetFileName() const
            {
                return m_FileName;
            }

            const v2& DeadZoneMenuItem::GetDimensions() const
            {
                return m_Dimension;
            }
            
            const v2& DeadZoneMenuItem::GetUVMin() const
            {
                return m_uvMin;
            }
            
            const v2& DeadZoneMenuItem::GetUVMax() const
            {
                return m_uvMax;
            }
            
            Eegeo::Helpers::ICallback0& DeadZoneMenuItem::GetCallback() const
            {
                return m_OnClickedEvent;
            }
        }
    }
}