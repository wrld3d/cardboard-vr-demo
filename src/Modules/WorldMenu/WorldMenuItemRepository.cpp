// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WorldMenuItemRepository.h"
#include "WorldMenuItem.h"
#include "IWorldMenuItemObserver.h"

#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            WorldMenuItemRepository::WorldMenuItemRepository()
            {
            }
            
            WorldMenuItemRepository::~WorldMenuItemRepository()
            {
                m_observers.clear();
                m_worldMenuItem.clear();
            }
            
            void WorldMenuItemRepository::AddWorldMenuItem(WorldMenuItem* pWorldMenuItemToAdd)
            {
                m_worldMenuItem.push_back(pWorldMenuItemToAdd);
                
                for (int i = 0; i < m_observers.size(); i++) {
                    m_observers[i]->OnWorldMenuItemAdded(*pWorldMenuItemToAdd);
                }
            }
            
            void WorldMenuItemRepository::RemoveWorldMenuItem(WorldMenuItem* pWorldMenuItemToRemove)
            {
                std::vector<WorldMenuItem*>::iterator position = std::find(m_worldMenuItem.begin(), m_worldMenuItem.end(), pWorldMenuItemToRemove);
                if (position != m_worldMenuItem.end()) {
                    m_worldMenuItem.erase(position);
                    
                    for (int i = 0; i < m_observers.size(); i++) {
                        m_observers[i]->OnWorldMenuItemRemoved(*pWorldMenuItemToRemove);
                    }
                }
            }
            
            int WorldMenuItemRepository::GetNumOfWorldMenuItems() const
            {
                return (int)m_worldMenuItem.size();
            }
            
            WorldMenuItem* WorldMenuItemRepository::GetWorldMenuItemAtIndex(int worldMenuItemIndex) const
            {
                return m_worldMenuItem[worldMenuItemIndex];
            }
            
            WorldMenuItem* WorldMenuItemRepository::GetWorldMenuItemById(TWorldMenuItemId id) const
            {
                for (int i=0; i<GetNumOfWorldMenuItems(); i++) {
                    if (m_worldMenuItem[i]->GetId() == id) {
                        return m_worldMenuItem[i];
                    }
                }
                
                return NULL;
            }
            
            void WorldMenuItemRepository::AddWorldMenuObserver(IWorldMenuItemObserver* pObserverToAdd)
            {
                m_observers.push_back(pObserverToAdd);
            }
            
            void WorldMenuItemRepository::RemoveWorldMenuObserver(IWorldMenuItemObserver* pObserverToRemove)
            {
                std::vector<IWorldMenuItemObserver*>::iterator position = std::find(m_observers.begin(), m_observers.end(), pObserverToRemove);
                if (position != m_observers.end())
                    m_observers.erase(position);
            }
            
            bool WorldMenuItemRepository::ContainsWorldMenuItem(const WorldMenuItem* pWorldMenuItemToCheck) const
            {
                for (int i=0; i<GetNumOfWorldMenuItems(); i++) {
                    if (m_worldMenuItem[i] == pWorldMenuItemToCheck) {
                        return true;
                    }
                }
                
                return false;
            }
            
            bool WorldMenuItemRepository::ContainsWorldMenuItemId(TWorldMenuItemId worldMenuItemId) const
            {
                if (GetWorldMenuItemById(worldMenuItemId) != NULL) {
                    return true;
                }
                
                return false;
            }
        }
    }
}
