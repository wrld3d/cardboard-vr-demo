// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

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
            
            float m_gazedTime = 0.0f;
            
            UIGaze::UIGazeView& m_uiGazeView;
            int m_focusedUIItemId;
            
            std::vector<IUIInteractableItem*> m_interactableItems;
            IUICameraProvider& m_cameraProvider;
            
        public:
            
            UIInteractionController(IUICameraProvider& cameraProvider, UIGaze::UIGazeView& uiGazeView);
            virtual ~UIInteractionController();
            
            void Update(float dt);
            
            void Event_ScreenInteractionStart(const Eegeo::v2& point);
            void Event_ScreenInteractionMoved(const Eegeo::v2& point);
            void Event_ScreenInteractionEnd(const Eegeo::v2& point);
            void Event_ScreenInteractionClick(const Eegeo::v2& point);
            
            const IUIInteractableItem* GetItemAtScreenPoint(const Eegeo::v2& point);
            virtual void RegisterInteractableItem(IUIInteractableItem* pInteractableItem);
            virtual void UnRegisterInteractableItem(IUIInteractableItem* pInteractableItem);
            
        };
        
    }
}
