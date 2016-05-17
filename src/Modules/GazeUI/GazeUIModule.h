// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "IGazeUIModule.h"
#include "IGazeUIView.h"

namespace Eegeo
{
    namespace GazeUI
    {
        class GazeUIModule : public IGazeUIModule
        {
            
        private:
            IGazeUIView& m_pGazeUIView;
            int m_pGazeProgress;
            
        public:
            
            GazeUIModule(IGazeUIView& gazeUIView);
            void Update(float dt);
            
            IGazeUIView& getGazeUIView(){ return m_pGazeUIView; }
            
        };
    }
}