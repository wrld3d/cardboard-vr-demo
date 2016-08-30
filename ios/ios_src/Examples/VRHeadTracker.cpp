// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VRHeadTracker.h"

namespace Examples
{
    VRHeadTracker::VRHeadTracker()
    {
        m_pcardBoardHeadTracker = Eegeo_NEW(CardboardSDK::HeadTracker)();
        m_pcardBoardHeadTracker->startTracking([UIApplication sharedApplication].statusBarOrientation);

    
    }
    VRHeadTracker::~VRHeadTracker()
    {
        m_pcardBoardHeadTracker->stopTracking();
        Eegeo_DELETE m_pcardBoardHeadTracker;
    }
    void VRHeadTracker::ResetTracker()
    {
    
    }
    void VRHeadTracker::HeadViewValue(float value[])
    {
        GLKMatrix4 lastViewValue = m_pcardBoardHeadTracker->lastHeadView();
        for (int i=0; i<16; i++)
        {
            value[i] = lastViewValue.m[i];
        }
        
    }
    
}