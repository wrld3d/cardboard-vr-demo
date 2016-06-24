//
//  JumpPoint.cpp
//  SDKSamplesApp
//
//  Created by Ali on 5/19/16.
//
//

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
                                         , UIQuad* pQuad
                                         , IUICameraProvider& uiCameraProvider
                                         , InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule
                                         )
            : m_jumpPoint(jumpPoint)
            , m_uiCameraProvider(uiCameraProvider)
            , m_interiorsExplorerModule(interiorsExplorerModule)
            , m_jumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , UIImageButton(uiRenderableFilter
                            , pQuad
                            , m_jumpPointClickCallback
                            , jumpPoint.GetDimensions()
                            , jumpPoint.GetEcefPosition())
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
