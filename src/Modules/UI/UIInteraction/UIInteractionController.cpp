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
            
        }
        
        void UIInteractionController::Event_ScreenInteractionStart(const Eegeo::v2& point)
        {
            m_FocusedUIItemId = -1;
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (m_InteractableItems[i]->IsCollidingWithPoint(point, m_pCameraProvider)) {
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
                if (m_InteractableItems[i]->IsCollidingWithPoint(point, m_pCameraProvider))
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
                if (m_InteractableItems[i]->IsCollidingWithPoint(point, m_pCameraProvider)) {
                    m_InteractableItems[i]->SetItemHasFocus(false);
                }
            }
        }
        
        void UIInteractionController::Event_ScreenInteractionClick(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (m_InteractableItems[i]->IsCollidingWithPoint(point, m_pCameraProvider)) {
                    m_InteractableItems[i]->OnItemClicked();
                }
            }
        }
        
        const IUIInteractableItem* UIInteractionController::GetItemAtScreenPoint(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (m_InteractableItems[i]->IsCollidingWithPoint(point, m_pCameraProvider)) {
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


