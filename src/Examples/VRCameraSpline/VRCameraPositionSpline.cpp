//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCameraPositionSpline.h"
#include "EcefTangentBasis.h"
#include "LatLongAltitude.h"
#include "CameraHelpers.h"
#include "Logger.h"


namespace Eegeo
{
    namespace VR
    {
        void VRCameraPositionSpline::AddPoint(const dv3& ecefEyePoint, const m33& orientation)
        {
            m_positionSpline.AddPoint(ecefEyePoint);
            
            v3 right = orientation.GetRow(0);
            v3 up = orientation.GetRow(1);
            v3 forward = orientation.GetRow(2);

            m_rightSpline.AddPoint(dv3(right.x, right.y, right.z));
            m_upSpline.AddPoint(dv3(up.x, up.y, up.z));
            m_forwardSpline.AddPoint(dv3(forward.x, forward.y, forward.z));
            
        }
        
        void VRCameraPositionSpline::setSlowDownFactor(float slowDownFactor){
            m_slowDownFactor = slowDownFactor;
        }
        
        void VRCameraPositionSpline::Clear()
        {
            m_positionSpline.Clear();
            m_rightSpline.Clear();
            m_upSpline.Clear();
            m_forwardSpline.Clear();
        }
        
        void VRCameraPositionSpline::Spew()
        {
            const std::vector<Geometry::CatmullRomSplinePoint>& rightPoints = m_rightSpline.GetPoints();
            const std::vector<Geometry::CatmullRomSplinePoint>& upPoints = m_upSpline.GetPoints();
            const std::vector<Geometry::CatmullRomSplinePoint>& forwardPoints = m_forwardSpline.GetPoints();
            const std::vector<Geometry::CatmullRomSplinePoint>& positionPoints = m_positionSpline.GetPoints();

            
            for(int i =0; i< rightPoints.size();i++)
            {
                const dv3 right = rightPoints.at(i).Position;
                const dv3 up = upPoints.at(i).Position;
                const dv3 forward = forwardPoints.at(i).Position;
                const dv3 position = positionPoints.at(i).Position;
                printf("orientation.SetFromBasis(Eegeo::v3(%f,%f,%f),Eegeo::v3(%f,%f,%f),Eegeo::v3(%f,%f,%f));\n", right.x,right.y,right.z,up.x,up.y,up.z,forward.x,forward.y,forward.z);
                printf("AddPoint(Eegeo::dv3(%f,%f,%f), orientation);\n",position.x,position.y,position.z);
            }
        }
        
        void VRCameraPositionSpline::Start()
        {
            
            if(m_positionSpline.GetNumberOfPoints() == 0)
            {
                return;
            }
            
            m_time = 0.0;
            m_playing = true;
        }
        
        void VRCameraPositionSpline::Stop()
        {
            m_playing = false;
        }
        
        void VRCameraPositionSpline::Update(float dt)
        {
            m_currentPlaybackSpeed = m_playbackSpeed ;//* m_slowDownFactor;
            if(m_playing && !IsStopPoint())
            {
                m_time += dt * m_currentPlaybackSpeed;
                if(m_time >= 1.0f)
                {
                    Stop();
                }
                
                m_time = Math::Clamp01(m_time);
            }
            
            if(IsStopPoint())
                m_time = 0.0f;
        }

        bool VRCameraPositionSpline::GetCurrentSplineHasWelcomeNote() const
        {
            return m_currentSplineHasWelcomeNote;
        }

        const std::string& VRCameraPositionSpline::GetCurrentSplineWelcomeNote() const
        {
            return m_welcomeNote;
        }

        void VRCameraPositionSpline::GetCurrentCameraPosition(dv3& interpolatedPositionEcef, m33& interpolatedOrientation) const
        {
            m_positionSpline.GetInterpolatedPositionInPlace(m_time, interpolatedPositionEcef);
            dv3 forward;
            dv3 up;
            dv3 right;
            m_forwardSpline.GetInterpolatedPositionInPlace(m_time, forward);
            m_upSpline.GetInterpolatedPositionInPlace(m_time, up);
            m_rightSpline.GetInterpolatedPositionInPlace(m_time, right);
            interpolatedOrientation.SetRow(0, right.Norm().ToSingle());
            interpolatedOrientation.SetRow(1, up.Norm().ToSingle());
            interpolatedOrientation.SetRow(2, forward.Norm().ToSingle());
            
        }

