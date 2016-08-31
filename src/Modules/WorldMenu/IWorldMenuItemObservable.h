// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "WorldMenu.h"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            /*!
             * \brief Interface to an observable collection of WorldMenuItem objects.
             *
             *  This interface allows the registration of observer objects to receive notifications when the
             *  contents of the collection are changed. This interface is a companion to IWorldMenuItemObserver.
             *
             */
            class IWorldMenuItemObservable
            {
            public:
                /*! Register an observer to receive notifications when the collection's contents are modified.
                 * \param observerToAdd The observer to register.
                 */
                virtual void AddWorldMenuObserver(IWorldMenuItemObserver* pObserverToAdd) = 0;
                
                /*! De-register an observer from receiving notifications when the collection's contents are modified.
                 * \param observerToRemove The observer to de-register.
                 */
                virtual void RemoveWorldMenuObserver(IWorldMenuItemObserver* pObserverToRemove) = 0;
                virtual ~IWorldMenuItemObservable() {};
            };
        }
    }
}
