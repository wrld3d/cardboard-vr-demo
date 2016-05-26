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
                                         , Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                                         , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                                         , IUICameraProvider& p_UICameraProvider
                                         )
            : m_JumpPoint(jumpPoint)
            , m_UICameraProvider(p_UICameraProvider)
            , m_JumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , UIImageButton(p_RenderingModule
                            , p_PlatformAbstractionModule
                            , jumpPoint.GetFileName()
                            , jumpPoint.GetEcefPosition()
                            , jumpPoint.GetDimensions()
                            , m_JumpPointClickCallback
                            , jumpPoint.GetUVMin()
                            , jumpPoint.GetUVMax()
                            , jumpPoint.GetColor()
                            )
            {}
            
            void JumpPointView::MoveCameraToJumpPoint()
            {
                m_UICameraProvider.GetRenderCameraForUI()->SetEcefLocation(m_JumpPoint.GetEcefPosition());
            }
            
        }
    }
}
