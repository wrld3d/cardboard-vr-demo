// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorMenuItemRepository.h"
#include "InteriorMenuItem.h"
#include "IInteriorMenuItemObserver.h"

#include <algorithm>

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        InteriorMenuItemRepository::InteriorMenuItemRepository()
        {
        }
        
        InteriorMenuItemRepository::~InteriorMenuItemRepository()
        {
            m_observers.clear();
            m_InteriorMenuItem.clear();
        }
        
        void InteriorMenuItemRepository::AddInteriorMenuItem(InteriorMenuItem* pInteriorMenuItemToAdd)
        {
            m_InteriorMenuItem.push_back(pInteriorMenuItemToAdd);
            
            for (int i = 0; i < m_observers.size(); i++) {
                m_observers[i]->OnInteriorMenuItemAdded(*pInteriorMenuItemToAdd);
            }
        }
        
        void InteriorMenuItemRepository::RemoveInteriorMenuItem(InteriorMenuItem* pInteriorMenuItemToRemove)
        {
            std::vector<InteriorMenuItem*>::iterator position = std::find(m_InteriorMenuItem.begin(), m_InteriorMenuItem.end(), pInteriorMenuItemToRemove);
            if (position != m_InteriorMenuItem.end()) {
                m_InteriorMenuItem.erase(position);
                
                for (int i = 0; i < m_observers.size(); i++) {
                    m_observers[i]->OnInteriorMenuItemRemoved(*pInteriorMenuItemToRemove);
                }
            }
        }
        
        int InteriorMenuItemRepository::GetNumOfInteriorMenuItems() const
        {
            return (int)m_InteriorMenuItem.size();
        }
        
        InteriorMenuItem* InteriorMenuItemRepository::GetInteriorMenuItemAtIndex(int InteriorMenuItemIndex) const
        {
            return m_InteriorMenuItem[InteriorMenuItemIndex];
        }
        
        InteriorMenuItem* InteriorMenuItemRepository::GetInteriorMenuItemById(TInteriorMenuItemId id) const
        {
            for (int i=0; i<GetNumOfInteriorMenuItems(); i++) {
                if (m_InteriorMenuItem[i]->GetId() == id) {
                    return m_InteriorMenuItem[i];
                }
            }
            
            return NULL;
        }
        
        void InteriorMenuItemRepository::AddInteriorMenuObserver(IInteriorMenuItemObserver* pObserverToAdd)
        {
            m_observers.push_back(pObserverToAdd);
        }
        
        void InteriorMenuItemRepository::RemoveInteriorMenuObserver(IInteriorMenuItemObserver* pObserverToRemove)
        {
            std::vector<IInteriorMenuItemObserver*>::iterator position = std::find(m_observers.begin(), m_observers.end(), pObserverToRemove);
            if (position != m_observers.end())
                m_observers.erase(position);
        }
        
        bool InteriorMenuItemRepository::ContainsInteriorMenuItem(const InteriorMenuItem* pInteriorMenuItemToCheck) const
        {
            for (int i=0; i<GetNumOfInteriorMenuItems(); i++) {
                if (m_InteriorMenuItem[i] == pInteriorMenuItemToCheck) {
                    return true;
                }
            }
            
            return false;
        }
        
        bool InteriorMenuItemRepository::ContainsInteriorMenuItemId(TInteriorMenuItemId InteriorMenuItemId) const
        {
            if (GetInteriorMenuItemById(InteriorMenuItemId) != NULL) {
                return true;
            }
            
            return false;
        }
    }
}
