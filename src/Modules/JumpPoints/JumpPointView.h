// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "ICallback.h"
#include "Types.h"
#include "VectorMath.h"
#include "Bounds.h"
#include "JumpPoints.h"
#include "../UI/UIImageButton.h"
#include "../UI/IUICameraProvider.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            class JumpPointView : public UIImageButton
            {
            public:
                JumpPointView(JumpPoint& jumpPoint
                              , UIQuad* quad
                              , IUICameraProvider& p_UICameraProvider);
                
                virtual ~JumpPointView(){}
                
                JumpPoint& GetJumpPoint() const;
                
               
                void MoveCameraToJumpPoint();
                
            private:
                JumpPoint& m_JumpPoint;
                IUICameraProvider& m_UICameraProvider;
                Eegeo::Helpers::TCallback0<JumpPointView> m_JumpPointClickCallback;
            };
        }
    }
}
