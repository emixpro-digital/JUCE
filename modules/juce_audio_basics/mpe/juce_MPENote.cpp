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

namespace
{
    uint16 generateNoteID (int midiChannel, int midiNoteNumber) noexcept
    {
        jassert (midiChannel > 0 && midiChannel <= 16);
        jassert (midiNoteNumber >= 0 && midiNoteNumber < 128);

        return uint16 ((midiChannel << 7) + midiNoteNumber);
    }
}

//==============================================================================
MPENote::MPENote (int midiChannel_,
                  int initialNote_,
                  MPEValue noteOnVelocity_,
                  MPEValue pitchbend_,
                  MPEValue pressure_,
                  MPEValue timbre_,
                  KeyState keyState_) noexcept
    : noteID (generateNoteID (midiChannel_, initialNote_)),
      midiChannel (uint8 (midiChannel_)),
      initialNote (uint8 (initialNote_)),
      noteOnVelocity (noteOnVelocity_),
      pitchbend (pitchbend_),
      pressure (pressure_),
      initialTimbre (timbre_),
      timbre (timbre_),
      keyState (keyState_)
{
    jassert (keyState != MPENote::off);
    jassert (isValid());
}

MPENote::MPENote() noexcept {}

//==============================================================================
bool MPENote::isValid() const noexcept
{
    return midiChannel > 0 && midiChannel <= 16 && initialNote < 128;
}

//==============================================================================
double MPENote::getFrequencyInHertz (double frequencyOfA) const noexcept
{
    auto pitchInSemitones = double (initialNote) + totalPitchbendInSemitones;
    return frequencyOfA * std::pow (2.0, (pitchInSemitones - 69.0) / 12.0);
}

//==============================================================================
bool MPENote::operator== (const MPENote& other) const noexcept
{
    jassert (isValid() && other.isValid());
    return noteID == other.noteID;
}

bool MPENote::operator!= (const MPENote& other) const noexcept
{
    jassert (isValid() && other.isValid());
    return noteID != other.noteID;
}


//==============================================================================
//==============================================================================
#if JUCE_UNIT_TESTS

class MPENoteTests final : public UnitTest
{
public:
    MPENoteTests()
        : UnitTest ("MPENote class", UnitTestCategories::midi)
    {}

    //==============================================================================
    void runTest() override
    {
        beginTest ("getFrequencyInHertz");
        {
            MPENote note;
            note.initialNote = 60;
            note.totalPitchbendInSemitones = -0.5;
            expectEqualsWithinOneCent (note.getFrequencyInHertz(), 254.178);
        }
    }

private:
    //==============================================================================
    void expectEqualsWithinOneCent (double frequencyInHertzActual,
                                    double frequencyInHertzExpected)
    {
        double ratio = frequencyInHertzActual / frequencyInHertzExpected;
        double oneCent = 1.0005946;
        expect (ratio < oneCent);
        expect (ratio > 1.0 / oneCent);
    }
};

static MPENoteTests MPENoteUnitTests;

#endif

} // namespace juce
