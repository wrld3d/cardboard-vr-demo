// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__OVRCameraSplineExampleFactory__
#define __ExampleApp__OVRCameraSplineExampleFactory__

#include "IExampleFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
    class OVRCameraSplineExampleFactory : public IExampleFactory
    {
        Eegeo::EegeoWorld& m_world;
        const IScreenPropertiesProvider& m_screenPropertiesProvider;
        
    public:
        OVRCameraSplineExampleFactory(Eegeo::EegeoWorld& world,
                                   const IScreenPropertiesProvider& screenPropertiesProvider);
        
        std::string ExampleName() const;
        
        IExample* CreateExample() const;
    };
}


#endif /* defined(__ExampleApp__OVRCameraSplineExampleFactory__) */
