//
//  GazeUIViewiOS.h
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

#ifndef GazeUIViewiOS_h
#define GazeUIViewiOS_h

#include "../../src/Modules/GazeUI/IGazeUIView.h"

namespace Eegeo {
    namespace GazeUI{
        class GazeUIViewiOS : public IGazeUIView, private Eegeo::NonCopyable
        {
        public:
            GazeUIViewiOS(){}
            ~GazeUIViewiOS(){}
            
            void CreateNativeUI(){}
            
            void UpdateGazeProgress(int progress){}
            void ShowView(){}
            void HideView(){}
        };
        
    }
}

#endif /* GazeUIViewiOS_h */
