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

AudioSourcePlayer::AudioSourcePlayer()
{
}

AudioSourcePlayer::~AudioSourcePlayer()
{
    setSource (nullptr);
}

void AudioSourcePlayer::setSource (AudioSource* newSource)
{
    if (source != newSource)
    {
        auto* oldSource = source;

        if (newSource != nullptr && bufferSize > 0 && sampleRate > 0)
            newSource->prepareToPlay (bufferSize, sampleRate);

        {
            const ScopedLock sl (readLock);
            source = newSource;
        }

        if (oldSource != nullptr)
            oldSource->releaseResources();
    }
}

void AudioSourcePlayer::setGain (const float newGain) noexcept
{
    gain = newGain;
}

void AudioSourcePlayer::audioDeviceIOCallbackWithContext (const float* const* inputChannelData,
                                                          int totalNumInputChannels,
                                                          float* const* outputChannelData,
                                                          int totalNumOutputChannels,
                                                          int numSamples,
                                                          [[maybe_unused]] const AudioIODeviceCallbackContext& context)
{
    // these should have been prepared by audioDeviceAboutToStart()...
    jassert (sampleRate > 0 && bufferSize > 0);

    const ScopedLock sl (readLock);

    if (source != nullptr)
    {
        int numActiveChans = 0, numInputs = 0, numOutputs = 0;

        // messy stuff needed to compact the channels down into an array
        // of non-zero pointers..
        for (int i = 0; i < totalNumInputChannels; ++i)
        {
            if (inputChannelData[i] != nullptr)
            {
                inputChans [numInputs++] = inputChannelData[i];
                if (numInputs >= numElementsInArray (inputChans))
                    break;
            }
        }

        for (int i = 0; i < totalNumOutputChannels; ++i)
        {
            if (outputChannelData[i] != nullptr)
            {
                outputChans [numOutputs++] = outputChannelData[i];
                if (numOutputs >= numElementsInArray (outputChans))
                    break;
            }
        }

        if (numInputs > numOutputs)
        {
            // if there aren't enough output channels for the number of
            // inputs, we need to create some temporary extra ones (can't
            // use the input data in case it gets written to)
            tempBuffer.setSize (numInputs - numOutputs, numSamples,
                                false, false, true);

            for (int i = 0; i < numOutputs; ++i)
            {
                channels[numActiveChans] = outputChans[i];
                memcpy (channels[numActiveChans], inputChans[i], (size_t) numSamples * sizeof (float));
                ++numActiveChans;
            }

            for (int i = numOutputs; i < numInputs; ++i)
            {
                channels[numActiveChans] = tempBuffer.getWritePointer (i - numOutputs);
                memcpy (channels[numActiveChans], inputChans[i], (size_t) numSamples * sizeof (float));
                ++numActiveChans;
            }
        }
        else
        {
            for (int i = 0; i < numInputs; ++i)
            {
                channels[numActiveChans] = outputChans[i];
                memcpy (channels[numActiveChans], inputChans[i], (size_t) numSamples * sizeof (float));
                ++numActiveChans;
            }

            for (int i = numInputs; i < numOutputs; ++i)
            {
                channels[numActiveChans] = outputChans[i];
                zeromem (channels[numActiveChans], (size_t) numSamples * sizeof (float));
                ++numActiveChans;
            }
        }

        AudioBuffer<float> buffer (channels, numActiveChans, numSamples);

        AudioSourceChannelInfo info (&buffer, 0, numSamples);
        source->getNextAudioBlock (info);

        for (int i = info.buffer->getNumChannels(); --i >= 0;)
            buffer.applyGainRamp (i, info.startSample, info.numSamples, lastGain, gain);

        lastGain = gain;
    }
    else
    {
        for (int i = 0; i < totalNumOutputChannels; ++i)
            if (outputChannelData[i] != nullptr)
                zeromem (outputChannelData[i], (size_t) numSamples * sizeof (float));
    }
}

void AudioSourcePlayer::audioDeviceAboutToStart (AudioIODevice* device)
{
    prepareToPlay (device->getCurrentSampleRate(),
                   device->getCurrentBufferSizeSamples());
}

void AudioSourcePlayer::prepareToPlay (double newSampleRate, int newBufferSize)
{
    sampleRate = newSampleRate;
    bufferSize = newBufferSize;
    zeromem (channels, sizeof (channels));

    if (source != nullptr)
        source->prepareToPlay (bufferSize, sampleRate);
}

void AudioSourcePlayer::audioDeviceStopped()
{
    if (source != nullptr)
        source->releaseResources();

    sampleRate = 0.0;
    bufferSize = 0;

    tempBuffer.setSize (2, 8);
}

} // namespace juce
