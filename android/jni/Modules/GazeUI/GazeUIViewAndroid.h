// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef GAZEUIVIEWANDROID_H_
#define GAZEUIVIEWANDROID_H_

#include "IGazeUIView.h"
#include "AndroidNativeState.h"

namespace Eegeo {
    namespace GazeUI{
        class GazeUIViewAndroid : public IGazeUIView, private Eegeo::NonCopyable
        {
            
            AndroidNativeState& m_nativeState;
            jclass m_androidGazeUIClass;
            jobject m_androidGazeUIView;
            
        private:
            
        public:
            GazeUIViewAndroid(AndroidNativeState& m_nativeState);
            ~GazeUIViewAndroid();

            void CreateNativeUI();
            
            void UpdateGazeProgress(int progress);
            void ShowView();
            void HideView();
        };

    }
}
#endif
