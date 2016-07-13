// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class IDv3Animateable
            {
            public:
                virtual void onDv3Updated(Eegeo::dv3& delta) = 0;
            };
        }
    }
}