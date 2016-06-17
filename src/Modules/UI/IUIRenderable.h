// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "RenderableBase.h"

namespace Eegeo
{
    namespace UI
    {
        /*!
         * \brief Interface for providing renderable items that are used by UI.
         *
         * This interface is used for renderable items that are used by UI.
         */
        class IUIRenderable
        {
        public:
            virtual Eegeo::Rendering::RenderableBase& GetUpdatedRenderable(const Eegeo::Rendering::RenderContext& renderContext) = 0;
            
            virtual ~IUIRenderable(){};
            
            virtual bool GetItemShouldRender(){ return m_shouldRender; }
            virtual void SetItemShouldRender(bool shouldRender){ m_shouldRender = shouldRender; }
            
        private:
            bool m_shouldRender;
        };
    }
}

