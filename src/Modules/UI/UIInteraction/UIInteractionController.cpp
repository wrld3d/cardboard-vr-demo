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
        
        
        UIInteractionController::UIInteractionController(IUICameraProvider& cameraProvider, UIGaze::UIGazeView& uiGazeView):
        m_cameraProvider(cameraProvider),
        m_interactableItems(),
        m_uiGazeView(uiGazeView)
        {
            m_focusedUIItemId = -1;
        }
        
        UIInteractionController::~UIInteractionController()
        {
            m_interactableItems.clear();
        }
        
        void UIInteractionController::Update(float dt)
        {
            if(m_focusedUIItemId>=0)
                m_gazedTime += dt;
            
        }
        
        void UIInteractionController::Event_ScreenInteractionStart(const Eegeo::v2& point)
        {
            m_focusedUIItemId = -1;
            for (int i = 0; i != m_interactableItems.size(); i++) {
                if (m_interactableItems[i]->IsCollidingWithPoint(point, m_cameraProvider)) {
                    m_interactableItems[i]->SetItemHasFocus(true);
                    m_focusedUIItemId = i;
                }
            }
        }
        
        void UIInteractionController::Event_ScreenInteractionMoved(const Eegeo::v2& point)
        {
            int touchedItemId = -1;
            for (int i = 0; i != m_interactableItems.size(); i++)
            {
                if (m_interactableItems[i]->IsCollidingWithPoint(point, m_cameraProvider))
                {
                    touchedItemId = i;
                    m_interactableItems[i]->SetItemHasFocus(true);
                }
                else
                {
                    m_interactableItems[i]->SetItemHasFocus(false);
                }
            }
            
            if(m_focusedUIItemId!=-1 && touchedItemId==-1)
            {
                m_gazedTime = 0.0f;
                m_uiGazeView.HideView();
                // end
            }
            else if(m_focusedUIItemId!=-1 && touchedItemId!=-1 && m_focusedUIItemId==touchedItemId)
            {
                if(m_gazedTime>=2.f)
                {
                    touchedItemId = -1;
                    m_gazedTime = 0.0f;
                    m_uiGazeView.HideView();
                    
                    Event_ScreenInteractionClick(point);
                    
                }
                // same continued
            }
            else if(m_focusedUIItemId!=-1 && touchedItemId!=-1 && m_focusedUIItemId!=touchedItemId)
            {
                m_gazedTime = 0.0f;
                m_uiGazeView.ResetProgress();
                // new item focused
            }
            else if(m_focusedUIItemId==-1 && touchedItemId!=-1)
            {
                m_gazedTime = 0.0f;
                m_uiGazeView.ShowView();
                // start
            }
            
            m_focusedUIItemId = touchedItemId;
            
        }
        
        void UIInteractionController::Event_ScreenInteractionEnd(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_interactableItems.size(); i++) {
                if (m_interactableItems[i]->IsCollidingWithPoint(point, m_cameraProvider)) {
                    m_interactableItems[i]->SetItemHasFocus(false);
                }
            }
        }
        
        void UIInteractionController::Event_ScreenInteractionClick(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_interactableItems.size(); i++) {
                if (m_interactableItems[i]->IsCollidingWithPoint(point, m_cameraProvider)) {
                    m_interactableItems[i]->OnItemClicked();
                }
            }
        }
        
        const IUIInteractableItem* UIInteractionController::GetItemAtScreenPoint(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_interactableItems.size(); i++) {
                if (m_interactableItems[i]->IsCollidingWithPoint(point, m_cameraProvider)) {
                    return m_interactableItems[i];
                }
            }
            
            return NULL;
        }
        
        void UIInteractionController::RegisterInteractableItem(IUIInteractableItem* pInteractableItem)
        {
            m_interactableItems.push_back(pInteractableItem);
        }
        
        void UIInteractionController::UnRegisterInteractableItem(IUIInteractableItem* pInteractableItem)
        {
            std::vector<IUIInteractableItem*>::iterator position = std::find(m_interactableItems.begin(), m_interactableItems.end(), pInteractableItem);
            if (position != m_interactableItems.end())
                m_interactableItems.erase(position);
        }
    }
}


