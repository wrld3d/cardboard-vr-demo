// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class IAnimation
            {
                
            public:
                virtual void Update(float dt) = 0;
                virtual bool isComplete() = 0;
                virtual float getProgress() = 0;
                virtual float getMaxProgress() = 0;
                
                virtual ~IAnimation(){}
                
            };
        }
    }
}