// Copyright eeGeo Ltd (2012-2016), All Rights Reserved

#pragma once

#include "UIQuad.h"

namespace Eegeo
{
    namespace UI
    {
        class IUIQuadFactory
        {
        public:
            
            virtual UIQuad* CreateUIQuad(const std::string& assetPath,
                                 const Eegeo::v2& dimension,
                                 const Eegeo::v2& uvMin = Eegeo::v2::Zero(),
                                 const Eegeo::v2& uvMax = Eegeo::v2::One(),
                                 const Eegeo::Rendering::LayerIds::Values renderLayer = Eegeo::Rendering::LayerIds::Values::AfterWorld) = 0;
            
            virtual ~IUIQuadFactory(){};
        };
    }
}


