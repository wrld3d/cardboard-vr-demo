// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "JumpPoints.h"
#include "../UI/UIImageButton.h"
#include "../UI/IUICameraProvider.h"

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
            class JumpPointView : protected Eegeo::NonCopyable , public UIImageButton
            {
            public:
                JumpPointView(JumpPoint& jumpPoint
                              , UIQuad* quad
                              , IUICameraProvider& p_UICameraProvider
                              );
                
                /*! Retrieve the JumpPoint model that the view represents.
                 * \return The view's JumpPoint model.
                 */
                JumpPoint& GetJumpPoint() const;
                
                /*! Move the render camera to jump point.
                 * \param The color vector to apply to the JumpPoint.
                 */
                void MoveCameraToJumpPoint();
                
            private:
                JumpPoint& m_JumpPoint;
                IUICameraProvider& m_UICameraProvider;
                Eegeo::Helpers::TCallback0<JumpPointView> m_JumpPointClickCallback;
            };
        }
    }
}
