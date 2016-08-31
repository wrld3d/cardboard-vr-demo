// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__IVRHeadTracker__
#define __ExampleApp__IVRHeadTracker__
#include "Logger.h"

namespace Examples
{
    class IVRHeadTracker
    {
    public:
        virtual ~IVRHeadTracker(){}
        virtual void ResetTracker() = 0;
        virtual void HeadViewValue(float value[]) = 0;
        virtual void UpdatedCardboardProfile(float profileValue[]) = 0;


    };
}


#endif /* defined(__ExampleApp__IVRHeadTracker__) */
