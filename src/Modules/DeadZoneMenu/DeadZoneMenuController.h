// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IDeadZoneMenuItemObserver.h"
#include "IDeadZoneMenuItemObservable.h"
#include "DeadZoneMenuItemView.h"
#include "IDeadZoneMenuItemViewFactory.h"
#include <map>
#include <algorithm>
#include "IUIInteractionObservable.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            /*!
             * \brief Controller for a set of DeadZoneMenuItems.
             *
             */
            class DeadZoneMenuController : protected Eegeo::NonCopyable, public IDeadZoneMenuItemObserver
            {
            public:
                DeadZoneMenuController(IDeadZoneMenuItemObservable& deadZoneMenuItemObservable, IDeadZoneMenuItemViewFactory& viewFactory, IUIInteractionObservable& uiInteractionObservable
                                       , IUICameraProvider& uiCameraProvider);
                
                ~DeadZoneMenuController();
                
                void Update(float deltaTime);
                
                virtual void OnDeadZoneMenuItemAdded(DeadZoneMenuItem& deadZoneMenuItem);
                
                virtual void OnDeadZoneMenuItemRemoved(DeadZoneMenuItem& deadZoneMenuItem);
                
            protected:
                void PositionItems();
                
            private:
                IDeadZoneMenuItemObservable& m_deadZoneMenuItemRepository;
                IDeadZoneMenuItemViewFactory& m_viewFactory;
                IUIInteractionObservable& m_pIUIInteractionObservable;
                IUICameraProvider& m_uiCameraProvider;
                Eegeo::dv3 m_cachedCenter;
                Eegeo::dv3 m_cameraLastPosition;
                Eegeo::m33 m_cachedHeadTracker;
                bool m_isMenuShown;
                typedef std::map<DeadZoneMenuItem*, DeadZoneMenuItemView*> TViewsByModel;
                dv3 m_lastCameraPosition;
                TViewsByModel m_viewsByModel;
                
                DeadZoneMenuItemView* GetViewForModel(const DeadZoneMenuItem& di) const;
                
                bool HasViewForModel(const DeadZoneMenuItem& di) const;
                
            };
        }
    }
}