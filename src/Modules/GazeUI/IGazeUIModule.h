// Copyright eeGeo Ltd (2012-2015), All Rights Reserved



namespace Eegeo
{
    namespace GazeUI
    {
        class IGazeUIModule
        {
            public:
                virtual ~IGazeUIModule() {}
                virtual void Update(float dt) = 0;
        };
    }
}