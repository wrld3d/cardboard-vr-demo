// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "InteriorMenu.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        /*!
         * \brief Interface to a factory for creating InteriorMenuItemView objects.
         *
         *  This class allows controller objects to delegate the creation of InteriorMenuItemView objects to a seperate factory class.
         *
         */
        class IInteriorMenuItemViewFactory
        {
        public:
            /*! Create a new InteriorMenuItemView to represent a given InteriorMenuItem object.
             * \param InteriorMenuModel The InteriorMenuItem model object to create a view for.
             * \return A pointer to the newly created InteriorMenuItemView to represent the given model.
             */
            virtual InteriorMenuItemView* CreateViewForInteriorMenuItem(InteriorMenuItem& InteriorMenuModel) = 0;
            
            virtual ~IInteriorMenuItemViewFactory() {};
        };
    }
}
