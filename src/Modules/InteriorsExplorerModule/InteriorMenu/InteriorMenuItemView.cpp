// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "RenderingModule.h"
#include "InteriorMenuItemView.h"
#include "InteriorMenuItem.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        
        InteriorMenuItemView::InteriorMenuItemView(InteriorMenuItem& InteriorMenuItem
                                                   , Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                                   , Eegeo::UI::IUIQuadFactory& quadFactory
                                                   , const std::string& assetPath
                                                   , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                                   , Eegeo::v2& dimension
                                                   , Eegeo::v2& uvMin
                                                   , Eegeo::v2& uvMax
                                                   )
        : InteriorMenuUIButton(uiRenderableFilter
                           , quadFactory
                           , assetPath
                           , progressBarConfig
                           , dimension
                           , Eegeo::v3::One()
                           , Eegeo::v3::One()
                           , Eegeo::v4::One()
                           , uvMin
                           , uvMax)
        ,m_InteriorMenuItem(InteriorMenuItem)
        {}
        
        bool InteriorMenuItemView::IsCollidingWithPoint(const Eegeo::v2& screenPoint, Eegeo::UI::IUICameraProvider& cameraProvider)
        {
            
            if(!m_pSprite->GetItemShouldRender())
                return false;
            
            Eegeo::Camera::RenderCamera& renderCamera = cameraProvider.GetRenderCameraForUI();
            if (renderCamera.GetEcefLocation().SquareDistanceTo(m_pSprite->GetEcefPosition()) < (GetItemRadius() * GetItemRadius()))
            {
                return false;
            }
            
            Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
            Eegeo::dv3 rayDirection;
            
            Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPoint.GetX(), screenPoint.GetY(), rayDirection);
            return Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, m_pSprite->GetEcefPosition(), GetItemRadius());
        }
        
        void InteriorMenuItemView::OnItemClicked()
        {
            m_InteriorMenuItem.GetCallback()(m_InteriorMenuItem);
        }
        
        
    }
}
