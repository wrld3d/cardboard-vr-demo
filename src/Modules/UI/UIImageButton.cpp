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
        UIImageButton::UIImageButton(UIQuad* quad
                                     , Eegeo::Helpers::ICallback0& onClickedEvent
                                     , Eegeo::v2 size
                                     , Eegeo::dv3 ecefPosition
                                     , Eegeo::v3 scale
                                     , Eegeo::v4 color
                                     , int spriteId
                                     , Eegeo::v2 spriteGridSize)
        : UISprite(quad, size, ecefPosition, scale, color, spriteId, spriteGridSize)
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
