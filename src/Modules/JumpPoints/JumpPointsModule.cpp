// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointsModule.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            JumpPointsModule::JumpPointsModule(IUIRenderableFilter& uiRenderableFilter
                                               , IUIQuadFactory& uiQuadFactory
                                               , IUIInteractionObservable& uiInteractionObservable
                                               , IUICameraProvider& uiCameraProvider
                                               , InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule
                                               )
            {
                m_pViewFactory = new JumpPointViewFactory(uiRenderableFilter
                                                          , uiQuadFactory
                                                          , uiCameraProvider
                                                          , interiorsExplorerModule);
                m_pRepository = new JumpPointRepository();
                m_pController = new JumpPointController(*m_pRepository, *m_pViewFactory, uiInteractionObservable);
            }
            
            JumpPointsModule::~JumpPointsModule()
            {
                Eegeo_DELETE m_pController;
                Eegeo_DELETE m_pRepository;
                Eegeo_DELETE m_pViewFactory;
            }
            
            void JumpPointsModule::Update(float dt)
            {
                m_pController->Update(dt);
            }
            
            JumpPointRepository& JumpPointsModule::GetRepository() const
            {
                return *m_pRepository;
            }
            
            JumpPointController& JumpPointsModule::GetController() const
            {
                return *m_pController;
            }
            
        }
    }
}
