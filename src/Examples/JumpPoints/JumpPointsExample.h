// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#ifndef __ExampleApp__JumpPointsExample__
#define __ExampleApp__JumpPointsExample__

#include "JumpPointsCameraController.h"
#include "IExample.h"
#include "Camera.h"
#include "Geometry.h"
#include "Streaming.h"
#include "GlobeCamera.h"
#include "Modules/UI/UIInteraction/UIInteractionController.h"
#include "Modules/UI/IUICameraProvider.h"
#include "Modules/UI/UIQuad/IUIQuadFactory.h"
#include "Modules/UI/UIRenderableFilter.h"

#include "Modules/JumpPoints/JumpPoint.h"
#include "Modules/JumpPoints/JumpPointsModule.h"
#include "Modules/JumpPoints/JumpPointRepository.h"

namespace Examples
{
    /*!
     *  JumpPointsExample demonstrates a camera controller that can animate the camera along a spline
     */
    class JumpPointsExample : public IExample, Eegeo::NonCopyable
    {
    private:
        
        float m_eyeDistance;
        Eegeo::EegeoWorld& m_world;
        
        Eegeo::UI::IUIQuadFactory& m_uiQuadFactory;
        Eegeo::UI::IUIInteractionObservable& m_uiInteractionObservable;
        Eegeo::UI::IUICameraProvider& m_uiCameraProvider;
        
        Eegeo::VR::JumpPointsCameraController* m_pSplineCameraController;
        Eegeo::UI::JumpPoints::JumpPoint *m_pJumpPoint1, *m_pJumpPoint2, *m_pJumpPoint3;
        Eegeo::UI::JumpPoints::JumpPointsModule* m_pJumpPointsModule;
        
        Eegeo::Rendering::RenderableFilters& m_renderableFilters;
        Eegeo::UI::UIRenderableFilter* m_pUIRenderableFilter;
        
    public:
        
        JumpPointsExample(Eegeo::EegeoWorld& eegeoWorld,
                            Eegeo::Streaming::ResourceCeilingProvider& resourceCeilingProvider,
                            Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                            const Eegeo::Rendering::ScreenProperties& initialScreenProperties,
                            Eegeo::UI::IUIQuadFactory& quadFactory,
                            Eegeo::UI::IUIInteractionObservable& uiInteractionObservable,
                            Eegeo::UI::IUICameraProvider& uiCameraProvider);
        
        virtual ~JumpPointsExample();
        
        static std::string GetName()
        {
            return "JumpPointsExample";
        }
        std::string Name() const
        {
            return GetName();
        }
        
        void Start();
        void OrientationUpdate();
        void EarlyUpdate(float dt);
        void Update(float dt);
        void PreWorldDraw() { }
        void Draw() {}
        void Suspend();
        
        Eegeo::m33& getCurrentCameraOrientation();
        
        void UpdateCardboardProfile(float cardboardProfile[]);
        
        virtual Eegeo::Camera::RenderCamera& GetRenderCamera();
        virtual Eegeo::Camera::CameraState GetCurrentLeftCameraState(float headTansform[]) const;
        virtual Eegeo::Camera::CameraState GetCurrentRightCameraState(float headTansform[]) const;
        virtual Eegeo::Camera::CameraState GetCurrentCameraState() const;
        
        virtual void NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties);
        
        void NotifyViewNeedsLayout() {}
        
        void Event_TouchRotate 			(const AppInterface::RotateData& data) { }
        void Event_TouchRotate_Start	(const AppInterface::RotateData& data) { }
        void Event_TouchRotate_End 		(const AppInterface::RotateData& data) { }
        
        void Event_TouchPinch 			(const AppInterface::PinchData& data) { }
        void Event_TouchPinch_Start 	(const AppInterface::PinchData& data) { }
        void Event_TouchPinch_End 		(const AppInterface::PinchData& data) { }
        
        void Event_TouchPan				(const AppInterface::PanData& data) { }
        void Event_TouchPan_Start		(const AppInterface::PanData& data) { }
        void Event_TouchPan_End 		(const AppInterface::PanData& data) { }
        
        void Event_TouchTap 			(const AppInterface::TapData& data) { }
        void Event_TouchDoubleTap		(const AppInterface::TapData& data) { }
        void Event_TouchDown 			(const AppInterface::TouchData& data) { }
        void Event_TouchMove 			(const AppInterface::TouchData& data) { }
        void Event_TouchUp 				(const AppInterface::TouchData& data) { }
        
    };
}

#endif /* defined(__ExampleApp__JumpPointsExample__) */
