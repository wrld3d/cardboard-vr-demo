// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <vector>
#include <map>

#include "Interiors.h"
#include "Types.h"
#include "GlobeCamera.h"
#include "Rendering.h"
#include "IIdentity.h"
#include "InteriorsExplorer.h"
#include "IInteriorsExplorerModule.h"
#include "InteriorMenu/InteriorMenuModule.h"
#include "ICallback.h"

namespace InteriorsExplorer
{
    class InteriorsExplorerModule : public IInteriorsExplorerModule, private Eegeo::NonCopyable
    {
    public:
        
        InteriorsExplorerModule(  Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                , Eegeo::UI::IUIQuadFactory& uiQuadFactory
                                , Eegeo::UI::IUIInteractionObservable& uiInteractionObservable
                                , Eegeo::UI::IUICameraProvider& uiCameraProvider
                                , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                , Eegeo::Resources::Interiors::InteriorInteractionModel& interiorInteractionModel
                                , Eegeo::Resources::Interiors::InteriorSelectionModel& interiorSelectionModel
                                , Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel);
        
        ~InteriorsExplorerModule();
        
        
        void Update(float dt) const;
        
        virtual bool InteriorLoaded();
        virtual void SelectFloor(int floor);
        virtual void ShowInteriors();
        virtual void HideInteriors();
        void ToggleInteriorDisplay();
        
        void OnMenuItemGazed(InteriorMenu::InteriorMenuItem& menuItem);
        
    private:
        
        int floorId;
        
        typedef std::vector<InteriorMenu::InteriorMenuItem*> TInteriorMenuItems;
        TInteriorMenuItems  m_pInteriorMenuItems;
        
        InteriorMenu::InteriorMenuModule* m_pInteriorMenuModule;
        InteriorsExplorerModel* m_pModel;
        InteriorVisibilityUpdater* m_pVisibilityUpdater;
        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
        
        Eegeo::Helpers::TCallback1<InteriorsExplorerModule, InteriorMenu::InteriorMenuItem&> m_interiorMenuItemGazeCallback;
        
    };
}
