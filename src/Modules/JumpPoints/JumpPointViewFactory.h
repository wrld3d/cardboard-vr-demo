// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IJumpPointViewFactory.h"
#include "LayerIds.h"
#include "JumpPoint.h"
#include "Bounds.h"
#include "JumpPointView.h"
#include "IUIQuadFactory.h"

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
                                     , IUICameraProvider& p_UICameraProvider);
                
                ~JumpPointViewFactory();
                
                virtual JumpPointView* CreateViewForJumpPoint(JumpPoint& jumpPointModel);
                
            private:
                IUICameraProvider& m_uiCameraProvider;
                IUIQuadFactory& m_uiQuadFactory;
                IUIRenderableFilter& m_uiRenderableFilter;
            };
        }
    }
}
