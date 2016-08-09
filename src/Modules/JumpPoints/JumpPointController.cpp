// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointController.h"
#include "JumpPoint.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            
            JumpPointController::JumpPointController(IJumpPointObservable& jumpPointObservable
                                                     , IJumpPointViewFactory& viewFactory
                                                     , IUIInteractionObservable& uiInteractionObservable)
            : m_jumppointRepository(jumpPointObservable)
            , m_viewFactory(viewFactory)
            , m_uiInteractionObservable(uiInteractionObservable)
            {
                m_jumppointRepository.AddJumpPointObserver(this);
            }
            
            JumpPointController::~JumpPointController()
            {
                m_jumppointRepository.RemoveJumpPointObserver(this);
                
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    JumpPointView* pView = it->second;
                    m_uiInteractionObservable.UnRegisterInteractableItem(pView);
                    Eegeo_DELETE pView;
                }
                m_viewsByModel.clear();
            }
            
            void JumpPointController::Update(float deltaTime)
            {
                UpdateViews(deltaTime);
            }

            void JumpPointController::ResetVisibility()
            {
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    it->first->SetVisibilityStatus(true);
                }
            }
            
            void JumpPointController::OnJumpPointAdded(JumpPoint& jumpPoint)
            {
                Eegeo_ASSERT(!HasViewForModel(jumpPoint), "Attempt to add duplicate model to JumpPointController.");
                
                JumpPointView* pView = m_viewFactory.CreateViewForJumpPoint(jumpPoint);
                m_viewsByModel[&jumpPoint] = pView;
                m_uiInteractionObservable.RegisterInteractableItem(pView);
            }
            
            void JumpPointController::OnJumpPointRemoved(JumpPoint& jumpPoint)
            {
                Eegeo_ASSERT(HasViewForModel(jumpPoint), "Attempt to remove unknown model from JumpPointController.");
                JumpPointView* pView = GetViewForModel(jumpPoint);
                
                m_viewsByModel.erase(&jumpPoint);
                m_uiInteractionObservable.UnRegisterInteractableItem(pView);
                
                Eegeo_DELETE(pView);
            }
            
            void JumpPointController::UpdateViews(float deltaTime)
            {
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    const JumpPoint* pJumpPoint = it->first;
                    JumpPointView* pView = it->second;
                    
                    const dv3& origin = pJumpPoint->GetEcefPosition();
                    pView->SetEcefPosition(origin);
                    pView->Update(deltaTime);
                    pView->SetItemShouldRender(pJumpPoint->GetVisibility());
                }
            }
            
            JumpPointView* JumpPointController::GetViewForModel(const JumpPoint& jp) const
            {
                TViewsByModel::const_iterator foundJP = m_viewsByModel.find(const_cast<JumpPoint*>(&jp));
                
                if(foundJP != m_viewsByModel.end())
                {
                    return foundJP->second;
                }
                
                return NULL;
            }
            
            bool JumpPointController::HasViewForModel(const JumpPoint& jp) const
            {
                return (GetViewForModel(jp) != NULL);
            }
            
            
        }
    }
}
