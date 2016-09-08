// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "InteriorMenuController.h"
#include "InteriorMenuItemView.h"
#include "InteriorMenuItem.h"
#include "Logger.h"
#include <vector>

namespace InteriorsExplorer
{
    const float InteriorMenuFloorAngleThreshold = 70.f;
    const float InteriorMenuHighPositionAngleThreshold = 100.f;
    
    namespace InteriorMenu
    {
        
        InteriorMenuController::InteriorMenuController(IInteriorMenuItemObservable& interiorMenuItemObservable, IInteriorMenuItemViewFactory& viewFactory, Eegeo::UI::IUIInteractionObservable& uiInteractionObservable , Eegeo::UI::IUICameraProvider& uiCameraProvider,
                                                       Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                                       , const std::string& spriteFileName
                                                       , int numberOfTilesAlong1Axis)
        : m_interiorMenuItemRepository(interiorMenuItemObservable)
        , m_viewFactory(viewFactory)
        , m_uiInteractionObservable(uiInteractionObservable)
        , m_uiCameraProvider(uiCameraProvider)
        , m_marginAngle(75.f)
        {
            const int InteriorUpIconSpriteID = 21;
            m_pInteriorMenuUpView = Eegeo_NEW(InteriorMenuUpView)(quadFactory, uiRenderableFilter, spriteFileName, InteriorUpIconSpriteID, numberOfTilesAlong1Axis);

            Eegeo::v2 size(numberOfTilesAlong1Axis,numberOfTilesAlong1Axis);
            Eegeo::v2 outMin;
            Eegeo::v2 outMax;
            Eegeo::UI::CalculateUV(size, 20, outMin, outMax);

            Eegeo::v2 dimension = Eegeo::v2(50.f,50.f);
            m_pSelectedArrow = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter,
                                                        quadFactory.CreateUIQuad(spriteFileName,
                                                                                 dimension,
                                                                                 outMin,
                                                                                 outMax,
                                                                                 Eegeo::Rendering::LayerIds::Values::AfterAll),
                                                        dimension);
            
            
            m_menuItemsShouldRender = true;
            m_isMenuShown = false;
            m_interiorMenuItemRepository.AddInteriorMenuObserver(this);
        }
        
        InteriorMenuController::~InteriorMenuController()
        {
            Eegeo_DELETE(m_pSelectedArrow);
            Eegeo_DELETE(m_pInteriorMenuUpView);
            m_interiorMenuItemRepository.RemoveInteriorMenuObserver(this);
            for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
            {
                InteriorMenuItemView* pView = it->second;
                m_uiInteractionObservable.UnRegisterInteractableItem(pView);
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
                m_pSelectedArrow->SetItemShouldRender(menuItemsShouldRender);
            }
        }
        
