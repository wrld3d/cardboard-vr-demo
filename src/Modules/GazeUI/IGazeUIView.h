// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



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
            
        };
    }
}