// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IJumpPointObservable.h"
#include "JumpPoints.h"
#include <vector>

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            
            class JumpPointRepository : protected Eegeo::NonCopyable, public IJumpPointObservable
            {
            public:
                JumpPointRepository();
                
                ~JumpPointRepository();
                
                void AddJumpPoint(JumpPoint* pJumpPointToAdd);
                
                void RemoveJumpPoint(JumpPoint* pJumpPointToRemove);
                
                int GetNumOfJumpPoints() const;
                
                JumpPoint* GetJumpPointAtIndex(int jumpPointIndex) const;
                
                JumpPoint* GetJumpPointById(TJumpPointId id) const;
                
                virtual void AddJumpPointObserver(IJumpPointObserver* pObserverToAdd);
                
                virtual void RemoveJumpPointObserver(IJumpPointObserver* pObserverToRemove);
                
            private:
                typedef std::vector<JumpPoint*> TJumpPoints;
                TJumpPoints m_jumpPoint;
                
                typedef std::vector<IJumpPointObserver*> TJumpPointObservers;
                TJumpPointObservers m_observers;
                
                bool ContainsJumpPoint(const JumpPoint* pJumpPointToCheck) const;
                bool ContainsJumpPointId(TJumpPointId jumpPointId) const;
            };
        }
    }
}
