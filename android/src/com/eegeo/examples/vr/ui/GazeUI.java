package com.eegeo.examples.vr.ui;

import android.view.View;
import android.widget.RelativeLayout;

import com.eegeo.mobilesdkharness.MainActivity;
import com.eegeo.mobilesdkharness.R;
import com.github.lzyzsd.arcprogress.ArcProgress;

public class GazeUI {
	
	private MainActivity m_activity = null;
	private View m_view = null;

	ArcProgress leftProgressArc;
	ArcProgress rightProgressArc;

	public GazeUI(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
	}

	public void CreateGazeUI()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.gaze_ui_container);
				m_view = m_activity.getLayoutInflater().inflate(R.layout.ui_gaze, uiRoot, false);
				m_view.setVisibility(View.GONE);
				uiRoot.addView(m_view);
				
				leftProgressArc = (ArcProgress) m_view.findViewById(R.id.left_progress_arc);
				rightProgressArc = (ArcProgress) m_view.findViewById(R.id.right_progress_arc);

				leftProgressArc.setProgress(0);
				rightProgressArc.setProgress(0);
			}
		});
	}


	public void DestroyView()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout) m_activity.findViewById(R.id.ui_container);
				uiRoot.removeView(m_view);
				m_view = null;
			}
		});
	}

	public void UpdateGazeProgress(final int progress)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
		        leftProgressArc.setProgress(progress);
		        rightProgressArc.setProgress(progress);
			}
		});
    }
    
    public void ShowView()
    {
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
		    	m_view.setVisibility(View.VISIBLE);
			}
		});
    }
    
    public void HideView()
    {
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
		    	m_view.setVisibility(View.INVISIBLE);
			}
		});
    }
    
}
