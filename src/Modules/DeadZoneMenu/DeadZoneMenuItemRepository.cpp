// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuItemRepository.h"
#include "DeadZoneMenuItem.h"
#include "IDeadZoneMenuItemObserver.h"

#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            DeadZoneMenuItemRepository::DeadZoneMenuItemRepository()
            {
            }
            
            DeadZoneMenuItemRepository::~DeadZoneMenuItemRepository()
            {
                m_observers.clear();
                m_DeadZoneMenuItem.clear();
            }
            
            void DeadZoneMenuItemRepository::AddDeadZoneMenuItem(DeadZoneMenuItem* pDeadZoneMenuItemToAdd)
            {
                m_DeadZoneMenuItem.push_back(pDeadZoneMenuItemToAdd);
                
                for (int i = 0; i < m_observers.size(); i++) {
                    m_observers[i]->OnDeadZoneMenuItemAdded(*pDeadZoneMenuItemToAdd);
                }
            }
            
            void DeadZoneMenuItemRepository::RemoveDeadZoneMenuItem(DeadZoneMenuItem* pDeadZoneMenuItemToRemove)
            {
                std::vector<DeadZoneMenuItem*>::iterator position = std::find(m_DeadZoneMenuItem.begin(), m_DeadZoneMenuItem.end(), pDeadZoneMenuItemToRemove);
                if (position != m_DeadZoneMenuItem.end()) {
                    m_DeadZoneMenuItem.erase(position);
                    
                    for (int i = 0; i < m_observers.size(); i++) {
                        m_observers[i]->OnDeadZoneMenuItemRemoved(*pDeadZoneMenuItemToRemove);
                    }
                }
            }
            
            int DeadZoneMenuItemRepository::GetNumOfDeadZoneMenuItems() const
            {
                return m_DeadZoneMenuItem.size();
            }
            
            DeadZoneMenuItem* DeadZoneMenuItemRepository::GetDeadZoneMenuItemAtIndex(int DeadZoneMenuItemIndex) const
            {
                return m_DeadZoneMenuItem[DeadZoneMenuItemIndex];
            }
            
            DeadZoneMenuItem* DeadZoneMenuItemRepository::GetDeadZoneMenuItemById(TDeadZoneMenuItemId id) const
            {
                for (int i=0; i<GetNumOfDeadZoneMenuItems(); i++) {
                    if (m_DeadZoneMenuItem[i]->GetId() == id) {
                        return m_DeadZoneMenuItem[i];
                    }
                }
                
                return NULL;
            }
            
            void DeadZoneMenuItemRepository::AddDeadZoneMenuObserver(IDeadZoneMenuItemObserver* observerToAdd)
            {
                m_observers.push_back(observerToAdd);
            }
            
            void DeadZoneMenuItemRepository::RemoveDeadZoneMenuObserver(IDeadZoneMenuItemObserver* observerToRemove)
            {
                std::vector<IDeadZoneMenuItemObserver*>::iterator position = std::find(m_observers.begin(), m_observers.end(), observerToRemove);
                if (position != m_observers.end())
                    m_observers.erase(position);
            }
            
            bool DeadZoneMenuItemRepository::ContainsDeadZoneMenuItem(const DeadZoneMenuItem* pDeadZoneMenuItemToCheck) const
            {
                for (int i=0; i<GetNumOfDeadZoneMenuItems(); i++) {
                    if (m_DeadZoneMenuItem[i] == pDeadZoneMenuItemToCheck) {
                        return true;
                    }
                }
                
                return false;
            }
            
            bool DeadZoneMenuItemRepository::ContainsDeadZoneMenuItemId(TDeadZoneMenuItemId deadZoneMenuItemId) const
            {
                if (GetDeadZoneMenuItemById(deadZoneMenuItemId) != NULL) {
                    return true;
                }
                
                return false;
            }
        }
    }
}
