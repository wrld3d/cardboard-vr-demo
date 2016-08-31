// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once



namespace Eegeo
{
    namespace UI
    {
        struct UIProgressBarConfig
        {
            std::string textureFilename;
            float frameRate;
            Eegeo::v2 spriteGridSize;
            int spriteId;
            Eegeo::v2 size;
            Eegeo::dv3 ecefPosition;
            Eegeo::v3 scale;
            Eegeo::v4 color;
            Eegeo::Rendering::LayerIds::Values renderLayer;
            
            UIProgressBarConfig()
            : frameRate(0.f)
            , spriteGridSize(Eegeo::v2::One())
            , spriteId(0)
            , size(Eegeo::v2::One())
            , ecefPosition(Eegeo::dv3::Zero())
            , scale(Eegeo::v3::Zero())
            , color(Eegeo::v4::One())
            , renderLayer(Eegeo::Rendering::LayerIds::Values::AfterAll)
            {
                
            }
        };
        
    }
}


