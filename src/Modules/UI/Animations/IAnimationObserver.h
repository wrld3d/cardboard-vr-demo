// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once


namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class IAnimationObserver
            {
                
            public:
                
                virtual void OnAnimationAdded(IAnimation& animation) = 0;
                virtual void OnAnimationProgress(IAnimation& animation) = 0;
                virtual void OnAnimationRemoved(IAnimation& animation) = 0;
                
                virtual ~IAnimationObserver() {}
            };
        }
    }
}