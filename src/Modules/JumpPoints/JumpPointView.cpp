// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "JumpPoint.h"
#include "JumpPointView.h"
#include "InteriorVisibilityUpdater.h"
#include "InteriorsExplorerModel.h"
#include "../UI/Animations/AnimationsController.h"
#include "../UI/Animations/IDv3Animateable.h"
#include "../UI/Animations/Dv3PropertyAnimation.h"
#include "../UI/Animations/AnimationEase.h"
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
                                         , Animations::AnimationsController& animationsController
                                         , Animations::IDv3Animateable& animateableCamera
                                         , Eegeo::Helpers::ICallback1<JumpPoint&>& onJumpPointSelected
                                         )
            : m_jumpPoint(jumpPoint)
            , m_uiCameraProvider(uiCameraProvider)
            , m_interiorsExplorerModule(interiorsExplorerModule)
            , m_jumpPointClickCallback(this, &JumpPointView::MoveCameraToJumpPoint)
            , m_animationsController(animationsController)
            , m_animateableCamera(animateableCamera)
            , m_onJumpPointSelected(onJumpPointSelected)
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
            {
                m_isCameraAnimating = false;
            }
            
            
            
            void JumpPointView::OnAnimationAdded(Animations::IAnimation& animation)
            {
                m_isCameraAnimating = true;
            }
            
            void JumpPointView::OnAnimationProgress(Animations::IAnimation& animation)
            {
            }
            
            void JumpPointView::OnAnimationRemoved(Animations::IAnimation& animation)
            {
                m_isCameraAnimating = false;
            }
            
            
            void JumpPointView::MoveCameraToJumpPoint()
            {
                
                if(m_isCameraAnimating)
                    return;
                
                if (m_jumpPoint.GetIsInInterior())
                {
                    
                    m_interiorsExplorerModule.SelectFloor(m_jumpPoint.GetInteriorFloor());
                    
                    if (m_interiorsExplorerModule.InteriorLoaded())
                    {
                        m_interiorsExplorerModule.ShowInteriors();
                        
                        m_animationsController.RemoveAnimationsForTag(0);
                        Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Animations::Dv3PropertyAnimation)(m_animateableCamera, NULL,m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), m_jumpPoint.GetEcefPosition(), 5.f, &AnimationEase::EaseInOutCubic);
                        animation->SetTag(0);
                        m_animationsController.AddAnimation(animation);
                    }
                }
                else
                {
                    if (m_interiorsExplorerModule.InteriorLoaded())
                    {
                        m_interiorsExplorerModule.HideInteriors();
                    }
                    
                    m_animationsController.RemoveAnimationsForTag(0);
                    Eegeo::UI::Animations::Dv3PropertyAnimation* animation = Eegeo_NEW(Animations::Dv3PropertyAnimation)(m_animateableCamera, NULL,m_uiCameraProvider.GetRenderCameraForUI().GetEcefLocation(), m_jumpPoint.GetEcefPosition(), 5.f, &AnimationEase::EaseInOutCubic);
                    animation->SetTag(0);
                    m_animationsController.AddAnimation(animation);
                }
                
                m_onJumpPointSelected(m_jumpPoint);
            }
            
        }
    }
}
