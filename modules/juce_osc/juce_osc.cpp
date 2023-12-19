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

#ifdef JUCE_OSC_H_INCLUDED
 /* When you add this cpp file to your project, you mustn't include it in a file where you've
    already included any other headers - just put it inside a file on its own, possibly with your config
    flags preceding it, but don't include anything else. That also includes avoiding any automatic prefix
    header files that the compiler may be using.
 */
 #error "Incorrect use of JUCE cpp file"
#endif

#include "juce_osc.h"

#include "osc/juce_OSCTypes.cpp"
#include "osc/juce_OSCTimeTag.cpp"
#include "osc/juce_OSCArgument.cpp"
#include "osc/juce_OSCAddress.cpp"
#include "osc/juce_OSCMessage.cpp"
#include "osc/juce_OSCBundle.cpp"
#include "osc/juce_OSCReceiver.cpp"
#include "osc/juce_OSCSender.cpp"