        void InteriorMenuController::Update(float deltaTime)
        {
            PositionItems();
            m_pSelectedArrow->Update(deltaTime);
            
            Eegeo::m33 headTrackedOrientation  = m_uiCameraProvider.GetOrientation();
            Eegeo::v3 top(headTrackedOrientation.GetRow(1));
            Eegeo::v3 forward(headTrackedOrientation.GetRow(2));
            
            Eegeo::dv3 center = m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation();
            Eegeo::dv3 position(center + (forward*100)+ (top*(Eegeo::Math::Tan(m_uiCameraProvider.GetRenderCameraForUI().GetFOV()/2.3f)*100)));
            
            m_pInteriorMenuUpView->SetEcefPosition(position);
            
            if(!m_menuItemsShouldRender || m_isMenuShown)
            {
                m_pInteriorMenuUpView->HideView();
            }
            else
            {
                m_pInteriorMenuUpView->ShowView();
            }
            
            m_pInteriorMenuUpView->Update(deltaTime);
            
            for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
            {
                InteriorMenuItemView* pView = it->second;
                bool shouldOutButtonRender = !((m_marginAngle < InteriorMenuHighPositionAngleThreshold && it->first->GetId() == -1) ||
                                               (m_marginAngle > InteriorMenuFloorAngleThreshold && it->first->GetId() == -2));
                pView->SetItemShouldRender(m_menuItemsShouldRender && m_isMenuShown && shouldOutButtonRender);
                m_pSelectedArrow->SetItemShouldRender(m_menuItemsShouldRender && m_isMenuShown);
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
        
        void InteriorMenuController::OnInteriorMenuItemAdded(InteriorMenuItem& interiorMenuItem)
        {
            Eegeo_ASSERT(!HasViewForModel(interiorMenuItem), "Attempt to add duplicate model to InteriorMenuController.");
            
            InteriorMenuItemView* pView = m_viewFactory.CreateViewForInteriorMenuItem(interiorMenuItem);
            m_viewsByModel[&interiorMenuItem] = pView;
            
            m_uiInteractionObservable.RegisterInteractableItem(pView);
            m_isMenuShown = false;
        }
        
        void InteriorMenuController::OnInteriorMenuItemRemoved(InteriorMenuItem& interiorMenuItem)
        {
            Eegeo_ASSERT(HasViewForModel(interiorMenuItem), "Attempt to remove unknown model from InteriorMenuController.");
            InteriorMenuItemView* pView = GetViewForModel(interiorMenuItem);
            
            m_viewsByModel.erase(&interiorMenuItem);
            m_uiInteractionObservable.UnRegisterInteractableItem(pView);
            
        }
        
        
        void InteriorMenuController::PositionItems()
        {
            
            if(!m_menuItemsShouldRender)
                return;
            
            Eegeo::m33 headTrackedOrientation;
            Eegeo::m33::Mul(headTrackedOrientation, m_uiCameraProvider.GetBaseOrientation(), m_cachedHeadTracker);
            
            
            Eegeo::dv3 center = m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation();
            
            Eegeo::v3 forward(headTrackedOrientation.GetRow(2));
            Eegeo::v3 top(center.ToSingle().Norm());
            Eegeo::v3 right(Eegeo::v3::Cross(top, forward));
            
            Eegeo::v3 vA = center.ToSingle();
            Eegeo::v3 vB = m_uiCameraProvider.GetOrientation().GetRow(2);
            float angle = Eegeo::Math::Rad2Deg(Eegeo::Math::ACos(Eegeo::v3::Dot(vA, vB)/(vA.Length()*vB.Length())));

            const int PositionMultiplier = 600;
            
            bool shouldUpdatePosition = false;
            
            if(!m_isMenuShown && angle<=m_marginAngle)
            {
                m_isMenuShown = true;
                shouldUpdatePosition = true;
                m_cachedHeadTracker = m_uiCameraProvider.GetHeadTrackerOrientation();
                m_cachedCenter = center;
            }
            else if(m_isMenuShown && angle>m_marginAngle)
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
                    
                    if((m_marginAngle < InteriorMenuHighPositionAngleThreshold && it->first->GetId() == -1) ||
                       (m_marginAngle > InteriorMenuFloorAngleThreshold && it->first->GetId() == -2))
                    {
                        continue;
                    }
                    
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
                
                float halfCount = items.size()/2;
                if(items.size()%2==0)
                    halfCount-=0.5f;
                
                for(std::vector<InteriorMenuItemView*>::iterator it = items.begin(); it != items.end(); ++it)
                {
                    InteriorMenuItemView* pView = *it;
                    if(!m_isMenuShown)
                    {
                        pView->SetItemShouldRender(false);
                        m_pSelectedArrow->SetItemShouldRender(false);
                        continue;
                    }
                    
                    Eegeo::dv3 position(center + (forward*PositionMultiplier) + (top*40) + (right*60*halfCount));
                    pView->SetEcefPosition(position);
                    pView->SetItemShouldRender(true);
                    m_pSelectedArrow->SetItemShouldRender(true);
                    
                    
                    if(m_floorId==pView->GetInteriorMenuItem().GetId())
                    {
                        m_pSelectedArrow->SetEcefPosition(center + (forward*PositionMultiplier) + (top*91) + (right*60*halfCount));
                    }
                    
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

        void InteriorMenuController::SetMenuVisibilityThresholdAngle(float angle)
        {
            m_marginAngle = angle;
        }

        float InteriorMenuController::GetMenuVisibilityThresholdAngle()
        {
            return m_marginAngle;
        }
    }
}
