// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "LayerIds.h"
#include "Bounds.h"
#include "InteriorMenu.h"
#include "IInteriorMenuItemViewFactory.h"
#include "IUIQuadFactory.h"
#include "../../UI/UIProgressBarConfig.h"
#include "../../UI/IUIRenderableFilter.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        class InteriorMenuItemViewFactory : protected Eegeo::NonCopyable, public IInteriorMenuItemViewFactory
        {
        public:
            InteriorMenuItemViewFactory(Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                        , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                                        , const std::string& spriteFileName
                                        , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                        , int numberOfTilesAlong1Axis
                                        );
            
            ~InteriorMenuItemViewFactory();
            
            virtual InteriorMenuItemView* CreateViewForInteriorMenuItem(InteriorMenuItem& menuItemModel);
            
        private:
            Eegeo::UI::IUIRenderableFilter& m_uiRenderableFilter;
            Eegeo::UI::IUIQuadFactory& m_uiQuadFactory;
            std::string m_spriteFileName;
            const Eegeo::UI::UIProgressBarConfig& m_progressBarConfig;
            Eegeo::v2 m_itemDimension;
            Eegeo::Rendering::ITexturePageLayout* m_pIconsTexturePageLayout;
        };
    }
}
