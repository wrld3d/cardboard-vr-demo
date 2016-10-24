// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include <map>
#include <algorithm>

#include "Types.h"
#include "WorldMenu.h"
#include "WorldMenuItem.h"
#include "WorldMenuItemView.h"
#include "IWorldMenuItemObserver.h"
#include "IWorldMenuItemObservable.h"
#include "IWorldMenuItemViewFactory.h"
#include "IUIInteractionObservable.h"
#include "WorldMenuUpView.h"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            /*!
             * \brief Controller for a set of WorldMenuItems.
             *
             */
            class WorldMenuController : protected Eegeo::NonCopyable, public IWorldMenuItemObserver
            {
            public:
                WorldMenuController(IWorldMenuItemObservable& worldMenuItemObservable
                                    , IWorldMenuItemViewFactory& viewFactory
                                    , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                    , Eegeo::UI::IUICameraProvider& uiCameraProvider
                                    , Eegeo::UI::IUIQuadFactory& quadFactory
                                    , Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                    , std::string texture
                                    , int topSpriteID
                                    , int numTilesAlong1Axes);
                
                ~WorldMenuController();
                
                void Update(float deltaTime);
                
                virtual void OnWorldMenuItemAdded(WorldMenuItem& worldMenuItem);
                
                virtual void OnWorldMenuItemRemoved(WorldMenuItem& worldMenuItem);
                
                void SetMenuItemsShouldRender(bool menuItemsShouldRender);
                
                void SetSelectedMenuItemId(int menuItemId);
                
            protected:
                void PositionItems();
                
            private:
                
                WorldMenuUpView* m_pWorldMenuUpView;
                
                Eegeo::UI::UISprite* m_pSelectedArrow;
                IWorldMenuItemObservable& m_worldMenuItemRepository;
                IWorldMenuItemViewFactory& m_viewFactory;
                Eegeo::UI::IUIInteractionObservable& m_uiInteractionObservable;
                Eegeo::UI::IUICameraProvider& m_uiCameraProvider;
                Eegeo::dv3 m_cachedCenter;
                Eegeo::dv3 m_cameraLastPosition;
                Eegeo::m33 m_cachedHeadTracker;
                
                int m_menuItemId;
                bool m_isMenuShown;
                bool m_menuItemsShouldRender;
                typedef std::map<WorldMenuItem*, WorldMenuItemView*> TViewsByModel;
                Eegeo::dv3 m_lastCameraPosition;
                TViewsByModel m_viewsByModel;
                
                WorldMenuItemView* GetViewForModel(const WorldMenuItem& di) const;
                
                bool HasViewForModel(const WorldMenuItem& di) const;
            };
        }
    }
}
