// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

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
                                                       , Eegeo::UI::IUIQuadFactory& quadFactory
                                                       , const std::string& assetPath
                                                       , const UIProgressBarConfig& progressBarConfig
                                                       , Eegeo::v2& dimension
                                                       , Eegeo::v2& uvMin
                                                       , Eegeo::v2& uvMax
                                                       )
            : m_deadZoneMenuItem(deadZoneMenuItem)
            , UIProgressButton(uiRenderableFilter
                            , quadFactory
                            , assetPath
                            , progressBarConfig
                            , deadZoneMenuItem.GetCallback()
                            , dimension
                            , Eegeo::v3::One()
                            , Eegeo::v3::One()
                            , Eegeo::v4::One()
                            , uvMin
                            , uvMax)
            {}
            
        }
    }
}
