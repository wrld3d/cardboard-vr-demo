//
//  UIInteractionModule.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#include <algorithm>

#include "UIInteractionModule.h"
#include "../../Examples/VRCameraSpline/VRCameraController.h"
#include "../UIGaze/IUIGazeView.h"
#include "VectorMath.h"

#define PICKED_COLOUR Eegeo::v4(1.0f, 1.0f, 0.0f, 0.5f)

namespace Eegeo
{
    namespace UI
    {
        void UIInteractionModule::CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray)
        {
            Eegeo::Camera::RenderCamera* renderCamera = m_pCameraProvider.GetRenderCameraForUI();
            
            //normalize the point
            float nx = 2.0f * screenPoint.GetX() / renderCamera->GetViewportWidth() - 1.f;
            float ny = - 2.0f * screenPoint.GetY() / renderCamera->GetViewportHeight() + 1.f;
            
            //prepare near and far points
            Eegeo::v4 near(nx, ny, renderCamera->GetNearClip(), 1.0f);
            Eegeo::v4 far(nx, ny, renderCamera->GetFarClip(), 1.0f);
            
            Eegeo::m44 invVP;
            Eegeo::m44::Inverse(invVP, renderCamera->GetViewProjectionMatrix());
            
            //unproject the points
            Eegeo::v4 unprojectedNear = Eegeo::v4::Mul(near, invVP);
            Eegeo::v4 unprojectedFar = Eegeo::v4::Mul(far, invVP);
            
            //convert to 3d
            Eegeo::v3 unprojectedNearWorld = unprojectedNear / unprojectedNear.GetW();
            Eegeo::v3 unprojectedFarWorld = unprojectedFar / unprojectedFar.GetW();
            
            //check intersection with a ray cast from camera position
            ray.origin = renderCamera->GetEcefLocation();
            ray.direction = (unprojectedNearWorld - unprojectedFarWorld).Norm();
        }
        
        bool UIInteractionModule::IsScreenPointInsideModel(const Eegeo::v2& screenPoint, IUIInteractableItem* uiItem)
        {
            Ray ray;
            CreateWorldSpaceRayFromScreen(screenPoint, ray);
            //            m_debugRenderer.DrawTextScreenSpace(screenPoint, "E", 100);
            ray.origin -= uiItem->GetItemEcefPosition();
            
            //the following is a standard ray sphere intersection - for other shapes, an appropriate intersection method
            //should be used
            
            double a =
            ray.direction.GetX() * ray.direction.GetX()
            + ray.direction.GetY() * ray.direction.GetY()
            + ray.direction.GetZ() * ray.direction.GetZ();
            
            double b =
            ray.direction.GetX() * (2.0 * ray.origin.GetX())
            + ray.direction.GetY() * (2.0 * ray.origin.GetY())
            + ray.direction.GetZ() * (2.0 * ray.origin.GetZ());
            
            double c =
            (ray.origin.GetX() * ray.origin.GetX()
             + ray.origin.GetY() * ray.origin.GetY()
             + ray.origin.GetZ() * ray.origin.GetZ());
            
            c -= (uiItem->GetItemRadius() * uiItem->GetItemRadius());
            
            double d = b * b + (-4.0) * a * c;
            
            //if determinant is negative sphere is in negative ray direction so can't hit
            if (d < 0.0)
            {
                return false;
            }
            
            d = sqrt(d);
            
            double t = (-0.5) * (b - d) / a;
            
            if (t >= 0.0)
            {
                return false;
            }
            
            return true;
        }
        
        UIInteractionModule::UIInteractionModule(Eegeo::EegeoWorld& world, IUICameraProvider& p_CameraProvider, UIGaze::UIGazeView& UIGazeView):
        m_pCameraProvider(p_CameraProvider),
        m_InteractableItems(),
        m_debugRenderer(world.GetDebugRenderingModule().GetDebugRenderer()),
        m_UIGazeView(UIGazeView)
        {
            m_FocusedUIItemId = -1;
        }
        
        UIInteractionModule::~UIInteractionModule()
        {
            m_InteractableItems.clear();
        }
        
        void UIInteractionModule::Update(float dt)
        {
            if(m_FocusedUIItemId>=0)
                m_GazedTime += dt;
            
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                m_InteractableItems[i]->Update(dt);
            }
        }
        
        void UIInteractionModule::Event_ScreenInteractionStart(const Eegeo::v2& point)
        {
            m_FocusedUIItemId = -1;
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    m_InteractableItems[i]->SetItemHasFocus(true);
                    m_FocusedUIItemId = i;
                }
            }
        }
        
        void UIInteractionModule::Event_ScreenInteractionMoved(const Eegeo::v2& point)
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
        
        void UIInteractionModule::Event_ScreenInteractionEnd(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    m_InteractableItems[i]->SetItemHasFocus(false);
                }
            }
        }
        
        void UIInteractionModule::Event_ScreenInteractionClick(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    m_InteractableItems[i]->OnItemClicked();
                }
            }
        }
        
        const IUIInteractableItem* UIInteractionModule::GetItemAtScreenPoint(const Eegeo::v2& point)
        {
            for (int i = 0; i != m_InteractableItems.size(); i++) {
                if (IsScreenPointInsideModel(point, m_InteractableItems[i])) {
                    return m_InteractableItems[i];
                }
            }
            
            return NULL;
        }
        
        void UIInteractionModule::RegisterInteractableItem(IUIInteractableItem* interactableItem)
        {
            m_InteractableItems.push_back(interactableItem);
        }
        
        void UIInteractionModule::UnRegisterInteractableItem(IUIInteractableItem* interactableItem)
        {
            std::vector<IUIInteractableItem*>::iterator position = std::find(m_InteractableItems.begin(), m_InteractableItems.end(), interactableItem);
            if (position != m_InteractableItems.end())
                m_InteractableItems.erase(position);
        }
    }
}


