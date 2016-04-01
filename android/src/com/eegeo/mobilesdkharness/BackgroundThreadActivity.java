//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.mobilesdkharness;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.util.DisplayMetrics;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.WindowManager;

import com.google.vrtoolkit.cardboard.CardboardDeviceParams;
import com.google.vrtoolkit.cardboard.DistortionRenderer;
import com.google.vrtoolkit.cardboard.ScreenParams;
import com.google.vrtoolkit.cardboard.proto.nano.CardboardDevice.DeviceParams;
import com.google.vrtoolkit.cardboard.sensors.HeadTracker;
import com.google.vrtoolkit.cardboard.sensors.MagnetSensor;
import com.google.vrtoolkit.cardboard.sensors.MagnetSensor.OnCardboardTriggerListener;
import com.google.vrtoolkit.cardboard.sensors.NfcSensor;
import com.google.vrtoolkit.cardboard.sensors.NfcSensor.OnCardboardNfcListener;

public class BackgroundThreadActivity extends MainActivity
{

	private static final float METERS_PER_INCH = 0.0254f;

	private EegeoSurfaceView m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
	private ThreadedUpdateRunner m_threadedRunner;
	private Thread m_updater;

	private DistortionRenderer m_distortionRenderer;
//	private CardboardView m_cardboardView;
	private HeadTracker m_headTracker; 
	private MagnetSensor m_magnetSensor;
	
	private NfcSensor mNfcSensor;
	private ScreenParams mParams;
	
	static {
		System.loadLibrary("eegeo-sdk-samples");
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);

		DisplayMetrics dm = getResources().getDisplayMetrics();
		final float dpi = dm.ydpi;
		final Activity activity = this;
		
		mParams = new ScreenParams(getWindowManager().getDefaultDisplay());
		
		m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
		m_surfaceView.getHolder().addCallback(this);
		m_surfaceView.setActivity(this);

		m_headTracker = HeadTracker.createFromContext(this);
		m_headTracker.setGyroBiasEstimationEnabled(true);
		m_headTracker.startTracking();
		
		m_magnetSensor = new MagnetSensor(this);
		m_magnetSensor.setOnCardboardTriggerListener(new OnCardboardTriggerListener() {
			
			@Override
			public void onCardboardTrigger() {
				runOnNativeThread(new Runnable() {
					public void run() {
						NativeJniCalls.magnetTriggered();
					}
				});
			}
		});
		m_magnetSensor.start();

		mNfcSensor = NfcSensor.getInstance(this);
		mNfcSensor.addOnCardboardNfcListener(new OnCardboardNfcListener() {
			@Override
			public void onRemovedFromCardboard() {
				System.out.println("On Removed From Cardboard.");
			}
			
			@Override
			public void onInsertedIntoCardboard(CardboardDeviceParams params) {
				System.out.println("params: "+params.getDistortion().getCoefficients()[0]);
			}
		});
		
		
		m_distortionRenderer = new DistortionRenderer();
		m_distortionRenderer.setVignetteEnabled(true);
		m_distortionRenderer.setChromaticAberrationCorrectionEnabled(true);

//		m_distortionRenderer.onFovChanged(hmd, leftFov, rightFov, virtualEyeToScreenDistance)
		
//		m_cardboardView = new CardboardView(this);
//		m_cardboardView.setVignetteEnabled(true);
//		m_cardboardView.setVRModeEnabled(true);
//		m_cardboardView.updateCardboardDeviceParams(CardboardDeviceParams.cardboardV1DeviceParams());
		
		
		m_threadedRunner = new ThreadedUpdateRunner(false);
		m_updater = new Thread(m_threadedRunner);
		m_updater.start();

