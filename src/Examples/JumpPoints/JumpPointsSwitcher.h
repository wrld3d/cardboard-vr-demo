// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <map>

#include "ICallback.h"
#include "Types.h"
#include "JumpPoint.h"
#include "JumpPointRepository.h"
#include "IInteriorsExplorerModule.h"

namespace Examples
{
    typedef std::vector<Eegeo::UI::JumpPoints::JumpPoint*> TJumpPointsDataVector;
    typedef std::map<std::string,TJumpPointsDataVector> TExteriorJumpPointsData;
    typedef std::map<int,TJumpPointsDataVector> TInteriorFloorJumpPointsData;
    typedef std::map<std::string,TInteriorFloorJumpPointsData> TInteriorJumpPointsData;

    class JumpPointsSwitcher: private Eegeo::NonCopyable
    {
    private:
        Eegeo::UI::JumpPoints::JumpPointRepository& m_jumpPointRepository;
        InteriorsExplorer::IInteriorsExplorerModule& m_interiorsExplorerModule;

        Eegeo::Helpers::TCallback0<JumpPointsSwitcher> m_interiorVisibilityChangedCallback;
        Eegeo::Helpers::TCallback1<JumpPointsSwitcher, InteriorsExplorer::InteriorsExplorerFloorAnimationState> m_floorAnimationCallback;

        const TExteriorJumpPointsData& m_exteriorJumpPoints;
        const TInteriorJumpPointsData& m_interiorJumpPoints;

        std::string m_currentLocation;
        bool m_isInInterior;
        int m_currentSelectedFloor;

        float m_delay;
        bool m_shouldSwitch;
        TJumpPointsDataVector m_jumpPoints;

    public:
        JumpPointsSwitcher(Eegeo::UI::JumpPoints::JumpPointRepository& jumpPointRepository,
                           InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule,
                           const TExteriorJumpPointsData& exteriorJumpPoints,
                           const TInteriorJumpPointsData& interiorJumpPoints);
        ~JumpPointsSwitcher();

        void SwitchJumpPoints(const TJumpPointsDataVector& jumpPoints, float delay = 0.f);
        void SwitchLocation(const std::string& location);

        void Update(float dt);

        void ReloadJumpPoints();

        //Callback for Interiors
        void MapStateChanged();

        void FloorAnimationStateChanged(InteriorsExplorer::InteriorsExplorerFloorAnimationState& state);
    };
}