//
//  IUICameraProvider.h
//  SDKSamplesApp
//
//  Created by Ali on 5/16/16.
//
//

#pragma once

#include "RenderCamera.h"

namespace Eegeo
{
    namespace UI
    {
        /*!
         * \brief Interface for providing camera that is used by UI.
         *
         * This interface is used for providing camera that is used by UI.
         */
        class IUICameraProvider
        {
        public:
            virtual Eegeo::Camera::RenderCamera& GetRenderCameraForUI() = 0;
            virtual const Eegeo::m33& GetOrientation() = 0;
            virtual const Eegeo::m33& GetBaseOrientation() = 0;
            virtual const Eegeo::m33& GetHeadTrackerOrientation() = 0;
            virtual ~IUICameraProvider(){};
        };
        
    }
}

