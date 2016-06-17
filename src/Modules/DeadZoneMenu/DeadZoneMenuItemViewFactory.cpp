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
            
            DeadZoneMenuItemViewFactory::DeadZoneMenuItemViewFactory(IUIRenderableFilter& uiRenderableFilter
                                                                     , IUIQuadFactory& uiQuadFactory
                                                                     , IUICameraProvider& uiCameraProvider
                                                                     , std::string& spriteFileName
                                                                     , int numberOfTilesAlong1Axis)
            : m_uiRenderableFilter(uiRenderableFilter)
            , m_uiQuadFactory(uiQuadFactory)
            , m_uiCameraProvider(uiCameraProvider)
            , m_numberOfTilesAlong1Axis(numberOfTilesAlong1Axis)
            {
                m_spriteFileName = std::string(spriteFileName);
                m_itemDimension = Eegeo::v2(50,50);
                m_pIconsTexturePageLayout = Eegeo_NEW(Eegeo::Rendering::RegularTexturePageLayout)(numberOfTilesAlong1Axis);
            }
            
            DeadZoneMenuItemViewFactory::~DeadZoneMenuItemViewFactory()
            {
                
            }
            
            DeadZoneMenuItemView* DeadZoneMenuItemViewFactory::CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& menuItemModel)
            {
                
                Eegeo::Geometry::Bounds2D bounds = m_pIconsTexturePageLayout->GetTileUVBounds(menuItemModel.GetSpriteId());
                DeadZoneMenuItemView* pMenuItemView = Eegeo_NEW(DeadZoneMenuItemView)(menuItemModel
                                                                          , m_uiRenderableFilter
                                                                        , m_uiQuadFactory.CreateUIQuad( m_spriteFileName.c_str()
                                                                                                        , m_itemDimension
                                                                                                        , bounds.min
                                                                                                        , bounds.max)
                                                                                     , m_uiCameraProvider
                                                                                     , m_itemDimension
                                                                        );
                return pMenuItemView;
            }
            
        }
    }
}
