// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "DeadZoneMenu.h"
#include "../UI/UIProgressButton.h"
#include "../UI/IUICameraProvider.h"
#include "UIQuad/IUIQuadFactory.h"

namespace Eegeo
{
    namespace UI
    {
        namespace DeadZoneMenu
        {
            /*!
             * \brief A view object representing a DeadZoneMenuItem in the world.
             *
             *  This class deals with the concerns of displaying a DeadZoneMenuItem.
             *
             */
            class DeadZoneMenuItemView : protected Eegeo::NonCopyable , public UIProgressButton
            {
            public:
                DeadZoneMenuItemView(DeadZoneMenuItem& deadZoneMenuItem
                                     , IUIRenderableFilter& uiRenderableFilter
                                     , Eegeo::UI::IUIQuadFactory& quadFactory
                                     , const std::string& assetPath
                                     , const UIProgressBarConfig& progressBarConfig
                                     , Eegeo::v2& dimension
                                     , Eegeo::v2& uvMin
                                     , Eegeo::v2& uvMax);
                
                /*! Retrieve the DeadZoneMenuItem model that the view represents.
                 * \return The view's DeadZoneMenuItem model.
                 */
                DeadZoneMenuItem& GetDeadZoneMenuItem() const
                {
                    return m_deadZoneMenuItem;
                }
                
            private:
                DeadZoneMenuItem& m_deadZoneMenuItem;
            };
        }
    }
}
