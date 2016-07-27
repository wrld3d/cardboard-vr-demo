// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointsSwitcher.h"
#include "Logger.h"

namespace Examples
{
    JumpPointsSwitcher::JumpPointsSwitcher(Eegeo::UI::JumpPoints::JumpPointRepository& jumpPointRepository,
                       InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                       const TExteriorJumpPointsData& exteriorJumpPoints,
                       const TInteriorJumpPointsData& interiorJumpPoints)
    : m_jumpPointRepository(jumpPointRepository)
    , m_interiorsExplorerModule(interiorsExplorerModule)
    , m_exteriorJumpPoints(exteriorJumpPoints)
    , m_interiorJumpPoints(interiorJumpPoints)
    , m_interiorVisibilityChangedCallback(this, &JumpPointsSwitcher::MapStateChanged)
    , m_isInInterior(false)
    {
        m_interiorsExplorerModule.RegisterVisibilityChangedCallback(m_interiorVisibilityChangedCallback);
    }

    JumpPointsSwitcher::~JumpPointsSwitcher()
    {
        m_interiorsExplorerModule.UnregisterVisibilityChangedCallback(m_interiorVisibilityChangedCallback);
    }

    void JumpPointsSwitcher::SwitchJumpPoints(const TJumpPointsDataVector& jumpPoints)
    {
        m_jumpPointRepository.RemoveAllJumpPoints();

        for (TJumpPointsDataVector::const_iterator it = jumpPoints.begin(); it != jumpPoints.end(); ++it) {
            m_jumpPointRepository.AddJumpPoint(*it);
        }
    }

    void JumpPointsSwitcher::SwitchLocation(const std::string &location)
    {
        if (m_currentLocation != location)
        {
            m_currentLocation = location;
            TExteriorJumpPointsData::const_iterator it = m_exteriorJumpPoints.find(m_currentLocation);

            if (it != m_exteriorJumpPoints.end())
            {
                SwitchJumpPoints(m_exteriorJumpPoints.at(m_currentLocation));
            }
        }
    }

    void JumpPointsSwitcher::MapStateChanged()
    {
        if(m_interiorsExplorerModule.GetSelectedFloor()<0)
        {
            m_jumpPointRepository.RemoveAllJumpPoints();
            return;
        }
        
        if (m_interiorsExplorerModule.IsInteriorVisible())
        {
            if (!m_isInInterior || m_interiorsExplorerModule.GetSelectedFloor() != m_currentSelectedFloor)
            {
                const std::string& interiorID = m_interiorsExplorerModule.GetSelectedInteriorID();
                TInteriorJumpPointsData::const_iterator itInterior = m_interiorJumpPoints.find(interiorID);
                if (itInterior != m_interiorJumpPoints.end())
                {
                    const TInteriorFloorJumpPointsData& currnetInteriorData = itInterior->second;
                    m_currentSelectedFloor = m_interiorsExplorerModule.GetSelectedFloor();
                    TInteriorFloorJumpPointsData::const_iterator itFloorData = currnetInteriorData.find(m_currentSelectedFloor);

                    if (itFloorData != currnetInteriorData.end())
                    {
                        SwitchJumpPoints(itFloorData->second);
                    }
                    else
                    {
                        m_jumpPointRepository.RemoveAllJumpPoints();
                    }
                }

                m_isInInterior = true;
            }
        }
        else
        {
            if (m_isInInterior)
            {
                TExteriorJumpPointsData::const_iterator it = m_exteriorJumpPoints.find(m_currentLocation);

                if (it != m_exteriorJumpPoints.end())
                {
                    SwitchJumpPoints(m_exteriorJumpPoints.at(m_currentLocation));
                }

                m_isInInterior = false;
            }
        }
    }
}
