/*
  ==============================================================================

    MultiTapDelayLine.h

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MultiTapDelayLine
{
public:
    MultiTapDelayLine(std::vector<int> multiTapDelayMilliSec);
    ~MultiTapDelayLine();

    void init(double sampleRate, float maxDelayMilliSec, float delayMilliSec, float maxRoomSize, float roomSize);
    void processSamples(float* sample, int numSamples);
    void updateDelayReadPosition(double sampleRate, float preDelayMilliSec, float roomSize);

private:
    void updateLivenessCoefficient();
    //==============================================================================
    const float ONE_IN_MILLI = 1000.0f;
    const float INTERVAL_MILLI_SEC = 30.0f;

    //==============================================================================
    AudioSampleBuffer delayLine;
    int delayWritePosition;
    int delayLineLength;
    std::vector<int> delayReadPositions;
    std::vector<int> multiTapDelayMilliSec;
    std::vector<float> livenessCoefficients;
};