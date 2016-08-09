// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WelcomeNoteViewer.h"
#include "Logger.h"

namespace Examples
{
    WelcomeNoteViewer::WelcomeNoteViewer(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter)
    : m_quadFactory(quadFactory)
    , m_uiRenderableFilter(uiRenderableFilter)
    , m_pNote(NULL)
    {

    }

    WelcomeNoteViewer::~WelcomeNoteViewer()
    {
        if(m_pNote != NULL)
        {
            Eegeo_DELETE m_pNote;
            m_pNote = NULL;
        }
    }

    void WelcomeNoteViewer::Update(float dt)
    {
        if(m_pNote != NULL)
        {
            m_pNote->Update(dt);

            if (m_pNote->GetAlpha() <= 0.f)
            {
                Eegeo_DELETE m_pNote;
                m_pNote = NULL;
            }
        }
    }

    void WelcomeNoteViewer::SetPosition(const Eegeo::dv3& ecefPosition)
    {
        if(m_pNote != NULL)
        {
            m_pNote->SetEcefPosition(ecefPosition);
        }
    }

    void WelcomeNoteViewer::ShowWelcomeNote(const std::string &noteAssetPath, float fadeSpeed, const Eegeo::v2& dimension)
    {
        if(m_pNote != NULL)
        {
            Eegeo_DELETE m_pNote;
        }

        m_pNote = Eegeo_NEW(Eegeo::UI::UISprite)(m_uiRenderableFilter,
                                                    m_quadFactory.CreateUIQuad(noteAssetPath,
                                                                             dimension));
        m_pNote->SetFadeTransitionSpeed(fadeSpeed);
        m_pNote->SetItemShouldRender(false);
    }
}
