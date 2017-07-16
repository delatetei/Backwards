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

    void init(double sampleRate, float maxDelayMilliSec, float delayMilliSec);
    void recalculateReadPosition(float preDelayMilliSec);
    void processSamples(float* sample, int numSamples);

private:
    //==============================================================================
    int calculateReadPosition(int delayMilliSec, float preDelayMilliSec);

    //==============================================================================
    const float ONE_IN_MILLI = 1000.0f;

    //==============================================================================
    AudioSampleBuffer delayLine;
    int delayWritePosition;
    int delayLineLength;
    double sampleRate;
    std::list<int> delayReadPositions;
    std::vector<int> multiTapDelayMilliSec;
};