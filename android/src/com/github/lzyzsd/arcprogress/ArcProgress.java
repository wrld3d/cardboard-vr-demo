package com.github.lzyzsd.arcprogress;

import android.content.Context;
import android.content.res.TypedArray;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.RectF;
import android.os.Bundle;
import android.os.Parcelable;
import android.text.TextPaint;
import android.text.TextUtils;
import android.util.AttributeSet;
import android.view.View;

/**
 * Created by bruce on 11/6/14.
 */
public class ArcProgress extends View {
    private Paint paint;

    private RectF rectF = new RectF();

    private float strokeWidth = 8;
    private int progress = 35;
    private int max = 100;
    private float arcAngle = 360;


    private static final String INSTANCE_STATE = "saved_instance";
    private static final String INSTANCE_STROKE_WIDTH = "stroke_width";
    private static final String INSTANCE_PROGRESS = "progress";
    private static final String INSTANCE_MAX = "max";
    private static final String INSTANCE_FINISHED_STROKE_COLOR = "finished_stroke_color";
    private static final String INSTANCE_UNFINISHED_STROKE_COLOR = "unfinished_stroke_color";
    private static final String INSTANCE_ARC_ANGLE = "arc_angle";

    public ArcProgress(Context context) {
        this(context, null);
    }

    public ArcProgress(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
    }

    public ArcProgress(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    protected void init() {
    	
        paint = new Paint();
        paint.setColor(Color.BLACK);
        paint.setAntiAlias(true);
        paint.setStrokeWidth(strokeWidth);
        paint.setStyle(Paint.Style.STROKE);
        paint.setStrokeCap(Paint.Cap.ROUND);
    }

    @Override
    public void invalidate() {
        init();
        super.invalidate();
    }

    public float getStrokeWidth() {
        return strokeWidth;
    }

    public void setStrokeWidth(float strokeWidth) {
        this.strokeWidth = strokeWidth;
        this.invalidate();
    }


    public int getProgress() {
        return progress;
    }

    public void setProgress(int progress) {
        this.progress = progress;
        if (this.progress > getMax()) {
            this.progress %= getMax();
        }
        invalidate();
    }

    public int getMax() {
        return max;
    }

    public void setMax(int max) {
        if (max > 0) {
            this.max = max;
            invalidate();
        }
    }



    public float getArcAngle() {
        return arcAngle;
    }

    public void setArcAngle(float arcAngle) {
        this.arcAngle = arcAngle;
        this.invalidate();
    }



    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        setMeasuredDimension(widthMeasureSpec, heightMeasureSpec);
        int width = MeasureSpec.getSize(widthMeasureSpec);
        rectF.set(strokeWidth / 2f, strokeWidth / 2f, width - strokeWidth / 2f, MeasureSpec.getSize(heightMeasureSpec) - strokeWidth / 2f);
        float radius = width / 2f;
        float angle = (360 - arcAngle) / 2f;
    }

    @Override
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        float startAngle = 270 - arcAngle / 2f;
        float finishedSweepAngle = progress / (float) getMax() * arcAngle;
        float finishedStartAngle = startAngle;
        
        paint.setColor(Color.WHITE);
        paint.setStyle(Paint.Style.FILL);
        paint.setAlpha(105);
        canvas.drawCircle(rectF.centerX(), rectF.centerY(), rectF.width()/2.5f, paint);
        
        paint.setColor(Color.BLACK);
        paint.setAlpha(255);
        canvas.drawCircle(rectF.centerX(), rectF.centerY(), rectF.width()/4f, paint);
        
        paint.setStyle(Paint.Style.STROKE);
        paint.setColor(Color.WHITE);
        canvas.drawArc(rectF, finishedStartAngle, finishedSweepAngle, false, paint);

    }

    @Override
    protected Parcelable onSaveInstanceState() {
        final Bundle bundle = new Bundle();
        bundle.putParcelable(INSTANCE_STATE, super.onSaveInstanceState());
        bundle.putFloat(INSTANCE_STROKE_WIDTH, getStrokeWidth());
        bundle.putInt(INSTANCE_PROGRESS, getProgress());
        bundle.putInt(INSTANCE_MAX, getMax());
        bundle.putFloat(INSTANCE_ARC_ANGLE, getArcAngle());
        return bundle;
    }

    @Override
    protected void onRestoreInstanceState(Parcelable state) {
        if(state instanceof Bundle) {
            final Bundle bundle = (Bundle) state;
            strokeWidth = bundle.getFloat(INSTANCE_STROKE_WIDTH);
            setMax(bundle.getInt(INSTANCE_MAX));
            setProgress(bundle.getInt(INSTANCE_PROGRESS));
            init();
            super.onRestoreInstanceState(bundle.getParcelable(INSTANCE_STATE));
            return;
        }
        super.onRestoreInstanceState(state);
    }
}
