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
    , m_floorAnimationCallback(this, &JumpPointsSwitcher::FloorAnimationStateChanged)
    , m_currentLocation("")
    , m_isInInterior(false)
    , m_currentSelectedFloor(0)
    , m_delay(0.f)
    , m_shouldSwitch(false)
    {
        m_interiorsExplorerModule.RegisterVisibilityChangedCallback(m_interiorVisibilityChangedCallback);
        m_interiorsExplorerModule.RegisterInteriorAnimationCallback(m_floorAnimationCallback);
    }

    JumpPointsSwitcher::~JumpPointsSwitcher()
    {
        m_interiorsExplorerModule.UnregisterVisibilityChangedCallback(m_interiorVisibilityChangedCallback);
        m_interiorsExplorerModule.UnregisterInteriorAnimationCallback(m_floorAnimationCallback);
    }

    void JumpPointsSwitcher::Update(float dt)
    {
        if (m_shouldSwitch)
        {
            if (m_delay <= 0.f)
            {
                m_shouldSwitch = false;
                m_jumpPointRepository.RemoveAllJumpPoints();

                for (TJumpPointsDataVector::const_iterator it = m_jumpPoints.begin(); it != m_jumpPoints.end(); ++it)
                {
                    (*it)->SetVisibilityStatus(true);
                    m_jumpPointRepository.AddJumpPoint(*it);
                }
            }
            else
            {
                m_delay -= dt;
            }
        }
    }

    void JumpPointsSwitcher::SwitchJumpPoints(const TJumpPointsDataVector& jumpPoints, float delay)
    {
        m_delay = delay;
        m_shouldSwitch = true;
        m_jumpPoints = jumpPoints;
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
            else
            {
                m_jumpPointRepository.RemoveAllJumpPoints();
            }
        }
    }

    void JumpPointsSwitcher::ReloadJumpPoints()
    {
        if (m_interiorsExplorerModule.IsInteriorVisible())
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
        }
        else
        {
            TExteriorJumpPointsData::const_iterator it = m_exteriorJumpPoints.find(m_currentLocation);

            if (it != m_exteriorJumpPoints.end())
            {
                SwitchJumpPoints(m_exteriorJumpPoints.at(m_currentLocation));
            }
            else
            {
                m_jumpPointRepository.RemoveAllJumpPoints();
            }

            m_isInInterior = false;
            
        }
    }

    void JumpPointsSwitcher::MapStateChanged()
    {
        if(m_interiorsExplorerModule.GetSelectedFloor()<0)
        {
            m_isInInterior = false;
            TExteriorJumpPointsData::const_iterator it = m_exteriorJumpPoints.find(m_currentLocation);

            if (it != m_exteriorJumpPoints.end())
            {
                SwitchJumpPoints(m_exteriorJumpPoints.at(m_currentLocation));
            }
            else
                m_jumpPointRepository.RemoveAllJumpPoints();

            return;
        }
        
        if (m_interiorsExplorerModule.IsInteriorVisible())
        {
            if (!m_isInInterior)
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

    void JumpPointsSwitcher::FloorAnimationStateChanged(InteriorsExplorer::InteriorsExplorerFloorAnimationState& state)
    {
        switch (state)
        {
            case InteriorsExplorer::InteriorsExplorerFloorAnimationState::AnimationStarted:
                m_jumpPointRepository.RemoveAllJumpPoints();
                break;

            case InteriorsExplorer::InteriorsExplorerFloorAnimationState::AnimationEnded:
                ReloadJumpPoints();
                break;

            default:
                ReloadJumpPoints();
                break;
        }
    }
}
