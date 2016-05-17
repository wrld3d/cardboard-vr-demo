// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "GazeUIModule.h"

namespace Eegeo
{
    namespace GazeUI
    {
        
        GazeUIModule::GazeUIModule(IGazeUIView& gazeUIView)
        :m_pGazeUIView(gazeUIView)
        {
            m_pGazeProgress = 0;
        }
        
        void GazeUIModule::Update(float dt){
            m_pGazeProgress +=1;
            m_pGazeUIView.UpdateGazeProgress(m_pGazeProgress);
        }
        
        
    }
}