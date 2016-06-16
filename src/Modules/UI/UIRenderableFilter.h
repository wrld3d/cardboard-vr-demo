// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "IRenderableFilter.h"
#include "IUIRenderableFilter.h"

#include <vector>

namespace Eegeo
{
    namespace UI
    {
        class UIRenderableFilter : public Eegeo::Rendering::IRenderableFilter, public IUIRenderableFilter
        {
        public:
            typedef std::vector<IUIRenderable*> UIRenderableVector;
            
            UIRenderableFilter(){}
            virtual ~UIRenderableFilter();
            
            // IUIRenderableFilter interface
            virtual void RegisterRenderable(IUIRenderable* p_UIItemToRender);
            virtual void UnRegisterRenderable(IUIRenderable* p_UIItemToRender);
            
            // IRenderableFilter interface
            void EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue);
            
        private:
            UIRenderableVector m_renderables;
        };
        
    }
}
