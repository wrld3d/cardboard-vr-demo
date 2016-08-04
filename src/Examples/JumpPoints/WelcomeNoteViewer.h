// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include "Types.h"
#include "UISprite.h"
#include "IUIQuadFactory.h"
#include "IUIRenderableFilter.h"

#include <string>

namespace Examples
{
    class WelcomeNoteViewer: protected Eegeo::NonCopyable
    {
    private:
        Eegeo::UI::IUIQuadFactory& m_quadFactory;
        Eegeo::UI::IUIRenderableFilter& m_uiRenderableFilter;
        Eegeo::UI::UISprite* m_pNote;
        float m_noteAplha;
        float m_fadeSpeed;
        Eegeo::v4 m_color;
        
    public:
        WelcomeNoteViewer(Eegeo::UI::IUIQuadFactory& quadFactory, Eegeo::UI::IUIRenderableFilter& uiRenderableFilter);
        ~WelcomeNoteViewer();

        void Update(float dt);
        void SetPosition(const Eegeo::dv3& ecefPosition);

        void ShowWelcomeNote(const std::string& noteAssetPath, float duration, const Eegeo::v2& dimension);
    };
}