// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__VRCameraSplineExampleFactory__
#define __ExampleApp__VRCameraSplineExampleFactory__

#include "IExampleFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
    class VRCameraSplineExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
        
    public:
        VRCameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                      DefaultCameraControllerFactory& defaultCameraControllerFactory,
                                      const IScreenPropertiesProvider& screenPropertiesProvider);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__VRCameraSplineExampleFactory__) */
