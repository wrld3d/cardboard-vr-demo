// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointRepository.h"
#include "JumpPoint.h"
#include "IJumpPointObserver.h"

#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            JumpPointRepository::JumpPointRepository()
            {
            }
            
            JumpPointRepository::~JumpPointRepository()
            {
                m_observers.clear();
                m_jumpPoint.clear();
            }
            
            void JumpPointRepository::AddJumpPoint(JumpPoint* pJumpPointToAdd)
            {
                m_jumpPoint.push_back(pJumpPointToAdd);
                
                for (int i = 0; i < m_observers.size(); i++) {
                    m_observers[i]->OnJumpPointAdded(*pJumpPointToAdd);
                }
            }
            
            void JumpPointRepository::RemoveJumpPoint(JumpPoint* pJumpPointToRemove)
            {
                std::vector<JumpPoint*>::iterator position = std::find(m_jumpPoint.begin(), m_jumpPoint.end(), pJumpPointToRemove);
                if (position != m_jumpPoint.end()) {
                    m_jumpPoint.erase(position);
                    
                    for (int i = 0; i < m_observers.size(); i++) {
                        m_observers[i]->OnJumpPointRemoved(*pJumpPointToRemove);
                    }
                }
            }
            
            int JumpPointRepository::GetNumOfJumpPoints() const
            {
                return m_jumpPoint.size();
            }
            
            JumpPoint* JumpPointRepository::GetJumpPointAtIndex(int jumpPointIndex) const
            {
                return m_jumpPoint[jumpPointIndex];
            }
            
            JumpPoint* JumpPointRepository::GetJumpPointById(TJumpPointId id) const
            {
                for (int i=0; i<GetNumOfJumpPoints(); i++) {
                    if (m_jumpPoint[i]->GetId() == id) {
                        return m_jumpPoint[i];
                    }
                }
                
                return NULL;
            }
            
            void JumpPointRepository::AddJumpPointObserver(IJumpPointObserver* pObserverToAdd)
            {
                m_observers.push_back(pObserverToAdd);
            }
            
            void JumpPointRepository::RemoveJumpPointObserver(IJumpPointObserver* pObserverToRemove)
            {
                std::vector<IJumpPointObserver*>::iterator position = std::find(m_observers.begin(), m_observers.end(), pObserverToRemove);
                if (position != m_observers.end())
                    m_observers.erase(position);
            }
            
            bool JumpPointRepository::ContainsJumpPoint(const JumpPoint* pJumpPointToCheck) const
            {
                for (int i=0; i<GetNumOfJumpPoints(); i++) {
                    if (m_jumpPoint[i] == pJumpPointToCheck) {
                        return true;
                    }
                }
                
                return false;
            }
            
            bool JumpPointRepository::ContainsJumpPointId(TJumpPointId jumpPointId) const
            {
                if (GetJumpPointById(jumpPointId) != NULL) {
                    return true;
                }
                
                return false;
            }
        }
    }
}
