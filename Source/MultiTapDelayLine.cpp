/*
  ==============================================================================

    MultiTapDelayLine.cpp

  ==============================================================================
*/

#include "MultiTapDelayLine.h"
#include <algorithm>

MultiTapDelayLine::MultiTapDelayLine(std::vector<int> multiTapDelayMilliSec)
    :
    delayLine(1, 1),
    delayWritePosition(0),
    multiTapDelayMilliSec(multiTapDelayMilliSec)
{
    std::sort(multiTapDelayMilliSec.begin(), multiTapDelayMilliSec.end());
}

MultiTapDelayLine::~MultiTapDelayLine()
{
}

void MultiTapDelayLine::init(double sampleRate, float maxDelayMilliSec, float preDelayMilliSec, float maxRoomSize, float roomSize)
{
    delayLineLength = static_cast<int>(((multiTapDelayMilliSec.back() + (INTERVAL_MILLI_SEC * maxRoomSize * (multiTapDelayMilliSec.size() - 1)) + maxDelayMilliSec) / ONE_IN_MILLI) * sampleRate);
    if (delayLineLength < 1) delayLineLength = 1;
    delayLine.setSize(1, delayLineLength);
    delayLine.clear();

    if (delayReadPositions.empty())
    {
        delayReadPositions.resize(multiTapDelayMilliSec.size());
        updateDelayReadPosition(sampleRate, preDelayMilliSec, roomSize);
    }

    if (livenessCoefficients.empty())
    {
        livenessCoefficients.resize(multiTapDelayMilliSec.size());
        updateLivenessCoefficient();
    }
}

void MultiTapDelayLine::processSamples(float* sample, int numSamples)
{
    float* delayData = delayLine.getWritePointer(0);

    for (int buffNum = 0; buffNum < numSamples; ++buffNum)
    {
        delayData[delayWritePosition] = sample[buffNum];
        int count = 0;
        sample[buffNum] = 0;
        for (int& drp : delayReadPositions)
        {
            sample[buffNum] += delayData[drp] * livenessCoefficients[count++];
            if (++drp >= delayLineLength) drp = 0;
        }
        if (++delayWritePosition >= delayLineLength) delayWritePosition = 0;
    }
}

void MultiTapDelayLine::updateDelayReadPosition(double sampleRate, float preDelayMilliSec, float roomSize)
{
    const int OFFSET_SAMPLE_NUM = 1;
    for (int i = 0; i < delayReadPositions.size(); ++i)
    {
        delayReadPositions[i] = (delayWritePosition - static_cast<int>((multiTapDelayMilliSec[i] + (INTERVAL_MILLI_SEC * roomSize * i) + preDelayMilliSec) / ONE_IN_MILLI * sampleRate) + delayLineLength) % delayLineLength + OFFSET_SAMPLE_NUM;
    }
}

void MultiTapDelayLine::updateLivenessCoefficient()
{
    for (int i = 0; i < livenessCoefficients.size(); ++i)
    {
       livenessCoefficients[i] = 0.01f * (i + 1);
    }
}
