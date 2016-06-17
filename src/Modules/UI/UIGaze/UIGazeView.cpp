//
//  UIGazeView.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/25/16.
//
//

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
            Eegeo::v2 dimension = Eegeo::v2(0.25f,0.25f)*7.f;
            m_pGazeProgress = Eegeo_NEW(Eegeo::UI::UIAnimatedSprite)(uiRenderableFilter,
                                                                    quadFactory,
                                                                    "mesh_example/gaze_loader.png",
                                                                    49.f/2.f,
                                                                    Eegeo::v2(7,7),
                                                                    0,
                                                                    dimension);
            
            dimension = Eegeo::v2(0.075f,0.075f)*3.f;
            m_pPointer = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter,
                                                       quadFactory.CreateUIQuad("mesh_example/gaze_point.png",
                                                                                dimension,
                                                                                Eegeo::v2::Zero(),
                                                                                Eegeo::v2::One(),
                                                                                Eegeo::v3::One(),
                                                                                Eegeo::v4::One(),
                                                                                Eegeo::Rendering::LayerIds::Values::AfterAll),
                                                       dimension);
        }
        
        UIGazeView::~UIGazeView()
        {
            Eegeo_DELETE m_pGazeProgress;
            Eegeo_DELETE m_pPointer;
        }
        
        void UIGazeView::Update(float dt)
        {
            m_pGazeProgress->Update(dt);
            m_pPointer->Update(dt);
        }
        
        void UIGazeView::SetEcefPosition(const dv3& position)
        {
            m_pGazeProgress->SetEcefPosition(position);
            m_pPointer->SetEcefPosition(position);
        }
        
        
        void UIGazeView::ShowView()
        {
            m_pGazeProgress->SetScale(v3::One());
        }
        
        void UIGazeView::HideView()
        {
            m_pGazeProgress->SetScale(v3::Zero());
            m_pGazeProgress->Reset();
        }
        
        void UIGazeView::ResetProgress()
        {
            m_pGazeProgress->Reset();
        }
        
        
    }
}
