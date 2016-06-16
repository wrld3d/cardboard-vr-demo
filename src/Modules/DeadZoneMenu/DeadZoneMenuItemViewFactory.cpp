// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuItemViewFactory.h"
#include "RegularTexturePageLayout.h"
#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuItemViewFactory::DeadZoneMenuItemViewFactory(IUIRenderableFilter& p_UIRenderableFilter
                                                                     , IUIQuadFactory& p_IUIQuadFactory
                                                                     , IUICameraProvider& p_UICameraProvider
                                                                     , std::string& spriteFileName
                                                                     , int numberOfTilesAlong1Axis)
            : m_UIRenderableFilter(p_UIRenderableFilter)
            , m_IUIQuadFactory(p_IUIQuadFactory)
            , m_UICameraProvider(p_UICameraProvider)
            , m_NumberOfTilesAlong1Axis(numberOfTilesAlong1Axis)
            {
                m_SpriteFileName = std::string(spriteFileName);
                p_ItemDimension = Eegeo::v2(50,50);
                m_pIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlong1Axis);
            }
            
            DeadZoneMenuItemViewFactory::~DeadZoneMenuItemViewFactory()
            {
                
            }
            
            DeadZoneMenuItemView* DeadZoneMenuItemViewFactory::CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& menuItemModel)
            {
                
                Eegeo::Geometry::Bounds2D bounds = m_pIconsTexturePageLayout->GetTileUVBounds(menuItemModel.GetSpriteId());
                DeadZoneMenuItemView* menuItemView = Eegeo_NEW(DeadZoneMenuItemView)(menuItemModel
                                                                          , m_UIRenderableFilter
                                                                        , m_IUIQuadFactory.CreateUIQuad( m_SpriteFileName.c_str()
                                                                                                        , p_ItemDimension
                                                                                                        , bounds.min
                                                                                                        , bounds.max)
                                                                                     , m_UICameraProvider
                                                                                     , p_ItemDimension
                                                                        );
                return menuItemView;
            }
            
        }
    }
}
