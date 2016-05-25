// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "GazeUIViewAndroid.h"
#include <jni.h>
#include "logger.h"

namespace Eegeo {
    namespace GazeUI{
        
        
        GazeUIViewAndroid::GazeUIViewAndroid(AndroidNativeState& androidNativeState)
        : m_nativeState(androidNativeState)
        {
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jstring strClassName = env->NewStringUTF("com/eegeo/examples/vr/ui/GazeUI");
            jclass routeMatchingExampleHudClass = m_nativeState.LoadClass(env, strClassName);
            env->DeleteLocalRef(strClassName);
            
            //create a persistent reference to the class
            m_androidGazeUIClass = static_cast<jclass>(env->NewGlobalRef(routeMatchingExampleHudClass));
            
            //get the constructor for the ExampleControllerHud, which takes the activity, a pointer to 'this' as
            //a parameter, and a flag to indicate if currently in follow mode.
            jmethodID gazeUIConstructor = env->GetMethodID(routeMatchingExampleHudClass, "<init>", "(Lcom/eegeo/mobilesdkharness/MainActivity;J)V");
            
            jobject instance = env->NewObject(
                                              m_androidGazeUIClass,
                                              gazeUIConstructor,
                                              m_nativeState.activity,
                                              (jlong)(this));
            
            m_androidGazeUIView = env->NewGlobalRef(instance);
            
            CreateNativeUI();
            
        }
        
        GazeUIViewAndroid::~GazeUIViewAndroid()
        {
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jmethodID destroyMethod = env->GetMethodID(m_androidGazeUIClass, "DestroyView", "()V");
            env->CallVoidMethod(m_androidGazeUIView, destroyMethod);
            
            env->DeleteGlobalRef(m_androidGazeUIView);
            env->DeleteGlobalRef(m_androidGazeUIClass);
        }
        
        void GazeUIViewAndroid::CreateNativeUI(){
            
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jmethodID createGazeUIMethod = env->GetMethodID(m_androidGazeUIClass, "CreateGazeUI", "()V");
            env->CallVoidMethod(m_androidGazeUIView, createGazeUIMethod);
        }
        
        
        void GazeUIViewAndroid::UpdateGazeProgress(int progress){
            
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jmethodID gazeHitStartedMethod = env->GetMethodID(m_androidGazeUIClass, "UpdateGazeProgress", "(I)V");
            env->CallVoidMethod(m_androidGazeUIView, gazeHitStartedMethod, progress);
            
        }
        
        void GazeUIViewAndroid::ShowView(){
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jmethodID showViewMethod = env->GetMethodID(m_androidGazeUIClass, "ShowView", "()V");
            env->CallVoidMethod(m_androidGazeUIView, showViewMethod);
        }
        
        void GazeUIViewAndroid::HideView(){
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jmethodID hideViewMethod = env->GetMethodID(m_androidGazeUIClass, "HideView", "()V");
            env->CallVoidMethod(m_androidGazeUIView, hideViewMethod);
        }
        
        void GazeUIViewAndroid::SetCenterPoint(float x, float y){
            AndroidSafeNativeThreadAttachment attached(m_nativeState);
            JNIEnv* env = attached.envForThread;
            
            jmethodID hideViewMethod = env->GetMethodID(m_androidGazeUIClass, "SetCenterPoint", "(FF)V");
            env->CallVoidMethod(m_androidGazeUIView, hideViewMethod, x, y);
        }
        
    }
}
