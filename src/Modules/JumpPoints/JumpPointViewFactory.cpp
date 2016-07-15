// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointViewFactory.h"
#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            
            JumpPointViewFactory::JumpPointViewFactory(IUIRenderableFilter& uiRenderableFilter
                                                       , IUIQuadFactory& uiQuadFactory
                                                       , IUICameraProvider& uiCameraProvider
                                                       , InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule
                                                       , Animations::AnimationsController& animationsController
                                                       , Animations::IDv3Animateable& animateableCamera
                                                       , const UIProgressBarConfig& progressBarConfig
                                                       , Eegeo::Helpers::ICallback1<JumpPoint&>& onJumpPointSelected)
            : m_uiRenderableFilter(uiRenderableFilter)
            , m_uiQuadFactory(uiQuadFactory)
            , m_uiCameraProvider(uiCameraProvider)
            , m_interiorsExplorerModule(interiorsExplorerModule)
            , m_animationsController(animationsController)
            , m_animateableCamera(animateableCamera)
            , m_progressBarConfig(progressBarConfig)
            , m_onJumpPointSelected(onJumpPointSelected)
            {
                
            }
            
            JumpPointViewFactory::~JumpPointViewFactory()
            {
                
            }
            
            JumpPointView* JumpPointViewFactory::CreateViewForJumpPoint(JumpPoint& jumpPointModel)
            {
                JumpPointView* pJumpPointView = Eegeo_NEW(JumpPointView)(jumpPointModel
                                                                        , m_uiRenderableFilter
                                                                        , m_uiQuadFactory
                                                                        , m_progressBarConfig
                                                                        , m_uiCameraProvider
                                                                        , m_interiorsExplorerModule
                                                                        , m_animationsController
                                                                        , m_animateableCamera
                                                                        , m_onJumpPointSelected
                                                                        );
                return pJumpPointView;
            }
            
        }
    }
}
