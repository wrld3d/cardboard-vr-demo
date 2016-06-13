// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IDeadZoneMenuItemViewFactory.h"
#include "LayerIds.h"
#include "DeadZoneMenuItem.h"
#include "Bounds.h"
#include "DeadZoneMenuItemView.h"
#include "IUIQuadFactory.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            class DeadZoneMenuItemViewFactory : protected Eegeo::NonCopyable, public IDeadZoneMenuItemViewFactory
            {
            public:
                DeadZoneMenuItemViewFactory(IUIQuadFactory& p_IUIQuadFactory
                                            , IUICameraProvider& p_UICameraProvider);
                
                ~DeadZoneMenuItemViewFactory();
                
                virtual DeadZoneMenuItemView* CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& menuItemModel);
                
            private:
                IUICameraProvider& m_UICameraProvider;
                IUIQuadFactory& m_IUIQuadFactory;
            };
        }
    }
}
