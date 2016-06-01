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
                                         , UIQuad* quad
                                         , IUICameraProvider& p_UICameraProvider
                                         )
            : m_JumpPoint(jumpPoint)
            , m_UICameraProvider(p_UICameraProvider)
            , m_JumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , UIImageButton(
                            quad
                            , jumpPoint.GetDimensions()
                            , jumpPoint.GetEcefPosition()
                            , m_JumpPointClickCallback
                            )
            {}
            
            void JumpPointView::MoveCameraToJumpPoint()
            {
                m_UICameraProvider.GetRenderCameraForUI()->SetEcefLocation(m_JumpPoint.GetEcefPosition());
            }
            
        }
    }
}
