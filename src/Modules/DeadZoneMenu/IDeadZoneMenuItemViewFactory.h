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
             * \brief Interface to a factory for creating DeadZoneMenuItemView objects.
             *
             *  This class allows controller objects to delegate the creation of DeadZoneMenuItemView objects to a seperate factory class.
             *
             */
            class IDeadZoneMenuItemViewFactory
            {
            public:
                /*! Create a new DeadZoneMenuItemView to represent a given DeadZoneMenuItem object.
                 * \param deadZoneMenuModel The DeadZoneMenuItem model object to create a view for.
                 * \return A pointer to the newly created DeadZoneMenuItemView to represent the given model.
                 */
                virtual DeadZoneMenuItemView* CreateViewForDeadZoneMenuItem(DeadZoneMenuItem& deadZoneMenuModel) = 0;
                
                virtual ~IDeadZoneMenuItemViewFactory() {};
            };
        }
    }
}
