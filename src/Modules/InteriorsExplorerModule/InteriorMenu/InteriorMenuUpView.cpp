// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "InteriorMenuUpView.h"
#include "Logger.h"

namespace InteriorsExplorer
{
    namespace InteriorMenu
    {
        InteriorMenuUpView::InteriorMenuUpView(Eegeo::UI::IUIQuadFactory& quadFactory,
                                               Eegeo::UI::IUIRenderableFilter& uiRenderableFilter,
                                               std::string texture,
                                               int spriteID,
                                               int numTilesAlong1Axes)
        {
            Init(quadFactory, uiRenderableFilter, texture, spriteID, numTilesAlong1Axes);
        }
        
        void InteriorMenuUpView::Init(Eegeo::UI::IUIQuadFactory& quadFactory,
                                      Eegeo::UI::IUIRenderableFilter& uiRenderableFilter,
                                      std::string texture,
                                      int spriteID,
                                      int numTilesAlong1Axes)
        {
            
            Eegeo::v2 size(numTilesAlong1Axes,numTilesAlong1Axes);
            Eegeo::v2 outMin;
            Eegeo::v2 outMax;
            Eegeo::UI::CalculateUV(size, spriteID, outMin, outMax);

            Eegeo::v2 dimension = Eegeo::v2(9.f,9.f);
            m_pPointer = Eegeo_NEW(Eegeo::UI::UISprite)(uiRenderableFilter,
                                                        quadFactory.CreateUIQuad(texture,
                                                                                 dimension,
                                                                                 outMin,
                                                                                 outMax,
                                                                                 Eegeo::Rendering::LayerIds::Values::AfterAll),
                                                        dimension);
            m_isShown = true;
            m_pPointer->SetItemShouldRender(m_isShown);
            m_pPointer->SetMaxAlpha(0.6f);
        }
        
        InteriorMenuUpView::~InteriorMenuUpView()
        {
            Eegeo_DELETE m_pPointer;
        }
        
        void InteriorMenuUpView::Update(float dt)
        {
            m_pPointer->Update(dt);
        }
        
        void InteriorMenuUpView::SetEcefPosition(const Eegeo::dv3& position)
        {
            m_pPointer->SetEcefPosition(position);
        }
        
        void InteriorMenuUpView::ShowView()
        {
            if(!m_isShown)
            {
                m_isShown = true;
                m_pPointer->SetItemShouldRender(m_isShown);
            }
        }
        
        void InteriorMenuUpView::HideView()
        {
            if(m_isShown)
            {
                m_isShown = false;
                m_pPointer->SetItemShouldRender(m_isShown);
            }
        }
        
    }
}