		m_threadedRunner.blockUntilThreadStartedRunning();

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_nativeAppWindowPtr = NativeJniCalls.createNativeCode(activity, getAssets(), dpi);
				if(m_nativeAppWindowPtr == 0)
				{
					throw new RuntimeException("Failed to start native code.");
				}
//				NativeJniCalls.updateCardboardProfile(getUpdatedCardboardProfile());
			}
		});
	}

	private float[] getUpdatedCardboardProfile(){

		float cardboardProperties[] = {
                50, //Outer
                50, //Upper
                50, //Inner
                50, //Lower
    	        mParams.getWidthMeters(), //Width
    	        mParams.getHeightMeters(), //Height
    	        mParams.getBorderSizeMeters(), //Border
                0.062f, //Separation
                0.035f, //Offset
                0.037f, //Screen Distance
                1, //Alignment
                0.26f, //K1
                0.27f  //K2
            };
		
		return cardboardProperties;

	}
	
	public void SetHeadMountedDisplayResolution(int width, int height) {
		
//		try {
//			if (m_cardboardView == null)
//				return;
//			
//			Display display = getWindowManager().getDefaultDisplay();
//			ScreenParams sp = new ScreenParams(display);
//			Phone.PhoneParams pp = new Phone.PhoneParams();
//			pp.setXPpi(width / sp.getWidthMeters() * METERS_PER_INCH);
//			pp.setYPpi(height / sp.getHeightMeters() * METERS_PER_INCH);
//			sp = ScreenParams.fromProto(display, pp);
//			
//			sp.setWidth(width);
//			sp.setHeight(height);
//			m_cardboardView.updateScreenParams(sp);
//			
//		} catch (Exception e) {
//			Log.e("backgroundThreadActivity", "exception", e);
//		}
	}
	
	public void UndistortTexture(int textureId){
		
//		try {
//				m_cardboardView.undistortTexture(textureId);
//		    } catch (Exception e) {
//		      Log.e("backgroundThreadActivity", "exception", e);
//		    }
	}
	
	@SuppressLint("InlinedApi") 
	private void setScreenSettings(){
			getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
		if(android.os.Build.VERSION.SDK_INT<16)
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION);
		else if(android.os.Build.VERSION.SDK_INT<19)
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_FULLSCREEN);
		else
			getWindow().getDecorView().setSystemUiVisibility(View.SYSTEM_UI_FLAG_HIDE_NAVIGATION | View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY | View.SYSTEM_UI_FLAG_FULLSCREEN);
	}
	
	public void runOnNativeThread(Runnable runnable)
	{
		m_threadedRunner.postTo(runnable);
	}

	@Override
	protected void onResume()
	{
		super.onResume();

		setScreenSettings();
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				NativeJniCalls.resumeNativeCode();
				m_threadedRunner.start();
				
				if(m_surfaceHolder != null && m_surfaceHolder.getSurface() != null)
				{
					NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
				}
			}
		});
		
//		getWindow().getDecorView().postDelayed(new Runnable(	) {
//			
//			@Override
//			public void run() {
//				runOnUiThread( new Runnable() {
//					public void run() {
//					
//				NativeJniCalls.updateCardboardProfile(getUpdatedCardboardProfile());	
//					}
//				});
//			}
//		}, 500);
	}

	@Override
	protected void onPause()
	{
		super.onPause();

//        if (m_cardboardView != null) {
//        	m_cardboardView.onPause();
//        }
        
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
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
				m_threadedRunner.stop();
				NativeJniCalls.destroyNativeCode();
				m_threadedRunner.destroyed();
				android.os.Process.killProcess(android.os.Process.myPid());
			}
		});

		m_threadedRunner.blockUntilThreadHasDestroyedPlatform();
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

		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
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
					m_threadedRunner.start();
				}
			}
		});
	}

	private class ThreadedUpdateRunner implements Runnable
	{
		private long m_endOfLastFrameNano;
		private boolean m_running;
		private Handler m_nativeThreadHandler;
		private float m_frameThrottleDelaySeconds;
		private boolean m_destroyed;

		public ThreadedUpdateRunner(boolean running)
		{
			m_endOfLastFrameNano = System.nanoTime();
			m_running = false;
			m_destroyed = false;

			// We need higher FPS of 60 for better VR
			float targetFramesPerSecond = 30.f; //30.f;
			m_frameThrottleDelaySeconds = 1.f/targetFramesPerSecond;
		}

		synchronized void blockUntilThreadStartedRunning()
		{
			while(m_nativeThreadHandler == null);
		}

		synchronized void blockUntilThreadHasDestroyedPlatform()
		{
			while(!m_destroyed);
		}

		public void postTo(Runnable runnable)
		{
			m_nativeThreadHandler.post(runnable);
		}

		public void start()
		{
			m_running = true;
		}

		public void stop()
		{
			m_running = false;
		}

		public void destroyed()
		{
			m_destroyed = true;
		}

		public void run()
		{
			Looper.prepare();
			m_nativeThreadHandler = new Handler();

			while(true)
			{
				runOnNativeThread(new Runnable()
				{
					public void run()
					{
						long timeNowNano = System.nanoTime();
						long nanoDelta = timeNowNano - m_endOfLastFrameNano;
						float deltaSeconds = (float)((double)nanoDelta / 1e9);
						
						if(deltaSeconds > m_frameThrottleDelaySeconds)
						{
							float[] headTransform = new float[16];
							m_headTracker.getLastHeadView(headTransform, 0);
							if(m_running)
							{
								NativeJniCalls.updateNativeCode(deltaSeconds, headTransform);
							}
							else
							{
								SystemClock.sleep(200);
							}

							m_endOfLastFrameNano = timeNowNano;
						}

						runOnNativeThread(this);
					}
				});

				Looper.loop();
			}
		}
	}
}
