//
//  UIInteractionController.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include <vector>
#include "ExampleController.h"
#include "IUICameraProvider.h"
#include "IUIInteractableItem.h"
#include "IUIInteractionObservable.h"
#include "../UIGaze/UIGazeView.h"

namespace Eegeo
{
    namespace UI
    {
        class UIInteractionController : public IUIInteractionObservable
        {
        private:
            
            float m_GazedTime = 0.0f;
            
            UIGaze::UIGazeView& m_UIGazeView;
            int m_FocusedUIItemId;
            
            std::vector<IUIInteractableItem*> m_InteractableItems;
            IUICameraProvider& m_pCameraProvider;
            
        public:
            
            UIInteractionController(IUICameraProvider& p_CameraProvider, UIGaze::UIGazeView& UIGazeView);
            virtual ~UIInteractionController();
            
            void Update(float dt);
            
            void Event_ScreenInteractionStart(const Eegeo::v2& point);
            void Event_ScreenInteractionMoved(const Eegeo::v2& point);
            void Event_ScreenInteractionEnd(const Eegeo::v2& point);
            void Event_ScreenInteractionClick(const Eegeo::v2& point);
            
            const IUIInteractableItem* GetItemAtScreenPoint(const Eegeo::v2& point);
            virtual void RegisterInteractableItem(IUIInteractableItem* interactableItem);
            virtual void UnRegisterInteractableItem(IUIInteractableItem* interactableItem);
            
        };
        
    }
}
