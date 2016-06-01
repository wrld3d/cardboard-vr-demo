//
//  UIAnimatedQuad.cpp
//  SDKSamplesApp
//
//  Created by Aqif Hamid on 5/24/16.
//
//

#include "UIAnimatedSprite.h"
#include "RenderingModule.h"
#include "EegeoWorld.h"
#include "Logger.h"

namespace Eegeo
{
    namespace UI
    {
        
        UIAnimatedSprite::UIAnimatedSprite(Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                         , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                         , const std::string& p_SpriteSheetName
                         , const Eegeo::dv3& p_EcefPosition
                         , const Eegeo::v2& p_Dimension
                         , Eegeo::Helpers::ICallback0& p_OnClickedEvent
                         , Eegeo::v2& p_FramesGridSize
                         , float p_FrameRate
        ):
        m_FramesGridSize(p_FramesGridSize),
        m_FrameRate(p_FrameRate),
        m_OnClickedEvent(p_OnClickedEvent)
        {
            m_TimeElapsed = 0;
            m_CurrentFrameNumber = 0;
            
            m_Quad = Eegeo_NEW(Eegeo::UI::UIQuad)(p_RenderingModule,
                                                            p_RenderingModule.GetGlBufferPool(),
                                                            p_RenderingModule.GetVertexBindingPool(),
                                                            p_RenderingModule.GetVertexLayoutPool(),
                                                            p_PlatformAbstractionModule.GetTextureFileLoader(),
                                                            p_RenderingModule.GetRenderableFilters(),
                                                            p_SpriteSheetName,
                                                            p_EcefPosition,
                                                            p_Dimension,
                                                            Eegeo::v2::Zero(),
                                                            Eegeo::v2(1.f/m_FramesGridSize.GetX(), 1.f/m_FramesGridSize.GetY()),
                                                            Eegeo::v4::One(),
                                                            Eegeo::Rendering::LayerIds::Values::AfterAll
                                                         );
            
            m_Radius = (p_Dimension.x > p_Dimension.y ? p_Dimension.x : p_Dimension.y)/2.0f;
        }
        
        UIAnimatedSprite::~UIAnimatedSprite(){
            Eegeo_DELETE m_Quad;
        }
        
        void UIAnimatedSprite::Reset()
        {
            m_TimeElapsed = 0.0f;
            m_CurrentFrameNumber = 0;
        }
        
        void UIAnimatedSprite::SetScale(Eegeo::v3 p_scale) {
            m_Quad->SetScale(p_scale);
            m_scale = p_scale;
        }
        
        void UIAnimatedSprite::Update(float dt)
        {
            m_TimeElapsed += dt;
            if(m_TimeElapsed>(1.0f/m_FrameRate)){
                
                m_TimeElapsed = 0.0f;
                
                m_CurrentFrameNumber+=1;
                
                if(m_CurrentFrameNumber>=(int) (m_FramesGridSize.GetX()*m_FramesGridSize.GetY()))
                    m_CurrentFrameNumber = 0;
                
                int x = m_CurrentFrameNumber % ((int) m_FramesGridSize.GetX());
                int y = m_CurrentFrameNumber / ((int) m_FramesGridSize.GetY());
                float xSize = 1.f/m_FramesGridSize.GetX();
                float ySize = 1.f/m_FramesGridSize.GetY();
                                
                Eegeo::v2 min(x*xSize, y*ySize);
                Eegeo::v2 max((x+1)*xSize, (y+1)*ySize);
                m_Quad->UpdateUVs(min, max);
                m_Quad->SetScale(m_scale);
                
            }
            
            
        }
        
        void UIAnimatedSprite::OnItemClicked()
        {
            m_OnClickedEvent();
        }
        
        void UIAnimatedSprite::OnFocusGained()
        {
            m_Quad->SetScale(Eegeo::v3::One() * 1.1f);
        }
        
        void UIAnimatedSprite::OnFocusLost()
        {
            m_Quad->SetScale(Eegeo::v3::One());
        }
        
    }
}