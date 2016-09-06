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
                Eegeo::v2 size(6,6);
                Eegeo::v2 outMin;
                Eegeo::v2 outMax;
                Eegeo::UI::CalculateUV(size, 21, outMin, outMax);

                Eegeo::v2 dimension = Eegeo::v2(9.f,9.f);
                m_pPointer = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter,
                                                            quadFactory.CreateUIQuad("mesh_example/PinIconTexturePage.png",
                                                                                     dimension,
                                                                                     outMin,
                                                                                     outMax,
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
