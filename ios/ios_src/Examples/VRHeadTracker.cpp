// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "Distortion.h"
#include "FieldOfView.h"
#include "ScreenParams.h"
#include "VRHeadTracker.h"
#include "HeadMountedDisplay.h"
#include "CardboardDeviceParams.h"

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
    
    void VRHeadTracker::UpdatedCardboardProfile(float profileValue[])
    {
        CardboardSDK::HeadMountedDisplay *hMDManager = Eegeo_NEW(CardboardSDK::HeadMountedDisplay)([UIScreen mainScreen]);
        CardboardSDK::ScreenParams *screenParams = hMDManager->getScreen();
        CardboardSDK::CardboardDeviceParams *cardboardDeviceParams = hMDManager->getCardboard();
        
        CardboardSDK::FieldOfView *fov = cardboardDeviceParams->maximumLeftEyeFOV();
        CardboardSDK::Distortion  *distCoef = cardboardDeviceParams->distortion();
        profileValue[0] = fov->left();
        profileValue[1] = fov->top();
        profileValue[2] = fov->right();
        profileValue[3] = fov->bottom();
        profileValue[4] = screenParams->widthInMeters();
        profileValue[5] = screenParams->widthInMeters();
        profileValue[6] = screenParams->borderSizeInMeters();
        profileValue[7] = cardboardDeviceParams->interLensDistance();
        profileValue[8] = cardboardDeviceParams->verticalDistanceToLensCenter();
        profileValue[9] = cardboardDeviceParams->screenToLensDistance();
        profileValue[10] = 1;
        profileValue[11] = distCoef->coefficients()[0];
        profileValue[12] = distCoef->coefficients()[1];
        profileValue[13] = fov->left();
        profileValue[14] = fov->left();
        profileValue[15] = fov->left();
        
        
    }
    
}