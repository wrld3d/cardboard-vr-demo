package com.eegeo.examples.vr.ui;

import android.view.View;
import android.widget.FrameLayout;
import android.widget.RelativeLayout;

import com.eegeo.mobilesdkharness.MainActivity;
import com.eegeo.mobilesdkharness.R;
import com.github.lzyzsd.arcprogress.ArcProgress;
import com.github.lzyzsd.arcprogress.ArcProgress.SizeMeasureListner;

public class GazeUI {

	private float m_centerX;
	private float m_centerY;
	private float deltaX;
	private float deltaY;
	
	private MainActivity m_activity = null;
	private View m_view = null;

	ArcProgress leftProgressArc;
	ArcProgress rightProgressArc;

	public GazeUI(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_centerX = m_centerY = deltaX = deltaY = 0;
	}

	public void CreateGazeUI()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.gaze_ui_container);
				m_view = m_activity.getLayoutInflater().inflate(R.layout.ui_gaze, uiRoot, false);
				uiRoot.addView(m_view);
				m_view.setVisibility(View.GONE);

				leftProgressArc  = (ArcProgress) m_view.findViewById(R.id.left_progress_arc);
				rightProgressArc = (ArcProgress) m_view.findViewById(R.id.right_progress_arc);

				leftProgressArc.setProgress(0);
				rightProgressArc.setProgress(0);
				
				leftProgressArc.setSizeMeasureListner(new SizeMeasureListner() {
					@Override
					public void OnSizeMeasured(float width, float height) {
						deltaX = width/2f;
						deltaY = height/2f;
						if(m_centerX>0)
							updatePositions();
					}
				});
				
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
    	updatePositions();
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

    
    public void SetCenterPoint(float x, float y){
    	
    	this.m_centerX = x;
    	this.m_centerY = y;
    	if(deltaX>0)
    		updatePositions();
    }
    
    void updatePositions(){

		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				leftProgressArc.setX(m_centerX-deltaX);
				leftProgressArc.setY(m_centerY+deltaY);
				rightProgressArc.setX(m_centerX*3f-deltaX);
				rightProgressArc.setY(m_centerY+deltaY);	
				
			}
		});
    }
    
}
