//Copyright eeGeo Ltd (2012-2014), All Rights Reserved
package com.eegeo.mobilesdkharness;

import android.app.Activity;
import android.content.res.AssetManager;
import android.view.Surface;

public class NativeJniCalls
{
	public static native long createNativeCode(Activity activity, AssetManager assetManager, float dpi);
	public static native void destroyNativeCode();
	public static native void pauseNativeCode();
	public static native void resumeNativeCode();
	public static native void releaseNativeWindow(long oldWindow);
	public static native long setNativeSurface(Surface surface);
	public static native void stopUpdatingNativeCode();
	public static native void updateNativeCode(float deltaTimeSeconds, float[] headTransform);
	public static native void updateCardboardProfile(float[] profileParams);
	public static native void magnetTriggered();
	public static native void toggleNightMode(boolean turnOn);
}
