// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorMenuItemViewFactory.h"
#include "RegularTexturePageLayout.h"
#include "InteriorMenuItemView.h"
#include "InteriorMenuItem.h"
#include "VectorMath.h"

using namespace Eegeo::UI;
namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        
        InteriorMenuItemViewFactory::InteriorMenuItemViewFactory(IUIRenderableFilter& uiRenderableFilter
                                                                 , IUIQuadFactory& uiQuadFactory
                                                                 , const std::string& spriteFileName
                                                                 , const UIProgressBarConfig& progressBarConfig
                                                                 , int numberOfTilesAlong1Axis)
        : m_uiRenderableFilter(uiRenderableFilter)
        , m_uiQuadFactory(uiQuadFactory)
        , m_progressBarConfig(progressBarConfig)
        {
            m_spriteFileName = std::string(spriteFileName);
            m_itemDimension = Eegeo::v2(50,50);
            m_pIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlong1Axis);
        }
        
        InteriorMenuItemViewFactory::~InteriorMenuItemViewFactory(){}
        
        InteriorMenuItemView* InteriorMenuItemViewFactory::CreateViewForInteriorMenuItem(InteriorMenuItem& menuItemModel)
        {
            
            Eegeo::Geometry::Bounds2D bounds = m_pIconsTexturePageLayout->GetTileUVBounds(menuItemModel.GetSpriteId());
            InteriorMenuItemView* pMenuItemView = Eegeo_NEW(InteriorMenuItemView)(menuItemModel
                                                                                  , m_uiRenderableFilter
                                                                                  , m_uiQuadFactory
                                                                                  , m_spriteFileName.c_str()
                                                                                  , m_progressBarConfig
                                                                                  , m_itemDimension
                                                                                  , bounds.min
                                                                                  , bounds.max
                                                                                  );
            return pMenuItemView;
        }
        
    }
}
