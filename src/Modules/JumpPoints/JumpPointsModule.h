// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

#include "Rendering.h"
#include "EegeoWorld.h"
#include "../UI/IUIInteractionObservable.h"
#include "JumpPointController.h"
#include "JumpPointRepository.h"
#include "JumpPointViewFactory.h"

namespace Eegeo
{
    namespace UI
    {
        namespace JumpPoints
        {
            /*!
             * \brief Default implementation of Jump point control and rendering.
             *
             *  This module handles the displaying and control of Jump points.
             *
             */
            class JumpPointsModule : protected Eegeo::NonCopyable
            {
            public:
                
                JumpPointsModule(Eegeo::Modules::Core::RenderingModule& p_RenderingModule
                                 , Modules::IPlatformAbstractionModule& p_PlatformAbstractionModule
                                 , IUIInteractionObservable& p_IUIInteractionObservable
                                 , IUICameraProvider& p_UICameraProvider
                                 , const std::string& fileName
                                 , const Eegeo::v2& p_Dimension
                                 );
                
                ~JumpPointsModule();
                
                void Update(float dt);
                
                JumpPointRepository& GetRepository() const;
                
                JumpPointController& GetController() const;
                
            private:
                JumpPointViewFactory* m_pViewFactory;
                JumpPointRepository* m_pRepository;
                JumpPointController * m_pController;
            };
        }
    }
}
