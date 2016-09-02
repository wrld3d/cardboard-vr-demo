
// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IVRHeadTracker.h"
#include "CardboardSDKService.h"
namespace Examples
{
    class VRHeadTracker : public IVRHeadTracker
    {
    public:
        VRHeadTracker(Examples::CardboardSDKService &cardboardService);
        ~VRHeadTracker();
        void ResetTracker();
    private:
        Examples::CardboardSDKService &m_cardboardService;
    };
}
