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
                DeadZoneMenuItemViewFactory(IUIRenderableFilter& p_UIRenderableFilter
                                            , IUIQuadFactory& p_IUIQuadFactory
                                            , IUICameraProvider& p_UICameraProvider
                                            , std::string& spriteFileName
                                            , int numberOfTilesAlong1Axis
                                            );
                
                ~DeadZoneMenuItemViewFactory();
                
                virtual DeadZoneMenuItemView* CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& menuItemModel);
                
            private:
                IUIRenderableFilter& m_UIRenderableFilter;
                IUICameraProvider& m_UICameraProvider;
                IUIQuadFactory& m_IUIQuadFactory;
                std::string m_SpriteFileName;
                int m_NumberOfTilesAlong1Axis;
                Eegeo::v2 p_ItemDimension;
                Eegeo::Rendering::ITexturePageLayout* m_pIconsTexturePageLayout;
            };
        }
    }
}