        void VRCameraPositionSpline::NextSpline()
        {
            const int MaxSpline = 8;
            m_time = 0.0f;
            ++m_currentSpline;
            if (m_currentSpline > MaxSpline)
            {
                m_currentSpline = 0;
            }
            SetSpline(m_currentSpline);
        }
        
        void VRCameraPositionSpline::SetSpline(int splineId)
        {
            Clear();
            m_currentSplineHasWelcomeNote = false;
            m_currentSpline = splineId;
            float p = 10.0f;
            m33 orientation;
            Eegeo::Space::EcefTangentBasis basis;
            switch(splineId)
            {
                case 0: // 1 STOP POINT
                {
                    m_currentSplineHasWelcomeNote = true;
                    m_welcomeNote = "mesh_example/welcome_sanfrancisco.png";

                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.795185, -122.402780, 305).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.791775, -122.402423, 305).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }

                    break;
                }
                    
                case 1: // 2 STOP POINT
                {
                    
                    Eegeo::dv3 p = Eegeo::Space::LatLongAltitude::FromDegrees(37.7955670, -122.3806140, 250).ToECEF();
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(p, 246.88382, basis);
                    orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                    AddPoint(p, orientation);
                    break;
                }
                    
                case 2: // SF
                {
                    
                    orientation.SetFromBasis(Eegeo::v3(0.449058,0.122659,0.885043),Eegeo::v3(0.667273,0.612706,-0.423481),Eegeo::v3(0.594215,-0.780735,-0.193294));
                    Eegeo::dv3 pt;
                    
                    Eegeo::Space::LatLongAltitude  lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.785699, -122.399769, 188.339979);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.317570,0.280255,0.905873),Eegeo::v3(0.667276,0.612702,-0.423481),Eegeo::v3(0.673713,-0.738955,-0.007569));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.786060, -122.398331, 146.802562);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.091987,0.496432,0.863187),Eegeo::v3(0.667288,0.612690,-0.423479),Eegeo::v3(0.739096,-0.614952,0.274904));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.786652, -122.396860, 118.010565);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.389510,0.771711,0.502735),Eegeo::v3(0.667321,0.612675,-0.423447),Eegeo::v3(0.634794,-0.170551,0.753626));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.788206, -122.397538, 155.645664);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.396365,0.773514,0.494541),Eegeo::v3(0.667322,0.612675,-0.423446),Eegeo::v3(0.630536,-0.162181,0.759028));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.788471, -122.398507, 165.217627);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.126863,0.653785,0.745968),Eegeo::v3(0.667305,0.612672,-0.423478),Eegeo::v3(0.733901,-0.444067,0.514000));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.788571, -122.399267, 149.286119);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.058661,0.523607,0.849937),Eegeo::v3(0.667290,0.612674,-0.423498),Eegeo::v3(0.742484,-0.592000,0.313458));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.788886, -122.400038, 149.288762);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.116586,0.475679,0.871858),Eegeo::v3(0.667287,0.612675,-0.423504),Eegeo::v3(0.735621,-0.631156,0.245983));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.789342, -122.400727, 169.325830);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.234662,0.366726,0.900247),Eegeo::v3(0.667274,0.612676,-0.423518),Eegeo::v3(0.706879,-0.700098,0.100933));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.790096, -122.401324, 194.168864);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.173796,0.424834,0.888432),Eegeo::v3(0.667280,0.612674,-0.423510),Eegeo::v3(0.724246,-0.666440,0.177001));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.791340, -122.402460, 264.185129);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.231126,0.370224,0.899731),Eegeo::v3(0.667273,0.612674,-0.423521),Eegeo::v3(0.708045,-0.698255,0.105433));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.792171, -122.403222, 310.522439);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.659192,-0.220850,0.718813),Eegeo::v3(0.667188,0.612709,-0.423605),Eegeo::v3(0.346873,-0.758822,-0.551246));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.794107, -122.403877, 330.227818);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.727191,-0.659140,0.191653),Eegeo::v3(0.667089,0.612795,-0.423632),Eegeo::v3(-0.161787,-0.435910,-0.885333));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.795105, -122.403033, 315.736584);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.411068,-0.171086,-0.895407),Eegeo::v3(0.667069,0.613004,-0.423361),Eegeo::v3(-0.621319,0.771339,0.137860));
                    lla = Eegeo::Space::LatLongAltitude::FromDegrees(37.795215, -122.402797, 305.956129);
                    pt = lla.ToECEF();
                    AddPoint(pt, orientation);
                    
                    break;
                }
                    
                case 3: // 3 STOP POINT
                {
                    m_currentSplineHasWelcomeNote = true;
                    m_welcomeNote = "mesh_example/welcome_dundee.png";

                    Eegeo::dv3 p = Eegeo::Space::LatLongAltitude::FromDegrees(56.456870, -2.957510, 304).ToECEF();
                    Eegeo::Camera::CameraHelpers::EcefTangentBasisFromPointAndHeading(p, 294.33133, basis);
                    orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                    AddPoint(p, orientation);
                    break;
                }
                    
                case 4: // Westport House
                {
                    
                    std::vector<Eegeo::dv3> points;
                    const double alt = 35.0;
                    
                    //Outside path
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.456160, -2.966101, alt + 250).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.456981, -2.969471, alt + 150).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.457455, -2.971733, alt + 100).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.458167, -2.974670, alt + 50).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.458972, -2.976199, alt + 25).ToECEF());
                    
                    //Close to interior
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459435, -2.977200, alt + 15).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459852, -2.977966, alt+10).ToECEF());
                    
                    //Interior
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459901, -2.978062, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459921, -2.978145, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459948, -2.978199, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459970, -2.978234, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459993, -2.978257, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.460026, -2.978270, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.460051, -2.978253, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.460067, -2.978212, alt).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.460083, -2.978168, alt).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    
                    break;
                }
                    
                case 5: // 4 STOP POINT
                {
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459928, -2.978063, 28.5).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459921, -2.978145, 28.5).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    break;
                }
                    
                    
                case 6: // 5 STOP POINT
                {
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459908, -2.978208, 28.5).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.460026, -2.978270, 28.5).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    break;
                }
                    
                case 7: // 6 STOP POINT
                {
                    m_currentSplineHasWelcomeNote = true;
                    m_welcomeNote = "mesh_example/welcome_newyork.png";

                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(40.699799, -74.021058, 380).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(40.702531, -74.015483, 380).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    break;
                }
                    
                    
                case 8: // NY
                {
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    Eegeo::dv3 pt = Eegeo::dv3(4645944.411084, 4162311.163091, 1332741.260517);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    pt = Eegeo::dv3(4645465.299021, 4162797.875165, 1332893.588509);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    pt = Eegeo::dv3(4644799.886354, 4163548.884426, 1333128.899514);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    pt = Eegeo::dv3(4644239.922460, 4164042.689519, 1333283.182439);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.003297,-0.301644,0.953413),Eegeo::v3(0.728825,0.652078,0.208825),Eegeo::v3(0.684698,-0.695559,-0.217691));
                    pt = Eegeo::dv3(4643677.358429, 4164614.177336, 1333462.042993);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.622116,-0.501066,-0.601582),Eegeo::v3(0.727658,0.653615,0.208093),Eegeo::v3(-0.288928,0.567207,-0.771233));
                    pt = Eegeo::dv3(4643254.487698, 4164814.040426, 1333531.934260);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.068765,0.233774,-0.969854),Eegeo::v3(0.727139,0.653852,0.209162),Eegeo::v3(-0.683033,0.719609,0.125021));
                    pt = Eegeo::dv3(4643042.347450, 4164609.062235, 1333691.663462);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    break;
                }
            }
        }
    }
}
