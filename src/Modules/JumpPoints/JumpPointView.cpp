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
                                         , const std::string& fileName
                                         , const Eegeo::v2& p_Dimension
                                         , const Eegeo::v2& p_uvMin
                                         , const Eegeo::v2& p_uvMax
                                         ) :
            m_JumpPoint(jumpPoint)
            , m_UICameraProvider(p_UICameraProvider)
            , m_JumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , UIImageButton(p_RenderingModule
                            , p_PlatformAbstractionModule
                            , fileName
                            , jumpPoint.GetEcefPosition()
                            , p_Dimension
                            , m_JumpPointClickCallback
                            , p_uvMin
                            , p_uvMax
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
