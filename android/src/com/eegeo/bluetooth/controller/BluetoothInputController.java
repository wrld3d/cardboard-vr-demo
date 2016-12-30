/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.eegeo.bluetooth.controller;

import com.eegeo.bluetooth.controller.InputManagerCompat.InputDeviceListener;
import com.eegeo.mobilesdkharness.NativeJniCalls;

import android.content.Context;
import android.util.Log;
import android.view.InputDevice;
import android.view.KeyEvent;
import android.view.MotionEvent;

public class BluetoothInputController implements InputDeviceListener
{
    private final String TAG = "BluetoothInputController";
    private final InputManagerCompat m_inputManager;
    private InputDevice m_inputDevice;
    private boolean m_isNightMode = false;
    
    public BluetoothInputController(Context context)
    {
        m_inputManager = InputManagerCompat.Factory.getInputManager(context);
        m_inputManager.registerInputDeviceListener(this, null);
    }
    
    // Iterate through the input devices, looking for controllers. Create a ship
    // for every device that reports itself as a gamepad or joystick.
    void findControllers()
    {
        int[] deviceIds = m_inputManager.getInputDeviceIds();
        for (int deviceId : deviceIds)
        {
            InputDevice dev = m_inputManager.getInputDevice(deviceId);
            int sources = dev.getSources();
            // if the device is a gamepad/joystick, create a ship to represent it
            if (((sources & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD) ||
                ((sources & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK))
            {
                // if the device has a gamepad or joystick
                Log.e(TAG, "Bluetooth Device " + deviceId + " added");
            }
        }
    }
    
    public void reset()
    {
        findControllers();
    }
    
    public boolean onGenericMotionEvent(MotionEvent event) {
        m_inputManager.onGenericMotionEvent(event);
        
        // Check that the event came from a joystick or gamepad since a generic
        // motion event could be almost anything. API level 18 adds the useful
        // event.isFromSource() helper function.
        int eventSource = event.getSource();
        if ((((eventSource & InputDevice.SOURCE_GAMEPAD) == InputDevice.SOURCE_GAMEPAD) ||
             ((eventSource & InputDevice.SOURCE_JOYSTICK) == InputDevice.SOURCE_JOYSTICK))
            && event.getAction() == MotionEvent.ACTION_MOVE) {
            int id = event.getDeviceId();
            if (-1 != id)
            {
                handleGenericMotionEvent(event);
            }
        }
        return false;
    }
    
    public boolean dispatchKeyEvent(KeyEvent event)
    {
        if(event.getAction() == MotionEvent.ACTION_DOWN)
        {
            return onKeyDown(event.getKeyCode(), event);
        }
        else if(event.getAction() == MotionEvent.ACTION_UP)
        {
            return onKeyUp(event.getKeyCode(), event);
        }
        return false;
    }
    
    private boolean onKeyDown(int keyCode, KeyEvent event)
    {
        boolean handled = false;
        int deviceId = event.getDeviceId();
        if (deviceId != -1)
        {
            if (event.getRepeatCount() == 0)
            {
                switch (keyCode)
                {
                    case KeyEvent.KEYCODE_DPAD_LEFT:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_DPAD_LEFT");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_RIGHT:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_DPAD_RIGHT");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_UP:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_DPAD_UP");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_DOWN:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_DPAD_DOWN");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_X:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_X");
                        m_isNightMode = !m_isNightMode;
                        NativeJniCalls.toggleNightMode(m_isNightMode);
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_A:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_A");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_Y:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_Y");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_B:
                        Log.e(TAG,"Bluetooth Event : KeyDown:  KEYCODE_B");
                        handled = true;
                        break;
                    default:
                        if (isFireKey(keyCode))
                        {
                            Log.e(TAG,"Bluetooth Event : KeyDown:  FIRE");
                            handled = true;
                        }
                        break;
                }
            }
        }
        return handled;
    }
    
    private boolean onKeyUp(int keyCode, KeyEvent event)
    {
        boolean handled = false;
        int deviceId = event.getDeviceId();
        if (deviceId != -1)
        {
            // Handle DPad keys and fire button on initial down but not on
            // auto-repeat.
            if (event.getRepeatCount() == 0)
            {
                switch (keyCode)
                {
                    case KeyEvent.KEYCODE_DPAD_LEFT:
                        Log.e(TAG,"Bluetooth Event : KeyUp:  KEYCODE_DPAD_LEFT");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_RIGHT:
                        Log.e(TAG,"Bluetooth Event : KeyUp: KEYCODE_DPAD_RIGHT");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_UP:
                        Log.e(TAG,"Bluetooth Event : KeyUp: KEYCODE_DPAD_UP");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_DPAD_DOWN:
                        Log.e(TAG,"Bluetooth Event : KeyUp: KEYCODE_DPAD_DOWN");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_X:
                        Log.e(TAG,"Bluetooth Event : KeyUp:  KEYCODE_X");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_A:
                        Log.e(TAG,"Bluetooth Event : KeyUp:  KEYCODE_A");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_Y:
                        Log.e(TAG,"Bluetooth Event : KeyUp:  KEYCODE_Y");
                        handled = true;
                        break;
                    case KeyEvent.KEYCODE_BUTTON_B:
                        Log.e(TAG,"Bluetooth Event : KeyUp:  KEYCODE_B");
                        handled = true;
                        break;
                    default:
                        if (isFireKey(keyCode))
                        {
                            Log.e(TAG,"Bluetooth Event : KeyUp: FIRE");
                            handled = true;
                        }
                        break;
                }
            }
        }
        return handled;
    }
    
    /**
     * Any gamepad button + the spacebar or DPAD_CENTER will be used as the fire
     * key.
     *
     * @param keyCode
     * @return true of it's a fire key.
     */
    private boolean isFireKey(int keyCode)
    {
        return KeyEvent.isGamepadButton(keyCode)
        || keyCode == KeyEvent.KEYCODE_DPAD_CENTER
        || keyCode == KeyEvent.KEYCODE_SPACE;
    }
    
    private boolean handleGenericMotionEvent(MotionEvent event)
    {
        // Process all historical movement samples in the batch.
        final int historySize = event.getHistorySize();
        for (int i = 0; i < historySize; i++)
        {
            processJoystickInput(event, i);
        }
        
        // Process the current movement sample in the batch.
        processJoystickInput(event, -1);
        return true;
    }
    
    private void processJoystickInput(MotionEvent event, int historyPos)
    {
        // Get joystick position.
        // Many game pads with two joysticks report the position of the
        // second
        // joystick
        // using the Z and RZ axes so we also handle those.
        // In a real game, we would allow the user to configure the axes
        // manually.
        if (null == m_inputDevice)
        {
            m_inputDevice = event.getDevice();
        }
        float x = getCenteredAxis(event, m_inputDevice, MotionEvent.AXIS_X, historyPos);
        if (x == 0)
        {
            x = getCenteredAxis(event, m_inputDevice, MotionEvent.AXIS_HAT_X, historyPos);
        }
        if (x == 0)
        {
            x = getCenteredAxis(event, m_inputDevice, MotionEvent.AXIS_Z, historyPos);
        }
        
        float y = getCenteredAxis(event, m_inputDevice, MotionEvent.AXIS_Y, historyPos);
        if (y == 0)
        {
            y = getCenteredAxis(event, m_inputDevice, MotionEvent.AXIS_HAT_Y, historyPos);
        }
        if (y == 0)
        {
            y = getCenteredAxis(event, m_inputDevice, MotionEvent.AXIS_RZ, historyPos);
        }
        Log.e(TAG, "Bluetooth Device : JoyStick : x,y " + x + "," + y);
    }
    
    private float getCenteredAxis(MotionEvent event, InputDevice device, int axis, int historyPos)
    {
        final InputDevice.MotionRange range = device.getMotionRange(axis, event.getSource());
        if (range != null)
        {
            final float flat = range.getFlat();
            final float value = historyPos < 0 ? event.getAxisValue(axis)
            : event.getHistoricalAxisValue(axis, historyPos);
            
            // Ignore axis values that are within the 'flat' region of the
            // joystick axis center.
            // A joystick at rest does not always report an absolute position of
            // (0,0).
            if (Math.abs(value) > flat)
            {
                return value;
            }
        }
        return 0;
    }

    @Override
    public void onInputDeviceAdded(int deviceId)
    {
        Log.e(TAG, "Bluetooth Device "+ deviceId +" Added");
    }

    @Override
    public void onInputDeviceChanged(int deviceId)
    {
        Log.e(TAG, "onInputDeviceChanged" + String.valueOf(InputDevice.getDevice(deviceId)));
    }

    @Override
    public void onInputDeviceRemoved(int deviceId)
    {
        Log.e(TAG, "Bluetooth Device Removed");
    }
}
