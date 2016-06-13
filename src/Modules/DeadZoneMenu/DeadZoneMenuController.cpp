// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuController.h"
#include "DeadZoneMenuItem.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuController::DeadZoneMenuController(IDeadZoneMenuItemObservable& DeadZoneMenuItemObservable, IDeadZoneMenuItemViewFactory& viewFactory, IUIInteractionObservable& p_IUIInteractionObservable)
            : m_DeadZoneMenuItemRepository(DeadZoneMenuItemObservable)
            , m_viewFactory(viewFactory)
            , m_pIUIInteractionObservable(p_IUIInteractionObservable)
            {
                m_DeadZoneMenuItemRepository.AddDeadZoneMenuObserver(this);
            }
            
            DeadZoneMenuController::~DeadZoneMenuController()
            {
                m_DeadZoneMenuItemRepository.RemoveDeadZoneMenuObserver(this);
                
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    DeadZoneMenuItemView* pView = it->second;
                    m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
                    Eegeo_DELETE pView;
                }
                m_viewsByModel.clear();
            }
            
            void DeadZoneMenuController::Update(float deltaTime)
            {
                UpdateViews();
            }
            
            void DeadZoneMenuController::OnDeadZoneMenuItemAdded(DeadZoneMenuItem& DeadZoneMenuItem)
            {
                Eegeo_ASSERT(!HasViewForModel(DeadZoneMenuItem), "Attempt to add duplicate model to DeadZoneMenuController.");
                
                DeadZoneMenuItemView* pView = m_viewFactory.CreateViewForDeadZoneMenuItem(DeadZoneMenuItem);
                m_viewsByModel[&DeadZoneMenuItem] = pView;
                m_pIUIInteractionObservable.RegisterInteractableItem(pView);
            }
            
            void DeadZoneMenuController::OnDeadZoneMenuItemRemoved(DeadZoneMenuItem& DeadZoneMenuItem)
            {
                Eegeo_ASSERT(HasViewForModel(DeadZoneMenuItem), "Attempt to remove unknown model from DeadZoneMenuController.");
                DeadZoneMenuItemView* pView = GetViewForModel(DeadZoneMenuItem);
                
                m_viewsByModel.erase(&DeadZoneMenuItem);
                m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
                
                Eegeo_DELETE(pView);
            }
            
            void DeadZoneMenuController::UpdateViews()
            {
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    const DeadZoneMenuItem* pDeadZoneMenuItem = it->first;
                    DeadZoneMenuItemView* pView = it->second;
                    
                    const dv3& origin = pDeadZoneMenuItem->GetEcefPosition();
                    pView->SetEcefPosition(origin);
                    pView->SetColor(pDeadZoneMenuItem->GetColor());
                }
            }
            
            DeadZoneMenuItemView* DeadZoneMenuController::GetViewForModel(const DeadZoneMenuItem& jp) const
            {
                TViewsByModel::const_iterator foundJP = m_viewsByModel.find(const_cast<DeadZoneMenuItem*>(&jp));
                
                if(foundJP != m_viewsByModel.end())
                {
                    return foundJP->second;
                }
                
                return NULL;
            }
            
            bool DeadZoneMenuController::HasViewForModel(const DeadZoneMenuItem& jp) const
            {
                return (GetViewForModel(jp) != NULL);
            }
            
            
        }
    }
}
