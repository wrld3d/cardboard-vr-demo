// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorer.h"
#include "GlobeCamera.h"

    namespace InteriorsExplorer
    {
        class IInteriorsExplorerModule
        {
        public:
            virtual ~IInteriorsExplorerModule() { }
            
            virtual bool InteriorLoaded() = 0;
            
            virtual void SelectFloor(int floor) = 0;
            virtual void Update(float dt) const = 0;
            
            virtual void ShowInteriors() = 0;
            virtual void HideInteriors() = 0;
            
            
        };
}