//
//  CardboardDeviceProfile.cpp
//  SDKSamplesApp
//
//  Created by Ali on 3/31/16.
//
//

#include "VRCardboardDeviceProfile.h"
#include "Logger.h"

namespace Eegeo
{
    namespace VR
    {
        namespace Distortion
        {
            
            VRDevice VRCardboardDeviceProfile::GetDevice() {
                return device;
            }
            
            float VRCardboardDeviceProfile::Distort(float r, float k1, float k2) {
                float r2 = r * r;
                return ((k2 * r2 + k1) * r2 + 1) * r;
            }
            
            float VRCardboardDeviceProfile::DistortInv(float radius, float k1, float k2) {
                // Secant method.
                float r0 = 0;
                float r1 = 1;
                float dr0 = radius - Distort(r0, k1, k2);
                while (Eegeo::Math::Abs(r1 - r0) > 0.0001f) { 
                    float dr1 = radius - Distort(r1, k1, k2);
                    float r2 = r1 - dr1 * ((r1 - r0) / (dr1 - dr0));
                    r0 = r1;
                    r1 = r2;
                    dr0 = dr1;
                }
                return r1;
            }
            
            void VRCardboardDeviceProfile::SetupProfile(float profileData[]) {
                device.maxFOV.outer = profileData[0];
                device.maxFOV.upper = profileData[1];
                device.maxFOV.inner = profileData[2];
                device.maxFOV.lower = profileData[3];
                screen.width = profileData[4];
                screen.height = profileData[5];
                screen.border = profileData[6];
                device.lenses.separation = profileData[7];
                device.lenses.offset = profileData[8];
                device.lenses.screenDistance = profileData[9];
                device.lenses.alignment = (int)profileData[10];
                device.distortion.k1 = profileData[11];
                device.distortion.k2 = profileData[12];
                device.inverse = ApproximateInverse(device.distortion);
            }
            
            VRDistortionCoeff VRCardboardDeviceProfile::ApproximateInverse(VRDistortionCoeff distort, float maxRadius, const int numSamples) {
                const int numCoefficients = 2;

                // R + k1*R^3 + k2*R^5 = r, with R = rp = distort(r)
                // Repeating for numSamples:
                //   [ R0^3, R0^5 ] * [ K1 ] = [ r0 - R0 ]
                //   [ R1^3, R1^5 ]   [ K2 ]   [ r1 - R1 ]
                //   [ R2^3, R2^5 ]            [ r2 - R2 ]
                //   [ etc... ]                [ etc... ]
                // That is:
                //   matA * [K1, K2] = y
                // Solve:
                //   [K1, K2] = inverse(transpose(matA) * matA) * transpose(matA) * y
                double **matA = new double*[numSamples];
                double vecY[numSamples];
                for (int i = 0; i < numSamples; ++i) {
                    matA[i] = new double[numCoefficients];
                    float r = maxRadius * (i + 1) / (float) numSamples;
                    double rp = Distort(r, distort.k1, distort.k2);
                    double v = rp;
                    for (int j = 0; j < numCoefficients; ++j) {
                        v *= rp * rp;
                        matA[i][j] = v;
                    }
                    vecY[i] = r - rp;
                }
                double vecK[numCoefficients];
                SolveLeastSquares(matA, vecY, numSamples, numCoefficients, vecK);
                VRDistortionCoeff coeef = {(float)vecK[0],(float)vecK[1]};
                for (int i = 0; i < numSamples; ++i) {
                    delete [] matA[i];
                }
                
                delete [] matA;
                return coeef;
            }
            
            void VRCardboardDeviceProfile::SolveLeastSquares(double **matA, double vecY[], const int numSamples, const int numCoefficients, double vecX[]) {
                if (numCoefficients != 2) {
                    EXAMPLE_LOG("Only 2 coefficients supported.");
                    return;
                }
                // Calculate transpose(A) * A
                double matATA[numCoefficients][numCoefficients];

                
                for (int k = 0; k < numCoefficients; ++k) {
                    for (int j = 0; j < numCoefficients; ++j) {
                        double sum = 0.0f;
                        for (int i = 0; i < numSamples; ++i) {
                            sum += matA[i][j] * matA[i][k];
                        }
                        matATA[j][k] = sum;
                    }
                }

                // Calculate the inverse of transpose(A) * A.  Inverting isn't recommended for numerical
                // stability, but should be ok for small and well-behaved data sets.  Using manual matrix
                // inversion here (hence the restriction of numCoefficients to 2 in this function).

                double matInvATA[numCoefficients][numCoefficients];
                
                double det = matATA[0][0] * matATA[1][1] - matATA[0][1] * matATA[1][0];
                matInvATA[0][0] = matATA[1][1] / det;
                matInvATA[1][1] = matATA[0][0] / det;
                matInvATA[0][1] = -matATA[1][0] / det;
                matInvATA[1][0] = -matATA[0][1] / det;

                // Calculate transpose(A) * y
                double vecATY[numCoefficients];
                for (int j = 0; j < numCoefficients; ++j) {
                    double sum = 0.0;
                    for (int i = 0; i < numSamples; ++i) {
                        sum += matA[i][j] * vecY[i];
                    }
                    vecATY[j] = sum;
                }

                // Now matrix multiply the previous values to get the result.
                for (int j = 0; j < numCoefficients; ++j) {
                    double sum = 0.0;
                    for (int i = 0; i < numCoefficients; ++i) {
                        sum += matInvATA[i][j] * vecATY[i];
                    }
                    vecX[j] = sum;
                }
            }
            
