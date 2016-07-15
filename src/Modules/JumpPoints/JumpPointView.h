// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "JumpPoints.h"
#include "../UI/UIProgressButton.h"
#include "../UI/IUICameraProvider.h"
#include "IInteriorsExplorerModule.h"
#include "UIQuad/IUIQuadFactory.h"
#include "../UI/Animations/AnimationsController.h"
#include "../UI/Animations/IDv3Animateable.h"
#include "../UI/Animations/IAnimationObserver.h"
#include "../UI/Animations/IAnimation.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            /*!
             * \brief A view object representing a JumpPoint in the world.
             *
             *  This class deals with the concerns of displaying a JumpPoint.
             *
             */
            class JumpPointView : public Eegeo::UI::UIProgressButton, public Animations::IAnimationObserver
            {
            public:
                JumpPointView(JumpPoint& jumpPoint
                              , IUIRenderableFilter& uiRenderableFilter
                              , Eegeo::UI::IUIQuadFactory& quadFactory
                              , const UIProgressBarConfig& progressBarConfig
                              , IUICameraProvider& uiCameraProvider
                              , InteriorsExplorer::IInteriorsExplorerModule& interiorsExplorerModule
                              , Animations::AnimationsController& animationsController
                              , Animations::IDv3Animateable& animateableCamera);

                virtual ~JumpPointView(){}
                
	         /*! Retrieve the JumpPoint model that the view represents.
                 * \return The view's JumpPoint model.
                 */
                JumpPoint& GetJumpPoint() const;
                
                /*! Move the render camera to jump point.
                 * \param The color vector to apply to the JumpPoint.
                 */
                void MoveCameraToJumpPoint();
                
                virtual void OnAnimationAdded(Animations::IAnimation& animation);
                virtual void OnAnimationProgress(Animations::IAnimation& animation);
                virtual void OnAnimationRemoved(Animations::IAnimation& animation);
                
            private:
                
                JumpPoint& m_jumpPoint;
                IUICameraProvider& m_uiCameraProvider;
                InteriorsExplorer::IInteriorsExplorerModule& m_interiorsExplorerModule;
                Eegeo::Helpers::TCallback0<JumpPointView> m_jumpPointClickCallback;
                Animations::AnimationsController& m_animationsController;
                Animations::IDv3Animateable& m_animateableCamera;
                
                bool m_isCameraAnimating;
                
            };
        }
    }
}
