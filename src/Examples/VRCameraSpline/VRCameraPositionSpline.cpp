//  Copyright (c) 2014 eeGeo Ltd. All rights reserved.

#include "VRCameraPositionSpline.h"
#include "EcefTangentBasis.h"
#include "LatLongAltitude.h"
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
                    m_time = 0.0f;
                    Stop();
                }
                
                m_time = Math::Clamp01(m_time);
            }
            
            if(IsStopPoint())
                m_time = 0.0f;
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
            const int MaxSpline = 9;
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
            
            float p = 10.0f;
            m33 orientation;
            switch(splineId)
            {
                case 0: // 1 STOP POINT
                {
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.795185, -122.402780, 305).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.793005, -122.405079, 305).ToECEF());
                    
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
                    
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.7955670, -122.3806140, 640).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(37.7934285, -122.4045563, 640).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    break;
                }
                    
                case 2: // SF
                {
                    
                    orientation.SetFromBasis(Eegeo::v3(0.449058,0.122659,0.885043),Eegeo::v3(0.667273,0.612706,-0.423481),Eegeo::v3(0.594215,-0.780735,-0.193294));
                    Eegeo::dv3 pt = Eegeo::dv3(4256102.665643, 3908033.687894, -2700980.817413);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.317570,0.280255,0.905873),Eegeo::v3(0.667276,0.612702,-0.423481),Eegeo::v3(0.673713,-0.738955,-0.007569));
                    pt = Eegeo::dv3(4256121.872745, 3908040.075322, -2700843.217141);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.091987,0.496432,0.863187),Eegeo::v3(0.667288,0.612690,-0.423479),Eegeo::v3(0.739096,-0.614952,0.274904));
                    pt = Eegeo::dv3(4256137.972563, 3908074.451393, -2700700.106807);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.389510,0.771711,0.502735),Eegeo::v3(0.667321,0.612675,-0.423447),Eegeo::v3(0.634794,-0.170551,0.753626));
                    pt = Eegeo::dv3(4256041.568475, 3908234.288441, -2700709.616101);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.396365,0.773514,0.494541),Eegeo::v3(0.667322,0.612675,-0.423446),Eegeo::v3(0.630536,-0.162181,0.759028));
                    pt = Eegeo::dv3(4255987.064053, 3908263.446745, -2700775.918628);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.126863,0.653785,0.745968),Eegeo::v3(0.667305,0.612672,-0.423478),Eegeo::v3(0.733901,-0.444067,0.514000));
                    pt = Eegeo::dv3(4255934.864160, 3908262.422243, -2700822.034474);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.058661,0.523607,0.849937),Eegeo::v3(0.667290,0.612674,-0.423498),Eegeo::v3(0.742484,-0.592000,0.313458));
                    pt = Eegeo::dv3(4255880.366696, 3908290.190068, -2700867.734507);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.116586,0.475679,0.871858),Eegeo::v3(0.667287,0.612675,-0.423504),Eegeo::v3(0.735621,-0.631156,0.245983));
                    pt = Eegeo::dv3(4255834.981675, 3908342.549457, -2700910.800525);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.234662,0.366726,0.900247),Eegeo::v3(0.667274,0.612676,-0.423518),Eegeo::v3(0.706879,-0.700098,0.100933));
                    pt = Eegeo::dv3(4255780.004911, 3908424.134481, -2700938.035865);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.173796,0.424834,0.888432),Eegeo::v3(0.667280,0.612674,-0.423510),Eegeo::v3(0.724246,-0.666440,0.177001));
                    pt = Eegeo::dv3(4255654.784223, 3908533.602955, -2700976.967388);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.231126,0.370224,0.899731),Eegeo::v3(0.667273,0.612674,-0.423521),Eegeo::v3(0.708045,-0.698255,0.105433));
                    pt = Eegeo::dv3(4255573.915531, 3908609.336656, -2701005.031158);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.659192,-0.220850,0.718813),Eegeo::v3(0.667188,0.612709,-0.423605),Eegeo::v3(0.346873,-0.758822,-0.551246));
                    pt = Eegeo::dv3(4255428.695225, 3908776.976528, -2700981.091835);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(0.727191,-0.659140,0.191653),Eegeo::v3(0.667089,0.612795,-0.423632),Eegeo::v3(-0.161787,-0.435910,-0.885333));
                    pt = Eegeo::dv3(4255482.044510, 3908930.061602, -2700927.013249);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    orientation.SetFromBasis(Eegeo::v3(-0.411068,-0.171086,-0.895407),Eegeo::v3(0.667069,0.613004,-0.423361),Eegeo::v3(-0.621319,0.771339,0.137860));
                    pt = Eegeo::dv3(4255490.309183, 3908942.927425, -2700907.697746);
                    pt += pt.Norm() * p;
                    AddPoint(pt, orientation);
                    
                    break;
                }
                case 3: // 3 STOP POINT
                {
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.456870, -2.957510, 334).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.458548, -2.961596, 334).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
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
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459901, -2.978062, 33).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(56.459921, -2.978145, 33).ToECEF());
                    
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
                    
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(40.703463, -74.016762, 334).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(40.7470872,-73.9868875, 334).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    break;
                }
                    
                    
                    
                case 8: // 7 STOP POINT
                {
                    
                    
                    std::vector<Eegeo::dv3> points;
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(40.763648, -73.973461, 25).ToECEF());
                    points.push_back(Eegeo::Space::LatLongAltitude::FromDegrees(40.762869, -73.974012, 25).ToECEF());
                    
                    std::vector<Eegeo::dv3>::iterator it;
                    for(it = points.begin(); it < points.end()-1; it++){
                        Eegeo::dv3 point = *(it+1) - *it;
                        Eegeo::Space::EcefTangentBasis basis = Eegeo::Space::EcefTangentBasis(*it, Eegeo::v3(point.GetX(), point.GetY(), point.GetZ()));
                        orientation.SetFromBasis(basis.GetRight(), basis.GetUp(), -basis.GetForward());
                        AddPoint(*it, orientation);
                    }
                    break;
                }
                    
                    
                case 9: // NY
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
