// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IDeadZoneMenuItemObservable.h"
#include "DeadZoneMenuItem.h"
#include <vector>

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            class DeadZoneMenuItemRepository : protected Eegeo::NonCopyable, public IDeadZoneMenuItemObservable
            {
                
            public:
                
                DeadZoneMenuItemRepository();
                
                ~DeadZoneMenuItemRepository();
                
                void AddDeadZoneMenuItem(DeadZoneMenuItem* pDeadZoneMenuItemToAdd);
                
                void RemoveDeadZoneMenuItem(DeadZoneMenuItem* pDeadZoneMenuItemToRemove);
                
                size_t GetNumOfDeadZoneMenuItems() const;
                
                DeadZoneMenuItem* GetDeadZoneMenuItemAtIndex(int deadZoneMenuItemIndex) const;
                
                DeadZoneMenuItem* GetDeadZoneMenuItemById(TDeadZoneMenuItemId id) const;
                
                virtual void AddDeadZoneMenuObserver(IDeadZoneMenuItemObserver* pObserverToAdd);
                
                virtual void RemoveDeadZoneMenuObserver(IDeadZoneMenuItemObserver* pObserverToRemove);
                
            private:
                
                typedef std::vector<DeadZoneMenuItem*> TDeadZoneMenuItems;
                TDeadZoneMenuItems m_deadZoneMenuItem;
                
                typedef std::vector<IDeadZoneMenuItemObserver*> TDeadZoneMenuItemObservers;
                TDeadZoneMenuItemObservers m_observers;
                
                bool ContainsDeadZoneMenuItem(const DeadZoneMenuItem* pDeadZoneMenuItemToCheck) const;
                bool ContainsDeadZoneMenuItemId(TDeadZoneMenuItemId deadZoneMenuItemId) const;
            };
        }
    }
}
