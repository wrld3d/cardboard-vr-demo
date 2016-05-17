//
//  UIInteractionModule.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include <vector>
#include "ExampleController.h"

#include "IUIInteractableItem.h"

namespace Eegeo
{
    namespace UI
    {
        class UIInteractionModule
        {
        private:
            struct Ray
            {
                Eegeo::dv3 origin;
                Eegeo::v3 direction;
            };
            
            std::vector<IUIInteractableItem*> m_InteractableItems;
            Examples::ExampleController* m_pExampleController;
            
            bool IsScreenPointInsideModel(const Eegeo::v2& screenPoint, IUIInteractableItem* uiItem);
            void CreateWorldSpaceRayFromScreen(const Eegeo::v2& screenPoint, Ray& ray);
        public:
            UIInteractionModule(Examples::ExampleController* p_ExampleController);
            ~UIInteractionModule();
            void Update(float dt);
            void Event_ScreenInteractionStart(const Eegeo::v2& point);
            void Event_ScreenInteractionMoved(const Eegeo::v2& point);
            void Event_ScreenInteractionEnd(const Eegeo::v2& point);
            void Event_ScreenInteractionClick(const Eegeo::v2& point);
            const IUIInteractableItem* GetItemAtScreenPoint(const Eegeo::v2& point);
            void RegisterInteractableItem(IUIInteractableItem* interactableItem);
            void UnRegisterInteractableItem(IUIInteractableItem* interactableItem);
        };
        
    }
}


