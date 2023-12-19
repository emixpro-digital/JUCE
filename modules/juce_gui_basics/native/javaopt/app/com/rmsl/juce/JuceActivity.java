/*
  ==============================================================================

   This file is part of the JUCE 8 technical preview.
   Copyright (c) Raw Material Software Limited

   You may use this code under the terms of the GPL v3
   (see www.gnu.org/licenses).

   For the technical preview this file cannot be licensed commercially.

   JUCE IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL WARRANTIES, WHETHER
   EXPRESSED OR IMPLIED, INCLUDING MERCHANTABILITY AND FITNESS FOR PURPOSE, ARE
   DISCLAIMED.

  ==============================================================================
*/

package com.rmsl.juce;

import android.app.Activity;
import android.content.Intent;

//==============================================================================
public class JuceActivity   extends Activity
{
    //==============================================================================
    private native void appNewIntent (Intent intent);
    private native void appOnResume();

    @Override
    protected void onNewIntent (Intent intent)
    {
        super.onNewIntent(intent);
        setIntent(intent);

        appNewIntent (intent);
    }

    @Override
    protected void onResume()
    {
        super.onResume();

        appOnResume();
    }
}
