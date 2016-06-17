// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "DeadZoneMenu.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            /*!
             * \brief Interface to an observable collection of DeadZoneMenuItem objects.
             *
             *  This interface allows the registration of observer objects to receive notifications when the
             *  contents of the collection are changed. This interface is a companion to IDeadZoneMenuItemObserver.
             *
             */
            class IDeadZoneMenuItemObservable
            {
            public:
                /*! Register an observer to receive notifications when the collection's contents are modified.
                 * \param observerToAdd The observer to register.
                 */
                virtual void AddDeadZoneMenuObserver(IDeadZoneMenuItemObserver* pObserverToAdd) = 0;
                
                /*! De-register an observer from receiving notifications when the collection's contents are modified.
                 * \param observerToRemove The observer to de-register.
                 */
                virtual void RemoveDeadZoneMenuObserver(IDeadZoneMenuItemObserver* pObserverToRemove) = 0;
                virtual ~IDeadZoneMenuItemObservable() {};
            };
        }
    }
}
