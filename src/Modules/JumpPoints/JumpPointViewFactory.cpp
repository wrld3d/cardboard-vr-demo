// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointViewFactory.h"
#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            
            JumpPointViewFactory::JumpPointViewFactory(Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                                                       , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                                                       , IUICameraProvider& p_UICameraProvider)
            : m_RenderingModule(p_RenderingModule)
            , m_PlatformAbstractionModule(p_PlatformAbstractionModule)
            , m_UICameraProvider(p_UICameraProvider)
            {
                
            }
            
            JumpPointViewFactory::~JumpPointViewFactory()
            {
                
            }
            
            JumpPointView* JumpPointViewFactory::CreateViewForJumpPoint(JumpPoint& jumpPointModel)
            {
                
                JumpPointView* jumpPointView = Eegeo_NEW(JumpPointView)(jumpPointModel
                                                                        , m_RenderingModule
                                                                        , m_PlatformAbstractionModule
                                                                        , m_UICameraProvider
                                                                        );
                return jumpPointView;
            }
            
        }
    }
}
