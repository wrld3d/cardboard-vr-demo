// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "WorldMenuUpView.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        namespace WorldMenu
        {
            WorldMenuUpView::WorldMenuUpView(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter)
            {
                Init(quadFactory, uiRenderableFilter);
            }
            
            void WorldMenuUpView::Init(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter)
            {
                Eegeo::v2 dimension = Eegeo::v2(9.f,9.f);
                m_pPointer = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter,
                                                            quadFactory.CreateUIQuad("mesh_example/PinIconTexturePage",
                                                                                     dimension,
                                                                                     Eegeo::v2(1.f/5.f, 4.f/5.f),
                                                                                     Eegeo::v2(2.f/5.f, 1.f),
                                                                                     Eegeo::Rendering::LayerIds::Values::AfterAll),
                                                            dimension);
                m_isShown = true;
                m_pPointer->SetItemShouldRender(m_isShown);
                m_pPointer->SetMaxAlpha(0.6f);
            }
            
            WorldMenuUpView::~WorldMenuUpView()
            {
                Eegeo_DELETE m_pPointer;
            }
            
            void WorldMenuUpView::Update(float dt)
            {
                m_pPointer->Update(dt);
            }
            
            void WorldMenuUpView::SetEcefPosition(const Eegeo::dv3& position)
            {
                m_pPointer->SetEcefPosition(position);
            }
            
            void WorldMenuUpView::ShowView()
            {
                if(!m_isShown)
                {
                    m_isShown = true;
                    m_pPointer->SetItemShouldRender(m_isShown);
                }
            }
            
            void WorldMenuUpView::HideView()
            {
                if(m_isShown)
                {
                    m_isShown = false;
                    m_pPointer->SetItemShouldRender(m_isShown);
                }
            }
        }
    }
}
