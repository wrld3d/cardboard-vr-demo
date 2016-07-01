// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "../UIQuad/UIQuadFactory.h"
#include "UIGazeView.h"

namespace Eegeo
{
    namespace UIGaze
    {
        UIGazeView::UIGazeView(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter)
        {
            Init(quadFactory, uiRenderableFilter);
        }
        
        void UIGazeView::Init(Eegeo::UI::IUIQuadFactory& quadFactory, UI::IUIRenderableFilter& uiRenderableFilter)
        {
            Eegeo::v2 dimension = Eegeo::v2(0.075f,0.075f)*3.f;
            m_pPointer = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter,
                                                       quadFactory.CreateUIQuad("mesh_example/gaze_point.png",
                                                                                dimension,
                                                                                Eegeo::v2::Zero(),
                                                                                Eegeo::v2::One(),
                                                                                Eegeo::Rendering::LayerIds::Values::AfterAll),
                                                       dimension);
        }
        
        UIGazeView::~UIGazeView()
        {
            Eegeo_DELETE m_pPointer;
        }
        
        void UIGazeView::Update(float dt)
        {
            m_pPointer->Update(dt);
        }
        
        void UIGazeView::SetEcefPosition(const dv3& position)
        {
            m_pPointer->SetEcefPosition(position);
        }
        
        
        void UIGazeView::ShowView()
        {
        }
        
        void UIGazeView::HideView()
        {
        }
        
        void UIGazeView::ResetProgress()
        {
        }
        
        
    }
}
