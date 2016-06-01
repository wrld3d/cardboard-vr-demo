//
//  UIInteractionController.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#include <algorithm>
#include "CameraHelpers.h"
#include "IntersectionTests.h"
#include "UIInteractionController.h"
#include "../../Examples/VRCameraSpline/VRCameraController.h"
#include "../UIGaze/IUIGazeView.h"
#include "VectorMath.h"

#define PICKED_COLOUR Eegeo::v4(1.0f, 1.0f, 0.0f, 0.5f)

namespace Eegeo
{
    namespace UI
    {
        
        bool UIInteractionController::IsScreenPointInsideModel(const Eegeo::v2& screenPoint, IUIInteractableItem* uiItem)
        {
            Eegeo::Camera::RenderCamera* renderCamera = m_pCameraProvider.GetRenderCameraForUI();
            
            if (renderCamera->GetEcefLocation().SquareDistanceTo(uiItem->GetItemEcefPosition()) < (uiItem->GetItemRadius() * uiItem->GetItemRadius())) {
                //Camera is within item's radius
                return false;
            }
            
            Eegeo::dv3 rayOrigin = renderCamera->GetEcefLocation();
            Eegeo::dv3 rayDirection;
            
            Eegeo::Camera::CameraHelpers::GetScreenPickRay(*renderCamera, screenPoint.GetX(), screenPoint.GetY(), rayDirection);
            
            return Eegeo::Geometry::IntersectionTests::TestRaySphere(rayOrigin, rayDirection, uiItem->GetItemEcefPosition(), uiItem->GetItemRadius());
        }
        
        UIInteractionController::UIInteractionController(IUICameraProvider& p_CameraProvider, UIGaze::UIGazeView& UIGazeView):
        m_pCameraProvider(p_CameraProvider),
        m_InteractableItems(),
        m_UIGazeView(UIGazeView)
        {
            m_FocusedUIItemId = -1;
        }
        
        UIInteractionController::~UIInteractionController()
        {
            m_InteractableItems.clear();
        }
        
        void UIInteractionController::Update(float dt)
        {
            if(m_FocusedUIItemId>=0)
                m_GazedTime += dt;
            
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                m_InteractableItems[i]->Update(dt);
            }
        }
        
        void UIInteractionController::Event_ScreenInteractionStart(const Eegeo::v2& point)
        {
            m_FocusedUIItemId = -1;
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    m_InteractableItems[i]->SetItemHasFocus(true);
                    m_FocusedUIItemId = i;
                }
            }
        }
        
        void UIInteractionController::Event_ScreenInteractionMoved(const Eegeo::v2& point)
        {
            int touchedItemId = -1;
            for (int i = 0; i != m_InteractableItems.size(); i++)
            {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i]))
                {
                    touchedItemId = i;
                    m_InteractableItems[i]->SetItemHasFocus(true);
                }
                else
                {
                    m_InteractableItems[i]->SetItemHasFocus(false);
                }
            }
            
            if(m_FocusedUIItemId!=-1 && touchedItemId==-1)
            {
                m_GazedTime = 0.0f;
                m_UIGazeView.HideView();
                // end
            }
            else if(m_FocusedUIItemId!=-1 && touchedItemId!=-1 && m_FocusedUIItemId==touchedItemId)
            {
                if(m_GazedTime>=2.f)
                {
                    touchedItemId = -1;
                    m_GazedTime = 0.0f;
                    m_UIGazeView.HideView();
                    
                    Event_ScreenInteractionClick(point);
                    
                }
                // same continued
            }
            else if(m_FocusedUIItemId!=-1 && touchedItemId!=-1 && m_FocusedUIItemId!=touchedItemId)
            {
                m_GazedTime = 0.0f;
                m_UIGazeView.ResetProgress();
                // new item focused
            }
            else if(m_FocusedUIItemId==-1 && touchedItemId!=-1)
            {
                m_GazedTime = 0.0f;
                m_UIGazeView.ShowView();
                // start
            }
            
            m_FocusedUIItemId = touchedItemId;
            
        }
        
        void UIInteractionController::Event_ScreenInteractionEnd(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    m_InteractableItems[i]->SetItemHasFocus(false);
                }
            }
        }
        
        void UIInteractionController::Event_ScreenInteractionClick(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    m_InteractableItems[i]->OnItemClicked();
                }
            }
        }
        
        const IUIInteractableItem* UIInteractionController::GetItemAtScreenPoint(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    return m_InteractableItems[i];
                }
            }
            
            return NULL;
        }
        
        void UIInteractionController::RegisterInteractableItem(IUIInteractableItem* interactableItem)
        {
            m_InteractableItems.push_back(interactableItem);
        }
        
        void UIInteractionController::UnRegisterInteractableItem(IUIInteractableItem* interactableItem)
        {
            std::vector<IUIInteractableItem*>::iterator position = std::find(m_InteractableItems.begin(), m_InteractableItems.end(), interactableItem);
            if (position != m_InteractableItems.end())
                m_InteractableItems.erase(position);
        }
    }
}


