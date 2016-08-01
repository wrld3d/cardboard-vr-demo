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
             * \brief Interface to a factory for creating WorldMenuItemView objects.
             *
             *  This class allows controller objects to delegate the creation of WorldMenuItemView objects to a seperate factory class.
             *
             */
            class IWorldMenuItemViewFactory
            {
            public:
                /*! Create a new WorldMenuItemView to represent a given WorldMenuItem object.
                 * \param WorldMenuModel The WorldMenuItem model object to create a view for.
                 * \return A pointer to the newly created WorldMenuItemView to represent the given model.
                 */
                virtual WorldMenuItemView* CreateViewForWorldMenuItem(WorldMenuItem& WorldMenuModel) = 0;
                
                virtual ~IWorldMenuItemViewFactory() {};
            };
        }
    }
}
