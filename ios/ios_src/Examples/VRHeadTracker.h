
// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "HeadTracker.h"
#include "IVRHeadTracker.h"

namespace Examples
{
    class VRHeadTracker : public IVRHeadTracker
    {
    public:
        VRHeadTracker();
        ~VRHeadTracker();
        void ResetTracker();
        void HeadViewValue(float value[]);
        void UpdatedCardboardProfile(float profileValue[]);

    private:
        CardboardSDK::HeadTracker *m_pcardBoardHeadTracker;
    };
}
