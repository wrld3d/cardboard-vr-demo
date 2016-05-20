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
             * \brief Interface to an observer of a collection Jump Point objects.
             *
             *  This interface specifies how an object can recieve notifications when the contents of a Jump Point collection
             *  is modified. This interface is a companion to IJumpPointObservable.
             *
             */
            class IJumpPointObserver
            {
            public:
                /*! Notification that a Jump Point has been added to a collection.
                 * \param jumpPoint The Jump Point that has been added to the collection.
                 */
                virtual void OnJumpPointAdded(JumpPoint& jumpPoint) = 0;
                
                /*! Notification that a Jump Point has been removed from a collection.
                 * \param jumpPoint The Jump Point that has been removed from the collection.
                 */
                virtual void OnJumpPointRemoved(JumpPoint& jumpPoint) = 0;
                
                virtual ~IJumpPointObserver() {};
            };
        }
    }
}