            /// The vertical offset of the lens centers from the screen center.
            float VRCardboardDeviceProfile::GetVerticalLensOffset() {
                    return (device.lenses.offset - screen.border - screen.height/2) * device.lenses.alignment;
            }
            
            /// Calculates the tan-angles from the maximum FOV for the left eye for the
            /// current device and screen parameters, assuming no lenses.
            void VRCardboardDeviceProfile::GetLeftEyeNoLensTanAngles(float* result) {
                // Tan-angles from the max FOV.
                float fovLeft = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-device.maxFOV.outer)), device.distortion.k1, device.distortion.k2);
                float fovTop = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(device.maxFOV.upper)), device.distortion.k1, device.distortion.k2);
                float fovRight = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(device.maxFOV.inner)), device.distortion.k1, device.distortion.k2);
                float fovBottom = DistortInv(Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-device.maxFOV.lower)), device.distortion.k1, device.distortion.k2);
                // Viewport size.
                float halfWidth = screen.width / 4;
                float halfHeight = screen.height / 2;
                // Viewport center, measured from left lens position.
                float centerX = device.lenses.separation / 2 - halfWidth;
                float centerY = -GetVerticalLensOffset();
                float centerZ = device.lenses.screenDistance;
                // Tan-angles of the viewport edges, as seen through the lens.
                float screenLeft = (centerX - halfWidth) / centerZ;
                float screenTop = (centerY + halfHeight) / centerZ;
                float screenRight = (centerX + halfWidth) / centerZ;
                float screenBottom = (centerY - halfHeight) / centerZ;
                // Compare the two sets of tan-angles and take the value closer to zero on each side.
                result[0] = Eegeo::Max<float>(fovLeft, screenLeft);
                result[1] = Eegeo::Min<float>(fovTop, screenTop);
                result[2] = Eegeo::Min<float>(fovRight, screenRight);
                result[3] = Eegeo::Max<float>(fovBottom, screenBottom);
            }
            
            /// Calculates the tan-angles from the maximum FOV for the left eye for the
            /// current device and screen parameters.
            void VRCardboardDeviceProfile::GetLeftEyeVisibleTanAngles(float* result) {
                // Tan-angles from the max FOV.
                
                float fovLeft = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-device.maxFOV.outer));
                float fovTop = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(device.maxFOV.upper));
                float fovRight = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(device.maxFOV.inner));
                float fovBottom = Eegeo::Math::Tan(Eegeo::Math::Deg2Rad(-device.maxFOV.lower));
                // Viewport size.
                float halfWidth = screen.width / 4;
                float halfHeight = screen.height / 2;
                // Viewport center, measured from left lens position.
                float centerX = device.lenses.separation / 2 - halfWidth;
                float centerY = -1 * GetVerticalLensOffset();
                float centerZ = device.lenses.screenDistance;
                // Tan-angles of the viewport edges, as seen through the lens.
                float screenLeft = Distort((centerX - halfWidth) / centerZ, device.distortion.k1, device.distortion.k2);
                float screenTop = Distort((centerY + halfHeight) / centerZ, device.distortion.k1, device.distortion.k2);
                float screenRight = Distort((centerX + halfWidth) / centerZ, device.distortion.k1, device.distortion.k2);
                float screenBottom = Distort((centerY - halfHeight) / centerZ, device.distortion.k1, device.distortion.k2);
                // Compare the two sets of tan-angles and take the value closer to zero on each side.

                result[0] = Eegeo::Max<float>(fovLeft, screenLeft);
                result[1] = Eegeo::Min<float>(fovTop, screenTop);
                result[2] = Eegeo::Min<float>(fovRight, screenRight);
                result[3] = Eegeo::Max<float>(fovBottom, screenBottom);
            }
            
            void VRCardboardDeviceProfile::GetLeftEyeVisibleScreenRect(float undistortedFrustum[], float *rect) {
                float dist = device.lenses.screenDistance;
                float eyeX = (screen.width - device.lenses.separation) / 2;
                float eyeY = GetVerticalLensOffset() + screen.height / 2;
                float left = (undistortedFrustum[0] * dist + eyeX) / screen.width;
                float top = (undistortedFrustum[1] * dist + eyeY) / screen.height;
                float right = (undistortedFrustum[2] * dist + eyeX) / screen.width;
                float bottom = (undistortedFrustum[3] * dist + eyeY) / screen.height;
                
                rect[0] = left;
                rect[1] = bottom;
                rect[2] = right - left;
                rect[3] = top - bottom;
            }
        }
    }
}
