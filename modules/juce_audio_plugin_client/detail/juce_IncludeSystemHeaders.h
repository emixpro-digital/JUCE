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

#if JUCE_WINDOWS
 #undef _WIN32_WINNT
 #define _WIN32_WINNT 0x500
 #undef STRICT
 #define STRICT 1
 #include <windows.h>
 #include <float.h>
 #if JUCE_MSVC
  #pragma warning (disable : 4312 4355)
 #endif
 #ifdef __INTEL_COMPILER
  #pragma warning (disable : 1899)
 #endif
#elif JUCE_LINUX || JUCE_BSD
 #include <float.h>
 #include <sys/time.h>
 #include <arpa/inet.h>
#elif JUCE_MAC || JUCE_IOS
 #ifdef __OBJC__
  #if JUCE_MAC
   #include <Cocoa/Cocoa.h>
  #elif JUCE_IOS
   #include <UIKit/UIKit.h>
  #else
   #error
  #endif
 #endif

 #include <objc/runtime.h>
 #include <objc/objc.h>
 #include <objc/message.h>
#endif
