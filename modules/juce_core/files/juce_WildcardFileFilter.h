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

namespace juce
{

//==============================================================================
/**
    A type of FileFilter that works by wildcard pattern matching.

    This filter only allows files that match one of the specified patterns, but
    allows all directories through.

    @see FileFilter, DirectoryContentsList, FileListComponent, FileBrowserComponent

    @tags{Core}
*/
class JUCE_API  WildcardFileFilter  : public FileFilter
{
public:
    //==============================================================================
    /**
        Creates a wildcard filter for one or more patterns.

        The wildcardPatterns parameter is a comma or semicolon-delimited set of
        patterns, e.g. "*.wav;*.aiff" would look for files ending in either .wav
        or .aiff.

        Passing an empty string as a pattern will fail to match anything, so by leaving
        either the file or directory pattern parameter empty means you can control
        whether files or directories are found.

        The description is a name to show the user in a list of possible patterns, so
        for the wav/aiff example, your description might be "audio files".
    */
    WildcardFileFilter (const String& fileWildcardPatterns,
                        const String& directoryWildcardPatterns,
                        const String& filterDescription);

    /** Destructor. */
    ~WildcardFileFilter() override;

    //==============================================================================
    /** Returns true if the filename matches one of the patterns specified. */
    bool isFileSuitable (const File& file) const override;

    /** This always returns true. */
    bool isDirectorySuitable (const File& file) const override;

private:
    //==============================================================================
    StringArray fileWildcards, directoryWildcards;

    JUCE_LEAK_DETECTOR (WildcardFileFilter)
};

} // namespace juce
