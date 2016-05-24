// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Types.h"
#include "IJumpPointViewFactory.h"
#include "LayerIds.h"
#include "JumpPoint.h"
#include "Bounds.h"
#include "JumpPointView.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            class JumpPointViewFactory : protected Eegeo::NonCopyable, public IJumpPointViewFactory
            {
            public:
                JumpPointViewFactory(Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                                     , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                                     , IUICameraProvider& p_UICameraProvider
                                     , const std::string& p_FileName
                                     , const Eegeo::v2& p_Dimension);
                
                ~JumpPointViewFactory();
                
                virtual JumpPointView* CreateViewForJumpPoint(JumpPoint& jumpPointModel);
                
            private:
                Eegeo::Modules::Core::RenderingModule& m_RenderingModule;
                Modules::IPlatformAbstractionModule& m_PlatformAbstractionModule;
                IUICameraProvider& m_UICameraProvider;
                const std::string m_FileName;
                const Eegeo::v2 m_Dimension;
            };
        }
    }
}
