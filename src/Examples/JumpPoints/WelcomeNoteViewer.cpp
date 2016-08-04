// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "WelcomeNoteViewer.h"
#include "Logger.h"

namespace Examples
{
    WelcomeNoteViewer::WelcomeNoteViewer(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter)
    : m_quadFactory(quadFactory)
    , m_uiRenderableFilter(uiRenderableFilter)
    , m_pNote(NULL)
    , m_color(Eegeo::v4::One())
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
            m_noteAplha -= dt * m_fadeSpeed;

            if (m_noteAplha <= 0.f)
            {
                Eegeo_DELETE m_pNote;
                m_pNote = NULL;
            }
            else
            {
                m_color.SetW(m_noteAplha);
                m_pNote->SetColor(m_color);
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

        m_fadeSpeed = fadeSpeed;
        m_noteAplha = 1.f;

        m_pNote = Eegeo_NEW(Eegeo::UI::UISprite)(m_uiRenderableFilter,
                                                    m_quadFactory.CreateUIQuad(noteAssetPath,
                                                                             dimension));
    }
}
