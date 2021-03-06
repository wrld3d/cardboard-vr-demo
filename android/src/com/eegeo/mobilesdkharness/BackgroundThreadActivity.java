//Copyright eeGeo Ltd (2012-2014), All Rights Reserved

package com.eegeo.mobilesdkharness;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.SystemClock;
import android.util.DisplayMetrics;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.WindowManager;

import com.eegeo.bluetooth.controller.BluetoothInputController;
import com.eegeo.cardboardvrdemo.R;

public class BackgroundThreadActivity extends MainActivity
{
	private EegeoSurfaceView m_surfaceView;
	private SurfaceHolder m_surfaceHolder;
	private long m_nativeAppWindowPtr;
	private ThreadedUpdateRunner m_threadedRunner;
	private Thread m_updater;
	private VRModule m_vrModule;
	private BluetoothInputController m_bluetoothInputController;
	
	static {
		System.loadLibrary("eegeo-sdk-samples");
	}
	
	@Override
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);

		setContentView(R.layout.activity_main);

		m_surfaceView = (EegeoSurfaceView)findViewById(R.id.surface);
		m_surfaceView.getHolder().addCallback(this);
		m_surfaceView.setActivity(this);

		m_vrModule = new VRModule(this);
		m_bluetoothInputController = new BluetoothInputController(this);
		DisplayMetrics dm = getResources().getDisplayMetrics();
		final float dpi = dm.ydpi;
		final Activity activity = this;

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
			}
		});
	}
	public void ResetTracker()
	{
		m_vrModule.resetTracker();
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
		m_bluetoothInputController.reset();
		setScreenSettings();
	}

	@Override
	protected void onPause()
	{
		super.onPause();
	}

	@Override
	protected void onDestroy()
	{
		super.onDestroy();
		if(m_threadedRunner == null)
		{
			return;
		}
		
		runOnNativeThread(new Runnable()
        {
            public void run()
            {
                NativeJniCalls.stopUpdatingNativeCode();
                m_threadedRunner.flagUpdatingNativeCodeStopped();
            }
        });

        m_threadedRunner.blockUntilThreadHasStoppedUpdatingPlatform();
        
		m_vrModule.stopTracker();
		runOnNativeThread(new Runnable()
		{
			public void run()
			{
				m_threadedRunner.stop();
				NativeJniCalls.destroyNativeCode();
				m_threadedRunner.destroyed();
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
				NativeJniCalls.pauseNativeCode();
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
					long oldWindow = NativeJniCalls.setNativeSurface(m_surfaceHolder.getSurface());
					m_threadedRunner.start();
					releaseNativeWindowDeferred(oldWindow);
					
					NativeJniCalls.updateCardboardProfile(m_vrModule.getUpdatedCardboardProfile());
					NativeJniCalls.resumeNativeCode();
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
		private boolean m_stoppedUpdatingPlatformBeforeTeardown;

		public ThreadedUpdateRunner(boolean running)
		{
			m_endOfLastFrameNano = System.nanoTime();
			m_running = false;
			m_destroyed = false;
			m_stoppedUpdatingPlatformBeforeTeardown = false;
			
			// We need higher FPS of 60 for better VR
			float targetFramesPerSecond = 60.f; //30.f;
			m_frameThrottleDelaySeconds = 1.f/targetFramesPerSecond;
		}

		synchronized void blockUntilThreadStartedRunning()
		{
			while(m_nativeThreadHandler == null);
		}

		synchronized void blockUntilThreadHasDestroyedPlatform()
		{
			while(!m_destroyed)
			{
				SystemClock.sleep(200);
			}
		}
		
		synchronized void blockUntilThreadHasStoppedUpdatingPlatform()
        {
            while(!m_stoppedUpdatingPlatformBeforeTeardown)
            {
                SystemClock.sleep(200);
            }
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
		
		void flagUpdatingNativeCodeStopped()
        {
            m_stoppedUpdatingPlatformBeforeTeardown = true;
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
							if(m_running)
							{
								m_vrModule.updateNativeCode(deltaSeconds);
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
	
	@Override
	public boolean dispatchKeyEvent(KeyEvent event)
	{
		return m_bluetoothInputController.dispatchKeyEvent(event);
	}
	
	@Override
	public boolean dispatchGenericMotionEvent(MotionEvent event)
	{
		return m_bluetoothInputController.onGenericMotionEvent(event);
	}
	
	public void releaseNativeWindowDeferred(final long oldWindow)
    {
        runOnNativeThread(new Runnable() {
            @Override
            public void run() {
                NativeJniCalls.releaseNativeWindow(oldWindow);
            }
        });
    }
}
