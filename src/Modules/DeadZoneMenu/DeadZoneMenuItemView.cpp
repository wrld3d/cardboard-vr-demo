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
                                                       , IUIRenderableFilter& uiRenderableFilter
                                                       , UIQuad* pQuad
                                                       , IUICameraProvider& uiCameraProvider
                                                       , Eegeo::v2& dimension
                                                       )
            : m_deadZoneMenuItem(deadZoneMenuItem)
            , m_uiCameraProvider(uiCameraProvider)
            , UIImageButton(uiRenderableFilter
                            , pQuad
                            , deadZoneMenuItem.GetCallback()
                            , dimension)
            {}
            
        }
    }
}
