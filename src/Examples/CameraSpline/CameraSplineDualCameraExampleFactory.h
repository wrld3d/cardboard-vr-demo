// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__CameraSplineDualCameraExampleFactory__
#define __ExampleApp__CameraSplineDualCameraExampleFactory__

#include "IExampleFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
    class CameraSplineDualCameraExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        
    public:
        CameraSplineDualCameraExampleFactory(Eegeo::EegeoWorld& world,
                                   const IScreenPropertiesProvider& screenPropertiesProvider);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__CameraSplineDualCameraExampleFactory__) */
