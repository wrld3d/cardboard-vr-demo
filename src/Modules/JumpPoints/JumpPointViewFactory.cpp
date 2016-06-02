// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "JumpPointViewFactory.h"
#include "VectorMath.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            
            JumpPointViewFactory::JumpPointViewFactory(IUIQuadFactory& p_IUIQuadFactory
                                                       , IUICameraProvider& p_UICameraProvider)
            : m_IUIQuadFactory(p_IUIQuadFactory)
            , m_UICameraProvider(p_UICameraProvider)
            {
                
            }
            
            JumpPointViewFactory::~JumpPointViewFactory()
            {
                
            }
            
            JumpPointView* JumpPointViewFactory::CreateViewForJumpPoint(JumpPoint& jumpPointModel)
            {
                
                JumpPointView* jumpPointView = Eegeo_NEW(JumpPointView)(jumpPointModel
                                                                        , m_IUIQuadFactory.CreateUIQuad(jumpPointModel.GetFileName()
                                                                                                        , jumpPointModel.GetDimensions()
                                                                                                        , jumpPointModel.GetUVMin()
                                                                                                        , jumpPointModel.GetUVMax()
                                                                                                        , jumpPointModel.GetEcefPosition()
                                                                                                        , jumpPointModel.GetColor())
                                                                        , m_UICameraProvider
                                                                        );
                return jumpPointView;
            }
            
        }
    }
}
