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
             * \brief Interface to an observer of a collection WorldMenuItem objects.
             *
             *  This interface specifies how an object can recieve notifications when the contents of a WorldMenuItem collection
             *  is modified. This interface is a companion to IWorldMenuItemObservable.
             *
             */
            class IWorldMenuItemObserver
            {
            public:
                /*! Notification that a WorldMenuItem has been added to a collection.
                 * \param WorldMenuItem The WorldMenuItem that has been added to the collection.
                 */
                virtual void OnWorldMenuItemAdded(WorldMenuItem& WorldMenuItem) = 0;
                
                /*! Notification that a WorldMenuItem has been removed from a collection.
                 * \param WorldMenuItem The WorldMenuItem that has been removed from the collection.
                 */
                virtual void OnWorldMenuItemRemoved(WorldMenuItem& WorldMenuItem) = 0;
                
                virtual ~IWorldMenuItemObserver() {};
            };
        }
    }
}
