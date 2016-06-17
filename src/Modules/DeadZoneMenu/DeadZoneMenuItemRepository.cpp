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
                m_deadZoneMenuItem.clear();
            }
            
            void DeadZoneMenuItemRepository::AddDeadZoneMenuItem(DeadZoneMenuItem* pDeadZoneMenuItemToAdd)
            {
                m_deadZoneMenuItem.push_back(pDeadZoneMenuItemToAdd);
                
                for (int i = 0; i < m_observers.size(); i++) {
                    m_observers[i]->OnDeadZoneMenuItemAdded(*pDeadZoneMenuItemToAdd);
                }
            }
            
            void DeadZoneMenuItemRepository::RemoveDeadZoneMenuItem(DeadZoneMenuItem* pDeadZoneMenuItemToRemove)
            {
                std::vector<DeadZoneMenuItem*>::iterator position = std::find(m_deadZoneMenuItem.begin(), m_deadZoneMenuItem.end(), pDeadZoneMenuItemToRemove);
                if (position != m_deadZoneMenuItem.end()) {
                    m_deadZoneMenuItem.erase(position);
                    
                    for (int i = 0; i < m_observers.size(); i++) {
                        m_observers[i]->OnDeadZoneMenuItemRemoved(*pDeadZoneMenuItemToRemove);
                    }
                }
            }
            
            int DeadZoneMenuItemRepository::GetNumOfDeadZoneMenuItems() const
            {
                return m_deadZoneMenuItem.size();
            }
            
            DeadZoneMenuItem* DeadZoneMenuItemRepository::GetDeadZoneMenuItemAtIndex(int deadZoneMenuItemIndex) const
            {
                return m_deadZoneMenuItem[deadZoneMenuItemIndex];
            }
            
            DeadZoneMenuItem* DeadZoneMenuItemRepository::GetDeadZoneMenuItemById(TDeadZoneMenuItemId id) const
            {
                for (int i=0; i<GetNumOfDeadZoneMenuItems(); i++) {
                    if (m_deadZoneMenuItem[i]->GetId() == id) {
                        return m_deadZoneMenuItem[i];
                    }
                }
                
                return NULL;
            }
            
            void DeadZoneMenuItemRepository::AddDeadZoneMenuObserver(IDeadZoneMenuItemObserver* pObserverToAdd)
            {
                m_observers.push_back(pObserverToAdd);
            }
            
            void DeadZoneMenuItemRepository::RemoveDeadZoneMenuObserver(IDeadZoneMenuItemObserver* pObserverToRemove)
            {
                std::vector<IDeadZoneMenuItemObserver*>::iterator position = std::find(m_observers.begin(), m_observers.end(), pObserverToRemove);
                if (position != m_observers.end())
                    m_observers.erase(position);
            }
            
            bool DeadZoneMenuItemRepository::ContainsDeadZoneMenuItem(const DeadZoneMenuItem* pDeadZoneMenuItemToCheck) const
            {
                for (int i=0; i<GetNumOfDeadZoneMenuItems(); i++) {
                    if (m_deadZoneMenuItem[i] == pDeadZoneMenuItemToCheck) {
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
