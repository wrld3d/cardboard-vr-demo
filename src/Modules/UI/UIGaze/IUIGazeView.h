// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VectorMath.h"

namespace Eegeo
{
    namespace UIGaze
    {
        class IUIGazeView
        {
            
        public:
            
            virtual void ShowView() = 0;
            virtual void HideView() = 0;
            virtual void ResetProgress() = 0;
            virtual void UpdateEcefPosition(dv3 position) = 0;
            
        };
    }
}