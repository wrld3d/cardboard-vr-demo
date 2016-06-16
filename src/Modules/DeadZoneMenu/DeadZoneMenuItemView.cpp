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
                                                       , IUIRenderableFilter& p_UIRenderableFilter
                                                       , UIQuad* quad
                                                       , IUICameraProvider& p_UICameraProvider
                                                       , Eegeo::v2& dimension
                                                       )
            : m_DeadZoneMenuItem(deadZoneMenuItem)
            , m_UICameraProvider(p_UICameraProvider)
            , UIImageButton(p_UIRenderableFilter
                            , quad
                            , deadZoneMenuItem.GetCallback()
                            , dimension)
            {}
            
        }
    }
}
