// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorMenuController.h"
#include "InteriorMenuItemView.h"
#include "InteriorMenuItem.h"
#include "Logger.h"
#include <vector>

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        
        InteriorMenuController::InteriorMenuController(IInteriorMenuItemObservable& InteriorMenuItemObservable, IInteriorMenuItemViewFactory& viewFactory, Eegeo::UI::IUIInteractionObservable& uiInteractionObservable , Eegeo::UI::IUICameraProvider& uiCameraProvider)
        : m_InteriorMenuItemRepository(InteriorMenuItemObservable)
        , m_viewFactory(viewFactory)
        , m_pIUIInteractionObservable(uiInteractionObservable)
        , m_uiCameraProvider(uiCameraProvider)
        {
            m_menuItemsShouldRender = true;
            m_isMenuShown = false;
            m_InteriorMenuItemRepository.AddInteriorMenuObserver(this);
        }
        
        InteriorMenuController::~InteriorMenuController()
        {
            m_InteriorMenuItemRepository.RemoveInteriorMenuObserver(this);
            for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
            {
                InteriorMenuItemView* pView = it->second;
                m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
            }
            m_viewsByModel.clear();
        }
        
        void InteriorMenuController::SetMenuItemsShouldRender(bool menuItemsShouldRender)
        {
            
            m_menuItemsShouldRender = menuItemsShouldRender;
            for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
            {
                InteriorMenuItemView* pView = it->second;
                pView->SetItemShouldRender(menuItemsShouldRender);
            }
        }
        
        void InteriorMenuController::Update(float deltaTime)
        {
            PositionItems();
            for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
            {
                InteriorMenuItemView* pView = it->second;
                pView->SetItemShouldRender(m_menuItemsShouldRender & m_isMenuShown);
                pView->Update(deltaTime);
            }
            
        }
        
        void InteriorMenuController::SetSelectedFloorId(int floorId)
        {
            
            m_floorId = floorId;
            
            for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
            {
                InteriorMenuItemView* pView = it->second;
                if(pView->GetInteriorMenuItem().GetId()==m_floorId)
                {
                    pView->SetItemSelected();
                }
                else
                {
                    pView->SetItemUnselected();
                }
                
            }
        }
        
        void InteriorMenuController::OnInteriorMenuItemAdded(InteriorMenuItem& InteriorMenuItem)
        {
            Eegeo_ASSERT(!HasViewForModel(InteriorMenuItem), "Attempt to add duplicate model to InteriorMenuController.");
            
            InteriorMenuItemView* pView = m_viewFactory.CreateViewForInteriorMenuItem(InteriorMenuItem);
            m_viewsByModel[&InteriorMenuItem] = pView;
            
            m_pIUIInteractionObservable.RegisterInteractableItem(pView);
            m_isMenuShown = false;
        }
        
        void InteriorMenuController::OnInteriorMenuItemRemoved(InteriorMenuItem& InteriorMenuItem)
        {
            Eegeo_ASSERT(HasViewForModel(InteriorMenuItem), "Attempt to remove unknown model from InteriorMenuController.");
            InteriorMenuItemView* pView = GetViewForModel(InteriorMenuItem);
            
            m_viewsByModel.erase(&InteriorMenuItem);
            m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
            
        }
        
        
        void InteriorMenuController::PositionItems()
        {
            
            if(!m_menuItemsShouldRender)
                return;
            
            Eegeo::m33 headTrackedOrientation;
            Eegeo::m33::Mul(headTrackedOrientation, m_uiCameraProvider.GetBaseOrientation(), m_cachedHeadTracker);
            
            float halfCount = m_viewsByModel.size()/2;
            if(m_viewsByModel.size()%2==0)
                halfCount-=0.5f;
            
            Eegeo::dv3 center = m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation();
            
            Eegeo::v3 top(headTrackedOrientation.GetRow(1));
            Eegeo::v3 forward(headTrackedOrientation.GetRow(2));
            Eegeo::v3 right(headTrackedOrientation.GetRow(0));
            
            Eegeo::v3 vA = center.ToSingle();
            Eegeo::v3 vB = m_uiCameraProvider.GetOrientation().GetRow(2);
            float angle = Eegeo::Math::Rad2Deg(Eegeo::Math::ACos(Eegeo::v3::Dot(vA, vB)/(vA.Length()*vB.Length())));
            
            
            float marginAngle = 90;
            int positionMultiplier = 600;
            
            bool shouldUpdatePosition = false;
            
            if(!m_isMenuShown && angle<=marginAngle)
            {
                m_isMenuShown = true;
                shouldUpdatePosition = true;
                m_cachedHeadTracker = m_uiCameraProvider.GetHeadTrackerOrientation();
                m_cachedCenter = center;
            }
            else if(m_isMenuShown && angle>marginAngle)
            {
                m_isMenuShown = false;
                shouldUpdatePosition = true;
            }
            
            if ((m_cachedCenter - center).LengthSq() > 1) {
                m_cachedCenter = center;
                shouldUpdatePosition = true;
            }
            
            if(shouldUpdatePosition || m_isMenuShown)
            {
                
                std::vector<InteriorMenuItemView*> items;
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    std::vector<InteriorMenuItemView*>::iterator itItems = items.begin();
                    for(; itItems != items.end(); ++itItems)
                    {
                        if((*itItems)->GetInteriorMenuItem().GetId() < it->second->GetInteriorMenuItem().GetId())
                        {
                            break;
                        }
                    }
                    items.insert(itItems, it->second);
                }
                
                for(std::vector<InteriorMenuItemView*>::iterator it = items.begin(); it != items.end(); ++it)
                {
                    InteriorMenuItemView* pView = *it;
                    if(!m_isMenuShown)
                    {
                        pView->SetItemShouldRender(false);
                        continue;
                    }
                    
                    Eegeo::dv3 position(center + (forward*positionMultiplier) + (top*40) + (right*60*halfCount));
                    pView->SetEcefPosition(position);
                    pView->SetItemShouldRender(true);
                    halfCount-=1;
                }
                
                items.clear();
                m_lastCameraPosition = center;
            }
        }
        
        
        InteriorMenuItemView* InteriorMenuController::GetViewForModel(const InteriorMenuItem& jp) const
        {
            TViewsByModel::const_iterator foundJP = m_viewsByModel.find(const_cast<InteriorMenuItem*>(&jp));
            
            if(foundJP != m_viewsByModel.end())
            {
                return foundJP->second;
            }
            
            return NULL;
        }
        
        bool InteriorMenuController::HasViewForModel(const InteriorMenuItem& jp) const
        {
            return (GetViewForModel(jp) != NULL);
        }
        
    }
}
