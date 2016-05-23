// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include <jni.h>
#include "AndroidVRHeadTracker.h"
#include "Logger.h"

namespace Examples
{
    
    AndroidVRHeadTracker::AndroidVRHeadTracker(AndroidNativeState& nativeState)
    :m_nativeState(nativeState){
    }
    
    void AndroidVRHeadTracker::ResetTracker()
    {
        
        AndroidSafeNativeThreadAttachment attached(m_nativeState);
        JNIEnv* env = attached.envForThread;
        
        jmethodID resetTrackerMethod = env->GetMethodID(m_nativeState.activityClass, "ResetTracker", "()V");
        env->CallVoidMethod(m_nativeState.activity, resetTrackerMethod);
        
    }
}


