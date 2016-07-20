// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once


namespace Eegeo
{
    namespace UI
    {
        namespace Animations
        {
            class IAnimationsObservable
            {
            public:
                virtual void AddAnimation(IAnimation* pAnimationToAdd) = 0;
                virtual void RemoveAnimation(IAnimation* pAnimationToRemove) = 0;
                virtual void RemoveAnimationsForTag(int tag) = 0;
                virtual void ClearAllAnimations() = 0;
                virtual ~IAnimationsObservable() {}
            };
        }
    }
}