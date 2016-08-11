// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "WorldMenu.h"
#include "WorldMenuUIButton.h"
#include "../../UI/IUICameraProvider.h"
#include "UIQuad/IUIQuadFactory.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            /*!
             * \brief A view object representing a WorldMenuItem in the world.
             *
             *  This class deals with the concerns of displaying a WorldMenuItem.
             *
             */
            class WorldMenuItemView : protected Eegeo::NonCopyable , public WorldMenuUIButton
            {
            public:
                WorldMenuItemView(WorldMenuItem& worldMenuItem
                                     , Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                     , Eegeo::UI::IUIQuadFactory& quadFactory
                                     , const std::string& assetPath
                                     , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                     , Eegeo::v2& dimension
                                     , Eegeo::v2& uvMin
                                     , Eegeo::v2& uvMax);
                
                /*! Retrieve the WorldMenuItem model that the view represents.
                 * \return The view's WorldMenuItem model.
                 */
                WorldMenuItem& GetWorldMenuItem() const
                {
                    return m_WorldMenuItem;
                }
                
                virtual bool IsCollidingWithPoint(const Eegeo::v2& screenPoint, Eegeo::UI::IUICameraProvider& cameraProvider);
                virtual void OnItemClicked();
                
                
            private:
                WorldMenuItem& m_WorldMenuItem;
            };
        }
    }
}
