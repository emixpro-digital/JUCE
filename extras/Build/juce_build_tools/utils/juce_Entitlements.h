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

namespace juce::build_tools
{

    struct EntitlementOptions final
    {
        String getEntitlementsFileContent() const;

        ProjectType::Target::Type type      = ProjectType::Target::GUIApp;

        bool isiOS                          = false;
        bool isAudioPluginProject           = false;
        bool shouldEnableIAA                = false;
        bool isAUPluginHost                 = false;
        bool isiCloudPermissionsEnabled     = false;
        bool isPushNotificationsEnabled     = false;
        bool isAppGroupsEnabled             = false;
        bool isHardenedRuntimeEnabled       = false;
        bool isAppSandboxEnabled            = false;
        bool isAppSandboxInhertianceEnabled = false;
        bool isNetworkingMulticastEnabled   = false;

        String appGroupIdString;

        StringArray hardenedRuntimeOptions;
        StringArray appSandboxOptions;

        struct KeyAndStringArray
        {
            String key;
            StringArray values;
        };

        std::vector<KeyAndStringArray> appSandboxTemporaryPaths;
        StringArray appSandboxExceptionIOKit;

    private:
        StringPairArray getEntitlements() const;
    };

} // namespace juce::build_tools
