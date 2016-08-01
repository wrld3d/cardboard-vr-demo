// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldMenuItemViewFactory.h"
#include "RegularTexturePageLayout.h"
#include "WorldMenuItemView.h"
#include "WorldMenuItem.h"
#include "VectorMath.h"

using namespace Eegeo::UI;
namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            
            WorldMenuItemViewFactory::WorldMenuItemViewFactory(IUIRenderableFilter& uiRenderableFilter
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
            
            WorldMenuItemViewFactory::~WorldMenuItemViewFactory(){}
            
            WorldMenuItemView* WorldMenuItemViewFactory::CreateViewForWorldMenuItem(WorldMenuItem& menuItemModel)
            {
                
                Eegeo::Geometry::Bounds2D bounds = m_pIconsTexturePageLayout->GetTileUVBounds(menuItemModel.GetSpriteId());
                WorldMenuItemView* pMenuItemView = Eegeo_NEW(WorldMenuItemView)(menuItemModel
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
}
