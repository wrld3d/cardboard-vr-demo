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
                                , Eegeo::Resources::Interiors::InteriorTransitionModel& interiorTransitionModel
                                , const std::string& menuTextureFileName
                                , int numberOfTilesAlong1Axis);
        
        ~InteriorsExplorerModule();
        
        
        void Update(float dt) const;
        
        virtual void ForceEnterInterior(int floorId);
        virtual void ForceLeaveInterior();
        
        virtual void SelectInterior(std::string);
        virtual std::string GetSelectedInteriorID() const;
        virtual bool InteriorLoaded();
        virtual void SelectFloor(int floor, bool shouldAnimate);
        virtual int GetSelectedFloor() const;
        virtual void ShowInteriors();
        virtual void HideInteriors();
        virtual bool IsInteriorVisible();
        void ToggleInteriorDisplay();

        virtual void RegisterVisibilityChangedCallback(Eegeo::Helpers::ICallback0& callback);
        virtual void UnregisterVisibilityChangedCallback(Eegeo::Helpers::ICallback0& callback);
        
        void OnMenuItemGazed(InteriorMenu::InteriorMenuItem& menuItem);

        virtual void RegisterMenuItemGazedCallback(Eegeo::Helpers::ICallback1<InteriorMenu::InteriorMenuItem&>& callback);
        virtual void UnregisterMenuItemGazedCallback(Eegeo::Helpers::ICallback1<InteriorMenu::InteriorMenuItem&>& callback);

        virtual void RegisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback);
        virtual void UnregisterInteriorAnimationCallback(Eegeo::Helpers::ICallback1<InteriorsExplorerFloorAnimationState>& callback);

        virtual void SetMenuVisibilityThresholdAngle(float angle);
        virtual float GetMenuVisibilityThresholdAngle();

        virtual void SetShouldShowExitButton(bool shouldShowExitButton);
        
    private:
        
        int m_floorId;
        
        Eegeo::Helpers::TCallback1<InteriorsExplorerModule, InteriorMenu::InteriorMenuItem&> m_interiorMenuItemGazeCallback;
        Eegeo::Helpers::CallbackCollection1<InteriorMenu::InteriorMenuItem&> m_menuItemCallbacks;

        typedef std::vector<InteriorMenu::InteriorMenuItem*> TInteriorMenuItems;
        TInteriorMenuItems  m_interiorMenuItems;
        
        InteriorMenu::InteriorMenuModule* m_pInteriorMenuModule;
        InteriorsExplorerModel* m_pModel;
        InteriorVisibilityUpdater* m_pVisibilityUpdater;
        Eegeo::Resources::Interiors::InteriorInteractionModel& m_interiorInteractionModel;
        Eegeo::Resources::Interiors::InteriorSelectionModel& m_interiorSelectionModel;
        Eegeo::Resources::Interiors::InteriorTransitionModel& m_interiorTransitionModel;
    };
}
