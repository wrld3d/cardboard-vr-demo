// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "JumpPoints.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
        /*!
         * \brief Interface to a factory for creating JumpPointView objects.
         *
         *  This class allows controller objects to delegate the creation of JumpPointView objects to a seperate factory class.
         *
         */
        class IJumpPointViewFactory
        {
        public:
            /*! Create a new JumpPointView to represent a given JumpPoint object.
             * \param jumpPointModel The JumpPoint model object to create a view for.
             * \return A pointer to the newly created JumpPointView to represent the given model.
             */
            virtual JumpPointView* CreateViewForJumpPoint(JumpPoint& jumpPointModel) = 0;
            
            virtual ~IJumpPointViewFactory() {};
        };
        }
    }
}
