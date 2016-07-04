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
                                                       , const UIProgressBarConfig& progressBarConfig)
            : m_uiRenderableFilter(uiRenderableFilter)
            , m_uiQuadFactory(uiQuadFactory)
            , m_uiCameraProvider(uiCameraProvider)
            , m_interiorsExplorerModule(interiorsExplorerModule)
            , m_progressBarConfig(progressBarConfig)
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
                                                                        );
                return pJumpPointView;
            }
            
        }
    }
}
