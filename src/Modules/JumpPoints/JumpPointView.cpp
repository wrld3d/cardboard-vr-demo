//
//  JumpPoint.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

#include "JumpPoint.h"
#include "JumpPointView.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            JumpPointView::JumpPointView(JumpPoint& jumpPoint
                                         , IUIRenderableFilter& uiRenderableFilter
                                         , UIQuad* pQuad
                                         , IUICameraProvider& uiCameraProvider
                                         )
            : m_jumpPoint(jumpPoint)
            , m_uiCameraProvider(uiCameraProvider)
            , m_jumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , UIImageButton(uiRenderableFilter
                            , pQuad
                            , m_jumpPointClickCallback
                            , jumpPoint.GetDimensions()
                            , jumpPoint.GetEcefPosition())
            {}
            
            void JumpPointView::MoveCameraToJumpPoint()
            {
                m_uiCameraProvider.GetRenderCameraForUI().SetEcefLocation(m_jumpPoint.GetEcefPosition());
            }
            
        }
    }
}
