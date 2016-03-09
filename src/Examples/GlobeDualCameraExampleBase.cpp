// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GlobeDualCameraExampleBase.h"
#include "ScreenProperties.h"
#include "GlobeCameraController.h"
#include "GlobeCameraTouchController.h"
#include "ScreenProperties.h"

namespace Examples
{
    GlobeDualCameraExampleBase::GlobeDualCameraExampleBase(Eegeo::Camera::GlobeCamera::GlobeCameraController* pCameraController,
                                                   Eegeo::Camera::GlobeCamera::GlobeCameraTouchController& cameraTouchController)
    : m_pGlobeCameraController(pCameraController)
    , m_globeCameraTouchController(cameraTouchController)
    {
    }
    
    GlobeDualCameraExampleBase::~GlobeDualCameraExampleBase()
    {
        delete m_pGlobeCameraController;
    }

    void GlobeDualCameraExampleBase::EarlyUpdate(float dt)
    {
        m_pGlobeCameraController->Update(dt);
    }
    
    void GlobeDualCameraExampleBase::NotifyScreenPropertiesChanged(const Eegeo::Rendering::ScreenProperties& screenProperties)
    {
        m_pGlobeCameraController->UpdateScreenProperties(screenProperties);
    }
    
    Eegeo::Camera::CameraState GlobeDualCameraExampleBase::GetCurrentCameraState() const
    {
        return m_pGlobeCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState GlobeDualCameraExampleBase::GetCurrentLeftCameraState() const
    {
        return m_pGlobeCameraController->GetCameraState();
    }
    
    Eegeo::Camera::CameraState GlobeDualCameraExampleBase::GetCurrentRightCameraState() const
    {
        return m_pGlobeCameraController->GetCameraState();
    }
    
    void GlobeDualCameraExampleBase::Event_TouchRotate(const AppInterface::RotateData& data)
    {
        m_globeCameraTouchController.Event_TouchRotate(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchRotate_Start(const AppInterface::RotateData& data)
    {
        m_globeCameraTouchController.Event_TouchRotate_Start(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchRotate_End(const AppInterface::RotateData& data)
    {
        m_globeCameraTouchController.Event_TouchRotate_End(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchPinch(const AppInterface::PinchData& data)
    {
        m_globeCameraTouchController.Event_TouchPinch(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchPinch_Start(const AppInterface::PinchData& data)
    {
        m_globeCameraTouchController.Event_TouchPinch_Start(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchPinch_End(const AppInterface::PinchData& data)
    {
        m_globeCameraTouchController.Event_TouchPinch_End(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchPan(const AppInterface::PanData& data)
    {
        m_globeCameraTouchController.Event_TouchPan(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchPan_Start(const AppInterface::PanData& data)
    {
        m_globeCameraTouchController.Event_TouchPan_Start(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchPan_End(const AppInterface::PanData& data)
    {
        m_globeCameraTouchController.Event_TouchPan_End(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchTap(const AppInterface::TapData& data)
    {
        m_globeCameraTouchController.Event_TouchTap(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchDoubleTap(const AppInterface::TapData& data)
    {
        m_globeCameraTouchController.Event_TouchDoubleTap(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchDown(const AppInterface::TouchData& data)
    {
        m_globeCameraTouchController.Event_TouchDown(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchMove(const AppInterface::TouchData& data)
    {
        m_globeCameraTouchController.Event_TouchMove(data);
    }
    
    void GlobeDualCameraExampleBase::Event_TouchUp(const AppInterface::TouchData& data)
    {
        m_globeCameraTouchController.Event_TouchUp(data);
    }
}