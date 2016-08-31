// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#include "UISprite.h"

#include "UISprite.h"
#include "RenderingModule.h"
#include "IPlatformAbstractionModule.h"

namespace Eegeo
{
    namespace UI
    {
        
        UISprite::UISprite(IUIRenderableFilter& uiRenderableFilter
                           , UIQuad* pQuad
                           , const Eegeo::v2& size
                           , const Eegeo::dv3& ecefPosition
                           , const Eegeo::v3& scale
                           , const Eegeo::v4& color)
        : m_pQuad(pQuad)
        , m_UIRenderableFilter(uiRenderableFilter)
        , m_maxAlpha(1.f)
        , m_shouldDisplay(true)
        , m_fadeTransitionSpeed(1.f)
        , m_shouldFade(true)
        {
            m_Size = size;
            
            m_UIRenderableFilter.RegisterRenderable(m_pQuad);
            SetEcefPosition(ecefPosition);
            SetScale(scale);
            SetColor(color);
        }
        
        UISprite::~UISprite()
        {
            m_UIRenderableFilter.UnRegisterRenderable(m_pQuad);
            delete m_pQuad;
        }
        
        void UISprite::Update(float dt)
        {
            if (m_shouldFade)
            {
                float alpha = m_pQuad->GetAlpha();

                if (m_shouldDisplay && alpha < m_maxAlpha)
                {
                    m_pQuad->SetAlpha(alpha + (dt * m_fadeTransitionSpeed));
                }

                if (!m_shouldDisplay && alpha > 0.f)
                {
                    m_pQuad->SetAlpha(alpha - (dt * m_fadeTransitionSpeed));
                }

                m_pQuad->SetItemShouldRender(m_pQuad->GetAlpha() > 0.f);
            }
        }
        
        void UISprite::SetEcefPosition(const Eegeo::dv3& position)
        {
            m_pQuad->SetEcefPosition(position);
        }
        
        Eegeo::dv3 UISprite::GetEcefPosition()
        {
            return m_pQuad->GetEcefPosition();
        }
        
        void UISprite::SetSize(const Eegeo::v2& size)
        {
            m_Size = Eegeo::v2(size);
        }
        
        Eegeo::v2 UISprite::GetSize()
        {
            return m_Size;
        }
        
        void UISprite::SetColor(const Eegeo::v4& color)
        {
            m_pQuad->SetColor(color);
        }
        
        Eegeo::v4 UISprite::GetColor()
        {
            return m_pQuad->GetColor();
        }
        
        void UISprite::SetScale(const Eegeo::v3& scale)
        {
            m_pQuad->SetScale(scale);
        }
        
        Eegeo::v3 UISprite::GetScale()
        {
            return m_pQuad->GetScale();
        }
        
        bool UISprite::GetItemShouldRender()
        {
            if (m_shouldFade)
            {
                return m_shouldDisplay;
            }
            else
            {
                return m_pQuad->GetItemShouldRender();
            }
        }

        void UISprite::SetItemShouldRender(bool shouldDisplay)
        {
            if (m_shouldFade)
            {
                m_shouldDisplay = shouldDisplay;
            }
            else
            {
                return m_pQuad->SetItemShouldRender(shouldDisplay);
            }
        }

        void UISprite::SetAlpha(float alpha)
        {
            m_pQuad->SetAlpha(alpha);
        }

        const float UISprite::GetAlpha()
        {
            return m_pQuad->GetAlpha();
        }

        void UISprite::SetFadeTransitionSpeed(float speed)
        {
            m_fadeTransitionSpeed = speed;
        }

        void UISprite::SetMaxAlpha(float maxAlpha)
        {
            m_maxAlpha = maxAlpha;

            if (GetAlpha() > maxAlpha)
            {
                SetAlpha(maxAlpha);
            }
        }

        bool UISprite::GetShouldFade()
        {
            return m_shouldFade;
        }

        void UISprite::SetShouldFade(bool shouldFade)
        {
            m_shouldFade = shouldFade;
        }
    }
}
