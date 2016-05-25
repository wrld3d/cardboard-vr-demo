// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "VectorMath.h"

namespace Eegeo
{
    namespace GazeUI
    {
        class IGazeUIView
        {
            
        public:
            
            virtual void UpdateGazeProgress(int progress) = 0;
            virtual void ShowView() = 0;
            virtual void HideView() = 0;
            virtual void SetCenterPoint(float x, float y) = 0;
            
            
        };
    }
}