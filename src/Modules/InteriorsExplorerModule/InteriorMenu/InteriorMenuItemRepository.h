// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IInteriorMenuItemObservable.h"
#include "InteriorMenuItem.h"
#include <vector>

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        
        class InteriorMenuItemRepository : protected Eegeo::NonCopyable, public IInteriorMenuItemObservable
        {
            
        public:
            
            InteriorMenuItemRepository();
            
            ~InteriorMenuItemRepository();
            
            void AddInteriorMenuItem(InteriorMenuItem* pInteriorMenuItemToAdd);
            
            void RemoveInteriorMenuItem(InteriorMenuItem* pInteriorMenuItemToRemove);
            
            int GetNumOfInteriorMenuItems() const;
            
            InteriorMenuItem* GetInteriorMenuItemAtIndex(int interiorMenuItemIndex) const;
            
            InteriorMenuItem* GetInteriorMenuItemById(TInteriorMenuItemId id) const;
            
            virtual void AddInteriorMenuObserver(IInteriorMenuItemObserver* pObserverToAdd);
            
            virtual void RemoveInteriorMenuObserver(IInteriorMenuItemObserver* pObserverToRemove);
            
        private:
            
            typedef std::vector<InteriorMenuItem*> TInteriorMenuItems;
            TInteriorMenuItems m_interiorMenuItem;
            
            typedef std::vector<IInteriorMenuItemObserver*> TInteriorMenuItemObservers;
            TInteriorMenuItemObservers m_observers;
            
            bool ContainsInteriorMenuItem(const InteriorMenuItem* pInteriorMenuItemToCheck) const;
            bool ContainsInteriorMenuItemId(TInteriorMenuItemId interiorMenuItemId) const;
        };
    }
}
