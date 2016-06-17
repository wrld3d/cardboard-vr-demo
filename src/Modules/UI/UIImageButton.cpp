//
//  UIImageButton.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "UIImageButton.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        UIImageButton::UIImageButton(IUIRenderableFilter& p_UIRenderableFilter
                                     , UIQuad* quad
                                     , Eegeo::Helpers::ICallback0& onClickedEvent
                                     , const Eegeo::v2& size
                                     , const Eegeo::dv3& ecefPosition
                                     , const Eegeo::v3& scale
                                     , const Eegeo::v4& color)
        : UISprite(p_UIRenderableFilter, quad, size, ecefPosition, scale, color)
        , m_OnClickedEvent(onClickedEvent)
        {
            m_Radius = (size.x > size.y ? size.x : size.y)/2.0f;
        }
        
        UIImageButton::~UIImageButton(){
        }
        
        bool UIImageButton::IsCollidingWithPoint(const Eegeo::v2& screenPoint, IUICameraProvider& cameraProvider)
        {
            Eegeo::Camera::RenderCamera& renderCamera = cameraProvider.GetRenderCameraForUI();
            
            if (renderCamera.GetEcefLocation().SquareDistanceTo(GetEcefPosition()) < (GetItemRadius() * GetItemRadius())) {
                return false;
            }
            
            Eegeo::dv3 rayOrigin = renderCamera.GetEcefLocation();
            Eegeo::dv3 rayDirection;
            
            Eegeo::Camera::CameraHelpers::GetScreenPickRay(renderCamera, screenPoint.GetX(), screenPoint.GetY(), rayDirection);
            return Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, GetEcefPosition(), GetItemRadius());
        }
        
        void UIImageButton::OnItemClicked()
        {
            m_OnClickedEvent();
        }
        
        void UIImageButton::OnFocusGained()
        {
            SetScale(Eegeo::v3::One() * 1.1f);
        }
        
        void UIImageButton::OnFocusLost()
        {
            SetScale(Eegeo::v3::One());
        }
        
    }
}
