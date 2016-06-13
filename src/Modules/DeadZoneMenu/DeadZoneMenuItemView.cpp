//
//  DeadZoneMenuItemView.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

#include "DeadZoneMenuItemView.h"
#include "DeadZoneMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuItemView::DeadZoneMenuItemView(DeadZoneMenuItem& deadZoneMenuItem
                                                       , UIQuad* quad
                                                       , IUICameraProvider& p_UICameraProvider
                                                       )
            : m_DeadZoneMenuItem(deadZoneMenuItem)
            , m_UICameraProvider(p_UICameraProvider)
            , UIImageButton(quad
                            , deadZoneMenuItem.GetCallback()
                            , deadZoneMenuItem.GetDimensions()
                            , deadZoneMenuItem.GetEcefPosition())
            {}
            
        }
    }
}
