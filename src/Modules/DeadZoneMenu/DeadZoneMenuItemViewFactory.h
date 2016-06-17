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
                DeadZoneMenuItemViewFactory(IUIRenderableFilter& uiRenderableFilter
                                            , IUIQuadFactory& uiQuadFactory
                                            , IUICameraProvider& uiCameraProvider
                                            , std::string& spriteFileName
                                            , int numberOfTilesAlong1Axis
                                            );
                
                ~DeadZoneMenuItemViewFactory();
                
                virtual DeadZoneMenuItemView* CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& menuItemModel);
                
            private:
                IUIRenderableFilter& m_uiRenderableFilter;
                IUICameraProvider& m_uiCameraProvider;
                IUIQuadFactory& m_uiQuadFactory;
                std::string m_spriteFileName;
                int m_numberOfTilesAlong1Axis;
                Eegeo::v2 m_itemDimension;
                Eegeo::Rendering::ITexturePageLayout* m_pIconsTexturePageLayout;
            };
        }
    }
}
