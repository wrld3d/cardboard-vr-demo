// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "JumpPoints.h"
#include "../UI/UIImageButton.h"
#include "../UI/UIImageButtonClickedCallback.h"
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
            class JumpPointView : protected Eegeo::NonCopyable , UIImageButton
            {
            public:
                /*! Create a new JumpPointView with a given sprite.
                 * \param jumpPoint The JumpPoint model that the view represents.
                 * \param modelVertexBounds the bounds of the JumpPoint in model space (this should typically be a bounds with x, y size, but with the z component set to 0)
                 */
                JumpPointView(JumpPoint& jumpPoint
                              , Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                              , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                              , const std::string& fileName
                              , const Eegeo::v2& p_Dimension
                              , const Eegeo::v2& p_uvMin = Eegeo::v2::Zero()
                              , const Eegeo::v2& p_uvMax = Eegeo::v2::One()
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
                TUIImageButtonClickedCallback<JumpPointView> m_JumpPointClickCallback;
            };
        }
    }
}
