// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorer.h"
#include "GlobeCamera.h"
#include "string"
#include "ICallback.h"
#include "InteriorMenuItem.h"

namespace InteriorsExplorer
{
    class IInteriorsExplorerModule
    {
    public:
        virtual ~IInteriorsExplorerModule() { }

        virtual bool InteriorLoaded() = 0;

        virtual void ForceEnterInterior(int floorId) = 0;
        virtual void ForceLeaveInterior() = 0;
        
        virtual void SelectFloor(int floor) = 0;
        virtual int GetSelectedFloor() const = 0;
        virtual void Update(float dt) const = 0;

        virtual void ShowInteriors() = 0;
        virtual void HideInteriors() = 0;
        virtual bool IsInteriorVisible() = 0;

        virtual void SelectInterior(std::string interiorID) = 0;
        virtual std::string GetSelectedInteriorID() const = 0;

        virtual void RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;
        virtual void UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback0& callback) = 0;

        virtual void RegisterMenuItemGazedCallback(Eegeo::Helpers::ICallback1<InteriorMenu::InteriorMenuItem&>& callback) = 0;
        virtual void UnregisterMenuItemGazedCallback(Eegeo::Helpers::ICallback1<InteriorMenu::InteriorMenuItem&>& callback) = 0;
    };
}