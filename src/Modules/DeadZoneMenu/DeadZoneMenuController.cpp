// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "DeadZoneMenuController.h"
#include "DeadZoneMenuItem.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            
            DeadZoneMenuController::DeadZoneMenuController(IDeadZoneMenuItemObservable& deadZoneMenuItemObservable, IDeadZoneMenuItemViewFactory& viewFactory, IUIInteractionObservable& uiInteractionObservable , IUICameraProvider& uiCameraProvider)
            : m_deadZoneMenuItemRepository(deadZoneMenuItemObservable)
            , m_viewFactory(viewFactory)
            , m_pIUIInteractionObservable(uiInteractionObservable)
            , m_UICameraProvider(uiCameraProvider)
            {
                
                m_isMenuShown = false;
                m_deadZoneMenuItemRepository.AddDeadZoneMenuObserver(this);
            }
            
            DeadZoneMenuController::~DeadZoneMenuController()
            {
                m_deadZoneMenuItemRepository.RemoveDeadZoneMenuObserver(this);
                
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
                PositionItems();
                for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                {
                    DeadZoneMenuItemView* pView = it->second;
                    pView->Update(deltaTime);
                }
            }
            
            void DeadZoneMenuController::OnDeadZoneMenuItemAdded(DeadZoneMenuItem& deadZoneMenuItem)
            {
                Eegeo_ASSERT(!HasViewForModel(deadZoneMenuItem), "Attempt to add duplicate model to DeadZoneMenuController.");
                
                DeadZoneMenuItemView* pView = m_viewFactory.CreateViewForDeadZoneMenuItem(deadZoneMenuItem);
                m_viewsByModel[&deadZoneMenuItem] = pView;
                
                m_pIUIInteractionObservable.RegisterInteractableItem(pView);
                m_isMenuShown = false;
            }
            
            void DeadZoneMenuController::OnDeadZoneMenuItemRemoved(DeadZoneMenuItem& deadZoneMenuItem)
            {
                Eegeo_ASSERT(HasViewForModel(deadZoneMenuItem), "Attempt to remove unknown model from DeadZoneMenuController.");
                DeadZoneMenuItemView* pView = GetViewForModel(deadZoneMenuItem);
                
                m_viewsByModel.erase(&deadZoneMenuItem);
                m_pIUIInteractionObservable.UnRegisterInteractableItem(pView);
                
                Eegeo_DELETE(pView);
            }
            
            
            void DeadZoneMenuController::PositionItems()
            {
                
                
                float halfCount =  m_viewsByModel.size()/2;
                if(m_viewsByModel.size()%2==0)
                    halfCount-=0.5f;
                
                Eegeo::dv3 center = m_UICameraProvider.GetRenderCameraForUI().GetEcefLocation();
                
                Eegeo::v3 right(m_UICameraProvider.GetOrientation().GetRow(0));
                Eegeo::v3 top(m_UICameraProvider.GetOrientation().GetRow(1));
                Eegeo::v3 forward(m_UICameraProvider.GetOrientation().GetRow(2));
                
                Eegeo::v3 vA = center.ToSingle();
                Eegeo::v3 vB = forward;
                float angle = Eegeo::Math::Rad2Deg(Eegeo::Math::ACos(Eegeo::v3::Dot(vA, vB)/(vA.Length()*vB.Length())));
                float marginAngle = 150;
                
                int positionMultiplier = 550;
                if(angle<marginAngle)
                    positionMultiplier *= -1;
                
                bool shouldUpdatePosition = false;
                
                if(!m_isMenuShown && angle>marginAngle)
                {
                    m_isMenuShown = true;
                    shouldUpdatePosition = true;
                }
                else if(m_isMenuShown && angle<marginAngle)
                {
                    m_isMenuShown = false;
                    shouldUpdatePosition = true;
                }
                
                if(shouldUpdatePosition)
                {
                    
                    for(TViewsByModel::iterator it = m_viewsByModel.begin(); it != m_viewsByModel.end(); ++it)
                    {
                        DeadZoneMenuItemView* pView = it->second;
                        Eegeo::dv3 position(center + (forward*positionMultiplier) + (right*(-50*halfCount)) + (top*-35));
                        pView->SetEcefPosition(position);
                        halfCount--;
                    }
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
