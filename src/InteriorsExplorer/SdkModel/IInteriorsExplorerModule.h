// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "InteriorsExplorer.h"
#include "GlobeCamera.h"

    namespace InteriorsExplorer
    {
        namespace SdkModel
        {
            class IInteriorsExplorerModule
            {
            public:
                virtual ~IInteriorsExplorerModule() { }

                virtual InteriorVisibilityUpdater& GetInteriorVisibilityUpdater() const = 0;
                
                virtual Eegeo::Resources::Interiors::InteriorsCameraController& GetInteriorsCameraController() const = 0;
                
                virtual void Update(float dt) const = 0;
                
                virtual InteriorsExplorerModel& GetInteriorsExplorerModel() const = 0;
                
                virtual Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& GetTouchController() const = 0;
                
            };
        }
}