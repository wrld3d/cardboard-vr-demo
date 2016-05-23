// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__AndroidVRHeadTracker__
#define __ExampleApp__AndroidVRHeadTracker__

#include <jni.h>
#include "AndroidNativeState.h"
#include "IVRHeadTracker.h"

namespace Examples
{
    class AndroidVRHeadTracker : public IVRHeadTracker
    {
        AndroidNativeState& m_nativeState;
        
    public:
        
        AndroidVRHeadTracker(AndroidNativeState& nativeState);
        virtual void ResetTracker() ;
    };
}


#endif /* defined(__ExampleApp__AndroidVRHeadTracker__) */
