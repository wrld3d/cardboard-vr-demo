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
#include "VRCameraState.h"
#include "IVRHeadTracker.h"

#include "Modules/UI/Animations/IDv3Animateable.h"

namespace Eegeo
{
    namespace VRCamera
    {
        class VRRenderCamera : public Eegeo::Location::IInterestPointProvider, protected Eegeo::NonCopyable
        {
            
        public:
            VRRenderCamera(float screenWidth, float screenHeight, float eyeDistance)
            : m_screenHeight(screenHeight)
            , m_screenWidth(screenWidth)
            , m_eyeDistance(eyeDistance)
            , m_ecefPosition(0.0, 0.0, 0.0)
            , m_pTerrainHeightProvider(NULL)
            , m_nearMultiplier(0.1f)
            , m_cachedVRState(m_ecefPosition, GetInitCameraState(), GetInitCameraState(), Eegeo::m33::CreateIdentity(), Eegeo::m33::CreateIdentity(), Eegeo::m33::CreateIdentity())
            {
                m_pRenderCamera = new Camera::RenderCamera();
                m_orientation.Identity();
                m_currentOrientation.Identity();
                m_headTrackerOrientation.Identity();
                m_pRenderCamera->SetViewport(0,0,screenWidth, screenHeight);
                m_pRenderCamera->SetProjection(0.7, 0.1, 4000);
            }
            
            ~VRRenderCamera()
            {
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
            
            void UpdateCachedState();
            void SetProjectionMatrix(Eegeo::m44& projection);
            void UpdateFromPose(float eyeDistanceMultiplier);
            void SetEcefPosition(const Eegeo::dv3& ecef);
            void SetStartLatLongAltitude(const Eegeo::Space::LatLongAltitude& eyePos, float heading);
            
            void SetStartPositionAndOrientation(const Eegeo::dv3& position, const Eegeo::m33& orientation);
            
            void GetNearFarPlaneDistances(float& out_near, float& out_far);
            
            virtual void Update(float dt);
            
            void SetTerrainHeightProvider(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider * pTerrainHeightProvider) { m_pTerrainHeightProvider = pTerrainHeightProvider;}
            
            Camera::CameraState GetCameraState() const;

            const Eegeo::VRCamera::VRCameraState& GetVRCameraState();
            
            m33& GetOrientation();

            void UpdateHeadOrientation(const float headTansform[]);

            void SetEyeDistance(float eyeDistance) { m_eyeDistance = eyeDistance; }

        protected:
            dv3 m_ecefPosition;
            m33 m_orientation;
            m33 m_headTrackerOrientation;
            m33 m_currentOrientation;
            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider * m_pTerrainHeightProvider;
            Eegeo::Camera::RenderCamera* m_pRenderCamera;
            float m_nearMultiplier;

        private:
            
            Camera::CameraState GetInitCameraState()
            {
                return Camera::CameraState(dv3::Zero(), dv3::Zero(), m44::CreateIdentity(), m44::CreateIdentity());
            }
            
            void UpdateFovAndClippingPlanes();
            
            float m_screenWidth;
            float m_screenHeight;
            
            Eegeo::VRCamera::VRCameraState m_cachedVRState;
            dv3 m_interestEcef;
            float m_eyeDistance;
        };
    }
}
