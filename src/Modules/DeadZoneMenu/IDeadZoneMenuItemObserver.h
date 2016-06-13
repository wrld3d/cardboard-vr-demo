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
             * \brief Interface to an observer of a collection DeadZoneMenuItem objects.
             *
             *  This interface specifies how an object can recieve notifications when the contents of a DeadZoneMenuItem collection
             *  is modified. This interface is a companion to IDeadZoneMenuItemObservable.
             *
             */
            class IDeadZoneMenuItemObserver
            {
            public:
                /*! Notification that a DeadZoneMenuItem has been added to a collection.
                 * \param deadZoneMenuItem The DeadZoneMenuItem that has been added to the collection.
                 */
                virtual void OnDeadZoneMenuItemAdded(DeadZoneMenuItem& deadZoneMenuItem) = 0;
                
                /*! Notification that a DeadZoneMenuItem has been removed from a collection.
                 * \param deadZoneMenuItem The DeadZoneMenuItem that has been removed from the collection.
                 */
                virtual void OnDeadZoneMenuItemRemoved(DeadZoneMenuItem& deadZoneMenuItem) = 0;
                
                virtual ~IDeadZoneMenuItemObserver() {};
            };
        }
    }
}
