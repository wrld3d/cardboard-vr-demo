// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "JumpPoint.h"
#include "JumpPointView.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModel.h"
namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            JumpPointView::JumpPointView(JumpPoint& jumpPoint
                                         , IUIRenderableFilter& uiRenderableFilter
                                         , Eegeo::UI::IUIQuadFactory& quadFactory
                                         , const UIProgressBarConfig& progressBarConfig
                                         , IUICameraProvider& uiCameraProvider
                                         , InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule
                                         )
            : m_jumpPoint(jumpPoint)
            , m_uiCameraProvider(uiCameraProvider)
            , m_interiorsExplorerModule(interiorsExplorerModule)
            , m_jumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , UIProgressButton(uiRenderableFilter
                            , quadFactory
                            , jumpPoint.GetFileName()
                            , progressBarConfig
                            , m_jumpPointClickCallback
                            , jumpPoint.GetDimensions()
                            , jumpPoint.GetEcefPosition()
                            , Eegeo::v3::One()
                            , jumpPoint.GetColor()
                            , jumpPoint.GetUVMin()
                            , jumpPoint.GetUVMax()
                            )
            {}
            
            void JumpPointView::MoveCameraToJumpPoint()
            {
                InteriorsExplorer::InteriorVisibilityUpdater& visibilityUpdater = m_interiorsExplorerModule.GetInteriorVisibilityUpdater();
                
                if (m_jumpPoint.GetIsInInterior())
                {
                    m_interiorsExplorerModule.GetInteriorsExplorerModel().SelectFloor(m_jumpPoint.GetInteriorFloor());
                    if (visibilityUpdater.GetInteriorHasLoaded()) {
                        visibilityUpdater.SetInteriorShouldDisplay(true);
                        visibilityUpdater.UpdateVisiblityImmediately();
                        m_uiCameraProvider.GetRenderCameraForUI().SetEcefLocation(m_jumpPoint.GetEcefPosition());
                    }
                }
                else
                {
                    if (visibilityUpdater.GetInteriorShouldDisplay())
                    {
                        visibilityUpdater.SetInteriorShouldDisplay(false);
                        visibilityUpdater.UpdateVisiblityImmediately();
                    }
                    
                    m_uiCameraProvider.GetRenderCameraForUI().SetEcefLocation(m_jumpPoint.GetEcefPosition());
                }
            }
            
        }
    }
}
