// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "JumpPoint.h"
#include "JumpPointView.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModel.h"
namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            JumpPointView::JumpPointView(JumpPoint& jumpPoint
                                         , IUIRenderableFilter& uiRenderableFilter
                                         , Eegeo::UI::IUIQuadFactory& quadFactory
                                         , const UIProgressBarConfig& progressBarConfig
                                         , IUICameraProvider& uiCameraProvider
                                         , Eegeo::Helpers::ICallback1<JumpPoint&>& onJumpPointSelected
                                         )
            : m_jumpPoint(jumpPoint)
            , m_uiCameraProvider(uiCameraProvider)
            , m_jumpPointGazed(this, &JumpPointView::JumpPointGazed)
            , m_onJumpPointSelected(onJumpPointSelected)
            , UIProgressButton(uiRenderableFilter
                            , quadFactory
                            , jumpPoint.GetFileName()
                            , progressBarConfig
                            , m_jumpPointGazed
                            , jumpPoint.GetDimensions()
                            , jumpPoint.GetEcefPosition()
                            , Eegeo::v3::One()
                            , jumpPoint.GetColor()
                            , jumpPoint.GetUVMin()
                            , jumpPoint.GetUVMax()
                            )
            {
            }
            
            void JumpPointView::JumpPointGazed()
            {
                m_onJumpPointSelected(m_jumpPoint);
            }
            
        }
    }
}
