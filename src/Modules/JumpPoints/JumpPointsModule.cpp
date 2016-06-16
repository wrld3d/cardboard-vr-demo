// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointsModule.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            JumpPointsModule::JumpPointsModule(IUIRenderableFilter& p_UIRenderableFilter
                                               , IUIQuadFactory& p_IUIQuadFactory
                                               , IUIInteractionObservable& p_IUIInteractionObservable
                                               , IUICameraProvider& p_UICameraProvider
                                               )
            {
                m_pViewFactory = new JumpPointViewFactory(p_UIRenderableFilter
                                                          , p_IUIQuadFactory
                                                          , p_UICameraProvider);
                m_pRepository = new JumpPointRepository();
                m_pController = new JumpPointController(*m_pRepository, *m_pViewFactory, p_IUIInteractionObservable);
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
