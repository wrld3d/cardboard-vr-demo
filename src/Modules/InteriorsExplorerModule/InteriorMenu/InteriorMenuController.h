// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>
#include <algorithm>

#include "Types.h"
#include "InteriorMenu.h"
#include "InteriorMenuItem.h"
#include "InteriorMenuItemView.h"
#include "IInteriorMenuItemObserver.h"
#include "IInteriorMenuItemObservable.h"
#include "IInteriorMenuItemViewFactory.h"
#include "IUIInteractionObservable.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        /*!
         * \brief Controller for a set of InteriorMenuItems.
         *
         */
        class InteriorMenuController : protected Eegeo::NonCopyable, public IInteriorMenuItemObserver
        {
        public:
            InteriorMenuController(IInteriorMenuItemObservable& InteriorMenuItemObservable, IInteriorMenuItemViewFactory& viewFactory, Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                   , Eegeo::UI::IUICameraProvider& uiCameraProvider);
            
            ~InteriorMenuController();
            
            void Update(float deltaTime);
            
            virtual void OnInteriorMenuItemAdded(InteriorMenuItem& InteriorMenuItem);
            
            virtual void OnInteriorMenuItemRemoved(InteriorMenuItem& InteriorMenuItem);
            
            void SetMenuItemsShouldRender(bool menuItemsShouldRender);
            
            void SetSelectedFloorId(int floorId);
            
        protected:
            void PositionItems();
            
        private:
            IInteriorMenuItemObservable& m_InteriorMenuItemRepository;
            IInteriorMenuItemViewFactory& m_viewFactory;
            Eegeo::UI::IUIInteractionObservable& m_pIUIInteractionObservable;
            Eegeo::UI::IUICameraProvider& m_uiCameraProvider;
            Eegeo::dv3 m_cachedCenter;
            Eegeo::dv3 m_cameraLastPosition;
            Eegeo::m33 m_cachedHeadTracker;
            
            int m_floorId;
            bool m_isMenuShown;
            bool m_menuItemsShouldRender;
            typedef std::map<InteriorMenuItem*, InteriorMenuItemView*> TViewsByModel;
            Eegeo::dv3 m_lastCameraPosition;
            TViewsByModel m_viewsByModel;
            
            InteriorMenuItemView* GetViewForModel(const InteriorMenuItem& di) const;
            
            bool HasViewForModel(const InteriorMenuItem& di) const;
        };
    }
}