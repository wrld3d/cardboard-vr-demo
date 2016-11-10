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
        bool OrderBySecondDescending(const std::pair<Eegeo::Rendering::RenderableBase*, float>& a, const std::pair<Eegeo::Rendering::RenderableBase*, float>& b)
        {
            return a.second > b.second;
        }

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
            typedef std::vector<std::pair<Eegeo::Rendering::RenderableBase*, float> > RenderablDepthPairVector;
            RenderablDepthPairVector renderableDepthPairs;

            for (UIRenderableVector::const_iterator iter = m_renderables.begin(); iter != m_renderables.end(); ++iter)
            {
                IUIRenderable& uiRenderable = (**iter);
                if (uiRenderable.GetItemShouldRender())
                {
                    Eegeo::Rendering::RenderableBase& renderable = uiRenderable.GetUpdatedRenderable(renderContext);

                    const float squareDrawDistance = renderable.GetEcefPosition().SquareDistanceTo(renderContext.GetRenderCamera().GetEcefLocation());
                    if( squareDrawDistance >= 1)
                    {
                        renderableDepthPairs.emplace_back(&renderable, squareDrawDistance);
                    }
                }
            }

            std::sort(renderableDepthPairs.begin(), renderableDepthPairs.end(), OrderBySecondDescending);
                
            u64 depthKey = 0;
                
            for (RenderablDepthPairVector::const_iterator iter = renderableDepthPairs.begin();
                    iter != renderableDepthPairs.end();
                    ++iter, ++depthKey)
            {
                Eegeo::Rendering::RenderableBase* renderable = iter->first;
                renderable->SetDepth(depthKey);
                renderQueue.EnqueueRenderable(renderable);
            }
        }
    }
}
