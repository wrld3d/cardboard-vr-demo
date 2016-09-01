// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "InteriorMenu.h"
#include "InteriorMenuUIButton.h"
#include "../../UI/IUICameraProvider.h"
#include "UIQuad/IUIQuadFactory.h"
#include "Logger.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        /*!
         * \brief A view object representing a InteriorMenuItem in the world.
         *
         *  This class deals with the concerns of displaying a InteriorMenuItem.
         *
         */
        class InteriorMenuItemView : protected Eegeo::NonCopyable , public InteriorMenuUIButton
        {
        public:
            InteriorMenuItemView(InteriorMenuItem& interiorMenuItem
                                 , Eegeo::UI::IUIRenderableFilter& uiRenderableFilter
                                 , Eegeo::UI::IUIQuadFactory& quadFactory
                                 , const std::string& assetPath
                                 , const Eegeo::UI::UIProgressBarConfig& progressBarConfig
                                 , Eegeo::v2& dimension
                                 , Eegeo::v2& uvMin
                                 , Eegeo::v2& uvMax);
            
            /*! Retrieve the InteriorMenuItem model that the view represents.
             * \return The view's InteriorMenuItem model.
             */
            InteriorMenuItem& GetInteriorMenuItem() const
            {
                return m_interiorMenuItem;
            }
            
            virtual bool IsCollidingWithPoint(const Eegeo::v2& screenPoint, Eegeo::UI::IUICameraProvider& cameraProvider);
            virtual void OnItemClicked();
            
            
        private:
            InteriorMenuItem& m_interiorMenuItem;
        };
    }
}
