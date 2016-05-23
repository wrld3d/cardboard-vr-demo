//
//  IUIInteractionObservable.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

namespace Eegeo
{
    namespace UI
    {
        /*!
         * \brief Interface to an observable collection of UI objects.
         *
         *  This interface allows the registration of observer objects to receive notifications when the
         *  contents of the collection are changed. This interface is a companion to IUIInteractableItem.
         *
         */
        class IUIInteractionObservable
        {
        public:
            virtual void RegisterInteractableItem(IUIInteractableItem* interactableItem) = 0;
            virtual void UnRegisterInteractableItem(IUIInteractableItem* interactableItem) = 0;
            virtual ~IUIInteractionObservable() {}
        };
        
    }
}

