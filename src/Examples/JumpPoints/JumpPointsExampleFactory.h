// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__JumpPointsExampleFactory__
#define __ExampleApp__JumpPointsExampleFactory__

#include "IExampleFactory.h"
#include "Modules/UI/UIInteraction/UIInteractionController.h"
#include "Modules/UI/IUICameraProvider.h"
#include "Modules/UI/UIQuad/IUIQuadFactory.h"
#include "EegeoRootDeclarations.h"
#include "ScreenPropertiesProvider.h"

namespace Examples
{
class JumpPointsExampleFactory : public IExampleFactory
{
    Eegeo::UI::IUIQuadFactory& m_UIQuadFactory;
    Eegeo::UI::IUIInteractionObservable& m_UIInteractionObservable;
    Eegeo::UI::IUICameraProvider& m_UICameraProvider;
    
    
    Eegeo::EegeoWorld& m_world;
    const IScreenPropertiesProvider& m_screenPropertiesProvider;
    DefaultCameraControllerFactory& m_defaultCameraControllerFactory;
    
public:
    JumpPointsExampleFactory(Eegeo::EegeoWorld& world,
                             DefaultCameraControllerFactory& defaultCameraControllerFactory,
                             const IScreenPropertiesProvider& screenPropertiesProvider,
                             Eegeo::UI::IUIQuadFactory& quadFactory,
                             Eegeo::UI::IUIInteractionObservable& uIInteractionObservable,
                             Eegeo::UI::IUICameraProvider& uICameraProvider);

	std::string ExampleName() const;

	IExample* CreateExample() const;
};
}

#endif /* defined(__ExampleApp__JumpPointsExampleFactory__) */
