// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorMenu.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        /*!
         * \brief Interface to an observer of a collection InteriorMenuItem objects.
         *
         *  This interface specifies how an object can recieve notifications when the contents of a InteriorMenuItem collection
         *  is modified. This interface is a companion to IInteriorMenuItemObservable.
         *
         */
        class IInteriorMenuItemObserver
        {
        public:
            /*! Notification that a InteriorMenuItem has been added to a collection.
             * \param InteriorMenuItem The InteriorMenuItem that has been added to the collection.
             */
            virtual void OnInteriorMenuItemAdded(InteriorMenuItem& InteriorMenuItem) = 0;
            
            /*! Notification that a InteriorMenuItem has been removed from a collection.
             * \param InteriorMenuItem The InteriorMenuItem that has been removed from the collection.
             */
            virtual void OnInteriorMenuItemRemoved(InteriorMenuItem& InteriorMenuItem) = 0;
            
            virtual ~IInteriorMenuItemObserver() {};
        };
    }
}
