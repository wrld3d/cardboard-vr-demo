// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IWorldMenuItemObservable.h"
#include "WorldMenuItem.h"
#include <vector>

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            
            class WorldMenuItemRepository : protected Eegeo::NonCopyable, public IWorldMenuItemObservable
            {
                
            public:
                
                WorldMenuItemRepository();
                
                ~WorldMenuItemRepository();
                
                void AddWorldMenuItem(WorldMenuItem* pWorldMenuItemToAdd);
                
                void RemoveWorldMenuItem(WorldMenuItem* pWorldMenuItemToRemove);
                
                int GetNumOfWorldMenuItems() const;
                
                WorldMenuItem* GetWorldMenuItemAtIndex(int worldMenuItemIndex) const;
                
                WorldMenuItem* GetWorldMenuItemById(TWorldMenuItemId id) const;
                
                virtual void AddWorldMenuObserver(IWorldMenuItemObserver* pObserverToAdd);
                
                virtual void RemoveWorldMenuObserver(IWorldMenuItemObserver* pObserverToRemove);
                
            private:
                
                typedef std::vector<WorldMenuItem*> TWorldMenuItems;
                TWorldMenuItems m_worldMenuItem;
                
                typedef std::vector<IWorldMenuItemObserver*> TWorldMenuItemObservers;
                TWorldMenuItemObservers m_observers;
                
                bool ContainsWorldMenuItem(const WorldMenuItem* pWorldMenuItemToCheck) const;
                bool ContainsWorldMenuItemId(TWorldMenuItemId worldMenuItemId) const;
            };
        }
    }
}
