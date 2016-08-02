//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once
#include "Types.h"
#include "RenderCamera.h"
#include "VectorMathDecl.h"
#include "Space.h"
#include "IInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "VRCameraPositionSpline.h"
#include "CameraState.h"
#include "IVRHeadTracker.h"

#include "Modules/UI/Animations/IDv3Animateable.h"

namespace Eegeo
{
    namespace VR
    {
        
        class JumpPointsCameraController : public Eegeo::Location::IInterestPointProvider, public Eegeo::UI::Animations::IDv3Animateable, protected Eegeo::NonCopyable
        {
            
        public:
            JumpPointsCameraController(float screenWidth, float screenHeight)
            : m_screenHeight(screenHeight)
            , m_screenWidth(screenWidth)
            , m_moveDirection(0.f, 0.f, 0.f)
            , m_ecefPosition(0.0, 0.0, 0.0)
            , m_time(0.0f)
            , m_pTerrainHeightProvider(NULL)
            , m_shiftDown(false)
            , m_nearMultiplier(0.1f)
            {
                m_pRenderCamera = new Camera::RenderCamera();
                m_orientation.Identity();
                m_currentOrientation.Identity();
                m_headTrackerOrientation.Identity();
                m_pRenderCamera->SetViewport(0,0,screenWidth, screenHeight);
                m_pRenderCamera->SetProjection(0.7, 0.1, 4000);
            }
            
            ~JumpPointsCameraController() {
                delete m_pRenderCamera;
            };
            
            Eegeo::dv3 GetEcefInterestPoint() const;
            double GetAltitudeAboveSeaLevel() const;

            Eegeo::Camera::RenderCamera& GetCamera() { return *m_pRenderCamera; }
            const dv3& GetCameraPosition() const { return m_ecefPosition; }
            const m33& GetCameraOrientation() const { return m_orientation; }
            const Eegeo::m33& GetHeadTrackerOrientation() { return m_headTrackerOrientation; };
            void SetCameraOrientation(const m33& orientation);
            void SetNearMultiplier(float nearMultiplier) { m_nearMultiplier = nearMultiplier; }
            
            const v3 GetRight() const { return m_orientation.GetRow(0); }
            const v3 GetUp() const { return m_orientation.GetRow(1); }
            const v3 GetForward() const { return m_orientation.GetRow(2); }
            
            
            void SetProjectionMatrix(Eegeo::m44& projection);
            void UpdateFromPose(const Eegeo::m33& orientation, float eyeDistance);
            void SetEcefPosition(const Eegeo::dv3& ecef);
            void SetStartLatLongAltitude(const Eegeo::Space::LatLongAltitude& eyePos);
            
            void SetStartPositionAndOrientation(Eegeo::dv3& position, Eegeo::m33& orientation);
            
            void GetNearFarPlaneDistances(float& out_near, float& out_far);
            
            // on animation update
            virtual void OnDv3Updated(Eegeo::dv3& delta);
            
            void Update(float dt);
            
            void RotateHorizontal(float angle);
            
            void SetTerrainHeightProvider(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider * pTerrainHeightProvider) { m_pTerrainHeightProvider = pTerrainHeightProvider;}
            
            Camera::CameraState GetCameraState() const;
            
            void SetShiftDown(bool down) { m_shiftDown = down; }
            
            m33& GetOrientation();
            
        private:
            
            
            void UpdateFovAndClippingPlanes();
            
            v3 m_moveDirection;
            
            float m_screenWidth;
            float m_screenHeight;
            
            
            float m_time;
            
            Eegeo::Camera::RenderCamera* m_pRenderCamera;
            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider * m_pTerrainHeightProvider;
            
            bool m_shiftDown;
            
            dv3 m_interestEcef;
            dv3 m_ecefPosition;
            m33 m_orientation;
            m33 m_currentOrientation;
            m33 m_headTrackerOrientation;
            float m_nearMultiplier;

        };
    }
}
