// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRHeadTracker.h"

namespace Examples
{
    VRHeadTracker::VRHeadTracker(Examples::CardboardSDKService &cardboardService):m_cardboardService(cardboardService)
    {
    }
    
    VRHeadTracker::~VRHeadTracker()
    {
    }
    void VRHeadTracker::ResetTracker()
    {
        m_cardboardService.GetHeadTracker().stopTracking();
        m_cardboardService.GetHeadTracker().stopTracking();
    }
}