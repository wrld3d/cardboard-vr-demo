// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "UIRenderableFilter.h"
#include "RenderQueue.h"
#include "RenderContext.h"
#include "RenderCamera.h"
#include <algorithm>

namespace Eegeo
{
    namespace UI
    {
        UIRenderableFilter::~UIRenderableFilter()
        {
            m_renderables.clear();
        }
        
        void UIRenderableFilter::RegisterRenderable(IUIRenderable* pUIItemToRender)
        {
            m_renderables.push_back(pUIItemToRender);
        }
        
        void UIRenderableFilter::UnRegisterRenderable(IUIRenderable* pUIItemToRender)
        {
            std::vector<IUIRenderable*>::iterator position = std::find(m_renderables.begin(), m_renderables.end(), pUIItemToRender);
            if (position != m_renderables.end())
                m_renderables.erase(position);
        }
        
        void UIRenderableFilter::EnqueueRenderables(const Eegeo::Rendering::RenderContext& renderContext, Eegeo::Rendering::RenderQueue& renderQueue)
        {
            for (UIRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
            {
                IUIRenderable& uiRenderable = (**iter);
                if (uiRenderable.GetItemShouldRender())
                {
                    Eegeo::Rendering::RenderableBase& renderable = uiRenderable.GetUpdatedRenderable(renderContext);
                
                    if(renderable.GetEcefPosition().SquareDistanceTo(renderContext.GetRenderCamera().GetEcefLocation()) >= 1)
                        renderQueue.EnqueueRenderable(renderable);
                }
            }
        }
    }
}