
// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once
#include "IVRHeadTracker.h"
namespace Examples
{
    class VRHeadTracker : public IVRHeadTracker
    {
    public:
        VRHeadTracker();
        ~VRHeadTracker();
        void ResetTracker();
    };
}
