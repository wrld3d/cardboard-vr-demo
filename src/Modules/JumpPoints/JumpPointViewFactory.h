// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IJumpPointViewFactory.h"
#include "LayerIds.h"
#include "JumpPoint.h"
#include "Bounds.h"
#include "JumpPointView.h"
#include "IUIQuadFactory.h"
#include "IInteriorsExplorerModule.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            class JumpPointViewFactory : protected Eegeo::NonCopyable, public IJumpPointViewFactory
            {
            public:
                JumpPointViewFactory(IUIRenderableFilter& p_UIRenderableFilter
                                     , IUIQuadFactory& p_IUIQuadFactory
                                     , IUICameraProvider& p_UICameraProvider
                                     , const UIProgressBarConfig& progressBarConfig
                                     , Eegeo::Helpers::ICallback1<JumpPoint&>& onJumpPointSelected);
                
                ~JumpPointViewFactory();
                
                virtual JumpPointView* CreateViewForJumpPoint(JumpPoint& jumpPointModel);
                
            private:
                IUICameraProvider& m_uiCameraProvider;
                IUIQuadFactory& m_uiQuadFactory;
                IUIRenderableFilter& m_uiRenderableFilter;
                const UIProgressBarConfig& m_progressBarConfig;
                Eegeo::Helpers::ICallback1<JumpPoint&>& m_onJumpPointSelected;
            };
        }
    }
}
