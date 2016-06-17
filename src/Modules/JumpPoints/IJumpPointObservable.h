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
             * \brief Interface to an observable collection of JumpPoint objects.
             *
             *  This interface allows the registration of observer objects to receive notifications when the
             *  contents of the collection are changed. This interface is a companion to IJumpPointObserver.
             *
             */
            class IJumpPointObservable
            {
            public:
                /*! Register an observer to receive notifications when the collection's contents are modified.
                 * \param observerToAdd The observer to register.
                 */
                virtual void AddJumpPointObserver(IJumpPointObserver* pObserverToAdd) = 0;
                
                /*! De-register an observer from receiving notifications when the collection's contents are modified.
                 * \param observerToRemove The observer to de-register.
                 */
                virtual void RemoveJumpPointObserver(IJumpPointObserver* pObserverToRemove) = 0;
                virtual ~IJumpPointObservable() {};
            };
        }
    }
}
