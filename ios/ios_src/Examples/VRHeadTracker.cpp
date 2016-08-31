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
        m_pCardBoardHeadTracker = Eegeo_NEW(CardboardSDK::HeadTracker)();
        m_pCardBoardHeadTracker->startTracking([UIApplication sharedApplication].statusBarOrientation);
    }
    
    VRHeadTracker::~VRHeadTracker()
    {
        m_pCardBoardHeadTracker->stopTracking();
        Eegeo_DELETE m_pCardBoardHeadTracker;
    }
    
    void VRHeadTracker::ResetTracker()
    {
    
    }
    
    void VRHeadTracker::HeadViewValue(float value[])
    {
        GLKMatrix4 lastViewValue = m_pCardBoardHeadTracker->lastHeadView();
        for (int i=0; i<16; i++)
        {
            value[i] = lastViewValue.m[i];
        }
        
    }
    
    void VRHeadTracker::UpdatedCardboardProfile(float profileValue[])
    {
        CardboardSDK::HeadMountedDisplay *pHMDManager = Eegeo_NEW(CardboardSDK::HeadMountedDisplay)([UIScreen mainScreen]);
        CardboardSDK::ScreenParams *pScreenParams = pHMDManager->getScreen();
        CardboardSDK::CardboardDeviceParams *pCardboardDeviceParams = pHMDManager->getCardboard();
        
        CardboardSDK::FieldOfView *pFov = pCardboardDeviceParams->maximumLeftEyeFOV();
        CardboardSDK::Distortion  *pDistCoef = pCardboardDeviceParams->distortion();
        profileValue[0] = pFov->left();
        profileValue[1] = pFov->top();
        profileValue[2] = pFov->right();
        profileValue[3] = pFov->bottom();
        profileValue[4] = pScreenParams->widthInMeters();
        profileValue[5] = pScreenParams->heightInMeters();
        profileValue[6] = pScreenParams->borderSizeInMeters();
        profileValue[7] = pCardboardDeviceParams->interLensDistance();
        profileValue[8] = pCardboardDeviceParams->verticalDistanceToLensCenter();
        profileValue[9] = pCardboardDeviceParams->screenToLensDistance();
        profileValue[10] = -1;
        profileValue[11] = pDistCoef->coefficients()[0];
        profileValue[12] = pDistCoef->coefficients()[1];

        Eegeo_DELETE pHMDManager;
    }
}