/*
  ==============================================================================

    MultiTapDelayLine.h

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <list>

class MultiTapDelayLine
{
public:
    MultiTapDelayLine(std::vector<int> multiTapDelayMilliSec);
    ~MultiTapDelayLine();

    void init(double sampleRate, float maxDelayMilliSec, float delayMilliSec, float liveness);
    void processSamples(float* sample, int numSamples);
    void updateDelayReadPosition(float preDelayMilliSec);
    void updateLivenessCoefficient(float liveness);

private:
    //==============================================================================
    const float ONE_IN_MILLI = 1000.0f;

    //==============================================================================
    AudioSampleBuffer delayLine;
    int delayWritePosition;
    int delayLineLength;
    double sampleRate;
    std::vector<int> delayReadPositions;
    std::vector<int> multiTapDelayMilliSec;
    std::vector<float> livenessCoefficients;
};