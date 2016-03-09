package com.eegeo.mobilesdkharness;

import java.util.ArrayList;

import android.content.Context;
import android.util.AttributeSet;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

import com.google.vrtoolkit.cardboard.CardboardView;

public class CardboardViewWithSurfaceHolder extends CardboardView{

	private INativeMessageRunner m_nativeMessageRunner;

	protected void setActivity(INativeMessageRunner nativeMessageRunner)
	{
		m_nativeMessageRunner = nativeMessageRunner;
	}

	public CardboardViewWithSurfaceHolder(Context context) {
		super(context);
		// TODO Auto-generated constructor stub
	}

	public CardboardViewWithSurfaceHolder(Context context, AttributeSet attrs) {
		super(context, attrs);
		// TODO Auto-generated constructor stub
	}

	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		super.surfaceCreated(holder);
		for(int lop=0; lop<mCallbacks.size(); lop++){
			mCallbacks.get(lop).surfaceCreated(holder);
		}
	}
	
	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int w, int h) {
		super.surfaceChanged(holder, format, w, h);
		for(int lop=0; lop<mCallbacks.size(); lop++){
			mCallbacks.get(lop).surfaceChanged(holder, format, w, h);
		}
	}
	
	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		super.surfaceDestroyed(holder);
		for(int lop=0; lop<mCallbacks.size(); lop++){
			mCallbacks.get(lop).surfaceDestroyed(holder);
		}
	}
	
	private ArrayList<SurfaceHolder.Callback> mCallbacks = new ArrayList<SurfaceHolder.Callback>();
	public void addCallback(SurfaceHolder.Callback callback){
		if(callback==null || mCallbacks.contains(callback))
			return;
		mCallbacks.add(callback);
	}
	
	public void removeCallback(SurfaceHolder.Callback callback){
		if(callback==null || !mCallbacks.contains(callback))
			return;
		mCallbacks.remove(callback);
	}
	
	@Override
	public boolean onTouchEvent(MotionEvent e)
	{
		//we need to convert multi-touch event handling into struct of arrays for many pointers to send over JNI

		//C++ event representation is like;
		/*
			float x, y;
			int pointerIdentity;
			int pointerIndex;
		 */

		final int pointerCount = e.getPointerCount();
		final int primaryActionIndex = e.getActionIndex();
		final int primaryActionIdentifier = e.getPointerId(primaryActionIndex);

		final float[] xArray = new float[pointerCount];
		final float[] yArray = new float[pointerCount];
		final int[] pointerIdentityArray = new int[pointerCount];
		final int[] pointerIndexArray = new int[pointerCount];

		for(int pointerIndex = 0; pointerIndex < pointerCount; ++pointerIndex)
		{
			xArray[pointerIndex] = e.getX(pointerIndex);
			yArray[pointerIndex] = e.getY(pointerIndex);
			pointerIdentityArray[pointerIndex] = e.getPointerId(pointerIndex);
			pointerIndexArray[pointerIndex] = pointerIndex;
		}

		switch (e.getActionMasked())
		{
		case MotionEvent.ACTION_DOWN:
		case MotionEvent.ACTION_POINTER_DOWN:
		{
			m_nativeMessageRunner.runOnNativeThread(new Runnable()
			{
				public void run()
				{
					processNativePointerDown(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
				}
			});
		}
		break;

		case MotionEvent.ACTION_POINTER_UP:
		case MotionEvent.ACTION_UP:
		{
			m_nativeMessageRunner.runOnNativeThread(new Runnable()
			{
				public void run()
				{
					processNativePointerUp(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
				}
			});
		}
		break;

		case MotionEvent.ACTION_MOVE:
		{
			m_nativeMessageRunner.runOnNativeThread(new Runnable()
			{
				public void run()
				{
					processNativePointerMove(primaryActionIndex, primaryActionIdentifier, pointerCount, xArray, yArray, pointerIdentityArray, pointerIndexArray);
				}
			});
		}
		break;
		}

		return true;
	}
	

	public static native void processNativePointerDown(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);
	public static native void processNativePointerUp(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);
	public static native void processNativePointerMove(int primaryActionIndex, int primaryActionIdentifier, int pointerCount, float[] x, float y[], int[] pointerIdentity, int[] pointerIndex);


}
