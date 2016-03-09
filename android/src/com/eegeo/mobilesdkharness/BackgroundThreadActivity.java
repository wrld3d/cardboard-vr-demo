//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.mobilesdkharness;

import javax.microedition.khronos.egl.EGLConfig;

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Vibrator;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.SurfaceHolder;

import com.google.vrtoolkit.cardboard.CardboardActivity;
import com.google.vrtoolkit.cardboard.CardboardView;
import com.google.vrtoolkit.cardboard.Eye;
import com.google.vrtoolkit.cardboard.HeadTransform;
import com.google.vrtoolkit.cardboard.Viewport;



public class BackgroundThreadActivity extends CardboardActivity implements CardboardView.StereoRenderer, SurfaceHolder.Callback, INativeMessageRunner
{
	private static final String TAG = "BackgroundThreadActivity";
	
	private CardboardViewWithSurfaceHolder m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
//	private ThreadedUpdateRunner m_threadedRunner;
//	private Thread m_updater;

	static {
		System.loadLibrary("eegeo-sdk-samples");
	}
	

	private Vibrator vibrator;
	  
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);

	    vibrator = (Vibrator) getSystemService(Context.VIBRATOR_SERVICE);
	    
		m_surfaceView = (CardboardViewWithSurfaceHolder)findViewById(R.id.surface);
		m_surfaceView.getHolder().addCallback(this);
		m_surfaceView.setActivity(this);


		m_surfaceView.setRestoreGLStateEnabled(false);
		m_surfaceView.setRenderer(this);
	    setCardboardView(m_surfaceView);
		
		DisplayMetrics dm = getResources().getDisplayMetrics();
		final float dpi = dm.ydpi;
		final Activity activity = this;

//		m_threadedRunner = new ThreadedUpdateRunner(false);
//		m_updater = new Thread(m_threadedRunner);
//		m_updater.start();

//		m_threadedRunner.blockUntilThreadStartedRunning();

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_nativeAppWindowPtr = NativeJniCalls.createNativeCode(activity, getAssets(), dpi);

				if(m_nativeAppWindowPtr == 0)
				{
					throw new RuntimeException("Failed to start native code.");
				}
			}
		});
	}

	public void runOnNativeThread(Runnable runnable)
	{
		m_surfaceView.queueEvent(runnable);
//		m_threadedRunner.postTo(runnable);
	}

	@Override
	protected void onResume()
	{
		super.onResume();
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				NativeJniCalls.resumeNativeCode();
//				m_threadedRunner.start();
				
				if(m_surfaceHolder != null && m_surfaceHolder.getSurface() != null)
				{
					NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
				}
			}
		});
	}

	@Override
	protected void onPause()
	{
		super.onPause();
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
//				m_threadedRunner.stop();
				NativeJniCalls.pauseNativeCode();
			}
		});
	}

	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
//				m_threadedRunner.stop();
				NativeJniCalls.destroyNativeCode();
//				m_threadedRunner.destroyed();
			}
		});

//		m_threadedRunner.blockUntilThreadHasDestroyedPlatform();
		m_nativeAppWindowPtr = 0;
	}
	
	@Override
	public void surfaceCreated(SurfaceHolder holder)
	{
		//nothing to do
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder)
	{

		System.out.println("surface destroyed");
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
//				m_threadedRunner.stop();
			}
		});
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		final SurfaceHolder h = holder;
		
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_surfaceHolder = h;
				if(m_surfaceHolder != null) 
				{
					NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
				}
			}
		});
	}



	private long m_endOfLastFrameNano = System.nanoTime();
	private float m_frameThrottleDelaySeconds = 1.0f/60.0f;
	 
	@Override
	public void onDrawEye(Eye eye) {
		
		if(eye.getType() == Eye.Type.RIGHT)
			return;
		
		long timeNowNano = System.nanoTime();
		long nanoDelta = timeNowNano - m_endOfLastFrameNano;
		float deltaSeconds = (float)((double)nanoDelta / 1e9);
		
		if(deltaSeconds > m_frameThrottleDelaySeconds)
		{
			NativeJniCalls.updateNativeCode(deltaSeconds);
			m_endOfLastFrameNano = timeNowNano;
		}
		
	}

	@Override
	public void onFinishFrame(Viewport viewport) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onNewFrame(HeadTransform headtransform) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void onRendererShutdown() {
		// TODO Auto-generated method stub
		
	}

	  @Override
	  public void onSurfaceChanged(int width, int height) {
	    Log.i(TAG, "onSurfaceChanged");
	  }

	  @Override
	  public void onSurfaceCreated(EGLConfig config) {
		// TODO Auto-generated method stub
		
	}
	  

	  /**
	   * Called when the Cardboard trigger is pulled.
	   */
	  @Override
	  public void onCardboardTrigger() {
	    Log.i(TAG, "onCardboardTrigger");

//	    if (isLookingAtObject()) {
//	      score++;
//	      overlayView.show3DToast("Found it! Look around for another one.\nScore = " + score);
//	      hideObject();
//	    } else {
//	      overlayView.show3DToast("Look around to find the object!");
//	    }

	    // Always give user feedback.
	    vibrator.vibrate(50);
	  }

}