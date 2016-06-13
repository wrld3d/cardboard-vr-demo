// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuItemViewFactory.h"
#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuItemViewFactory::DeadZoneMenuItemViewFactory(IUIQuadFactory& p_IUIQuadFactory
                                                                     , IUICameraProvider& p_UICameraProvider)
            : m_IUIQuadFactory(p_IUIQuadFactory)
            , m_UICameraProvider(p_UICameraProvider)
            {
                
            }
            
            DeadZoneMenuItemViewFactory::~DeadZoneMenuItemViewFactory()
            {
                
            }
            
            DeadZoneMenuItemView* DeadZoneMenuItemViewFactory::CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& menuItemModel)
            {
                DeadZoneMenuItemView* menuItemView = Eegeo_NEW(DeadZoneMenuItemView)(menuItemModel
                                                                        , m_IUIQuadFactory.CreateUIQuad(menuItemModel.GetFileName()
                                                                                                        , menuItemModel.GetDimensions()
                                                                                                        , menuItemModel.GetUVMin()
                                                                                                        , menuItemModel.GetUVMax()
                                                                                                        , menuItemModel.GetEcefPosition()
                                                                                                        , menuItemModel.GetColor())
                                                                        , m_UICameraProvider
                                                                        );
                return menuItemView;
            }
            
        }
    }
}
