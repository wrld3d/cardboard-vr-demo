//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#pragma once
#include "Types.h"
#include "RenderCamera.h"
#include "VectorMathDecl.h"
#include "Space.h"
#include "IInterestPointProvider.h"
#include "TerrainHeightProvider.h"
#include "OVRCameraPositionSpline.h"
#include "CameraState.h"

namespace Eegeo
{
    namespace OVR
    {
       
        struct FovPort
        {
            float UpTan;
            float DownTan;
            float LeftTan;
            float RightTan;
            
            FovPort ( float sideTan = 0.0f ) :
            UpTan(sideTan), DownTan(sideTan), LeftTan(sideTan), RightTan(sideTan) { }
            
            FovPort ( float u, float d, float l, float r ) :
            UpTan(u), DownTan(d), LeftTan(l), RightTan(r) { }
            
            static FovPort CreateFromRadians(float horizontalFov, float verticalFov)
            {
                FovPort result;
                result.UpTan    = tanf (   verticalFov * 0.5f );
                result.DownTan  = tanf (   verticalFov * 0.5f );
                result.LeftTan  = tanf ( horizontalFov * 0.5f );
                result.RightTan = tanf ( horizontalFov * 0.5f );
                return result;
            }
            
            //  Get Horizontal/Vertical components of Fov in radians.
            float GetVerticalFovRadians() const     { return atanf(UpTan)    + atanf(DownTan); }
            float GetHorizontalFovRadians() const   { return atanf(LeftTan)  + atanf(RightTan); }
            //  Get Horizontal/Vertical components of Fov in degrees.
            
            // Compute maximum tangent value among all four sides.
            float GetMaxSideTan() const
            {
                return std::max(std::max(UpTan, DownTan), std::max(LeftTan, RightTan));
            }
            
            // Converts Fov Tan angle units to [-1,1] render target NDC space
            Eegeo::v2 TanAngleToRendertargetNDC(Eegeo::v2 const &tanEyeAngle);
            
            
            // Compute per-channel minimum and maximum of Fov.
            static FovPort Min(const FovPort& a, const FovPort& b)
            {
                FovPort fov(std::min( a.UpTan   , b.UpTan    ),
                            std::min( a.DownTan , b.DownTan  ),
                            std::min( a.LeftTan , b.LeftTan  ),
                            std::min( a.RightTan, b.RightTan ) );
                return fov;
            }
            
            static FovPort Max(const FovPort& a, const FovPort& b)
            {
                FovPort fov( std::max( a.UpTan   , b.UpTan    ),
                            std::max( a.DownTan , b.DownTan  ),
                            std::max( a.LeftTan , b.LeftTan  ),
                            std::max( a.RightTan, b.RightTan ) );
                return fov;
            }
        };
        
        
        //-----------------------------------------------------------------------------------
        // ***** ScaleAndOffset
        
        struct ScaleAndOffset2D
        {
            Eegeo::v2 Scale;
            Eegeo::v2 Offset;
            
            ScaleAndOffset2D(float sx = 0.0f, float sy = 0.0f, float ox = 0.0f, float oy = 0.0f)
            : Scale(sx, sy), Offset(ox, oy)        
            { }
        };
        
        
        namespace MoveDirection
        {
            enum Values
            {
                Forward,
                Backwards,
                Left,
                Right,
                Up,
                Down
            };
        }
        
        class OVREegeoCameraController : public Eegeo::Location::IInterestPointProvider, protected Eegeo::NonCopyable
        {
            
        public:
            OVREegeoCameraController(float screenWidth, float screenHeight)
            : m_moving(false)
            , m_screenHeight(screenHeight)
            , m_screenWidth(screenWidth)
            , m_moveDirection(0.f, 0.f, 0.f)
            , m_ecefPosition(0.0, 0.0, 0.0)
            , m_falling(false)
            , m_IsFirstCall(true)
            , m_pTerrainHeightProvider(NULL)
            , m_shiftDown(false)
            {
                
                m_orientation.Identity();
                
                m_renderCamera.SetViewport(0,0,screenWidth, screenHeight);
                m_renderCamera.SetProjection(0.7, 0.001, 4000);
                
                m_OVRCameraPositionSpline.Start();

            }
            
            ~OVREegeoCameraController() { };
            
            Eegeo::dv3 GetEcefInterestPoint() const;
            double GetAltitudeAboveSeaLevel() const;

            Eegeo::Camera::RenderCamera& GetCamera() { return m_renderCamera; }
            const bool IsMoving() const { return m_moving; }
            const bool IsFalling() const { return m_falling; }
            const bool IsFollowingSpline() const { return m_OVRCameraPositionSpline.IsPlaying(); }
            const dv3& GetCameraPosition() const { return m_ecefPosition; }
            const m33& GetCameraOrientation() const { return m_orientation; }
            
            const v3 GetRight() const { return m_orientation.GetRow(0); }
            const v3 GetUp() const { return m_orientation.GetRow(1); }
            const v3 GetForward() const { return m_orientation.GetRow(2); }
            
            OVRCameraPositionSpline& GetOVRCameraPositionSpline() { return m_OVRCameraPositionSpline; }
            
            void SetProjectionMatrix(Eegeo::m44& projection);
            void UpdateFromPose(const Eegeo::m33& orientation, const Eegeo::v3& eyeOffset);
            void SetEcefPosition(const Eegeo::dv3& ecef);
            void SetStartLatLongAltitude(const Eegeo::Space::LatLongAltitude& eyePos);
            
            void GetNearFarPlaneDistances(float& out_near, float& out_far);
            
            ScaleAndOffset2D CreateNDCScaleAndOffsetFromFov ( FovPort tanHalfFov );
            m44 CreateProjection( bool rightHanded, float tanHalfFov,
                                 float zNear /*= 0.01f*/, float zFar /*= 10000.0f*/ );
            
            void Update(float dt);
            
            void MoveStart(MoveDirection::Values direction);
            void MoveEnd();
            
            void StartFall();
            void StopFall();
            
            void RotateHorizontal(float angle);
            
            void SetTerrainHeightProvider(Eegeo::Resources::Terrain::Heights::TerrainHeightProvider * pTerrainHeightProvider) { m_pTerrainHeightProvider = pTerrainHeightProvider;}
            
            Camera::CameraState GetCameraState() const;
            
            void SetShiftDown(bool down) { m_shiftDown = down; }
            
        private:
            bool CanAcceptUserInput() const;
            
            float MovementAltitudeMutlipler() const;
            
            void Move(float dt);
            void Fall(float dt);
            void UpdateFovAndClippingPlanes();

            bool m_moving;
            v3 m_moveDirection;
            
            float m_screenWidth;
            float m_screenHeight;
            
            float m_currentFallSpeed;
            bool m_falling;
            
            Eegeo::Camera::RenderCamera m_renderCamera;
            Eegeo::Resources::Terrain::Heights::TerrainHeightProvider * m_pTerrainHeightProvider;
            
            OVRCameraPositionSpline m_OVRCameraPositionSpline;
            
            bool m_shiftDown;
            bool m_IsFirstCall;
            
            dv3 m_interestEcef;
            dv3 m_ecefPosition;
            m33 m_orientation;
            m33 m_initialOrientation;
        };
    }
}
