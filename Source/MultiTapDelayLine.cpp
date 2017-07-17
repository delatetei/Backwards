/*
  ==============================================================================

    MultiTapDelayLine.cpp

  ==============================================================================
*/

#include "MultiTapDelayLine.h"

MultiTapDelayLine::MultiTapDelayLine(std::vector<int> multiTapDelayMilliSec)
    :
    delayLine(1, 1),
    delayWritePosition(0),
    multiTapDelayMilliSec(multiTapDelayMilliSec)
{
}

MultiTapDelayLine::~MultiTapDelayLine()
{
}

void MultiTapDelayLine::init(double sampleRate, float maxDelayMilliSec, float preDelayMilliSec)
{
    this->sampleRate = sampleRate;
    delayLineLength = static_cast<int>(((multiTapDelayMilliSec.back() + maxDelayMilliSec) / ONE_IN_MILLI) * this->sampleRate);
    if (delayLineLength < 1) delayLineLength = 1;
    delayLine.setSize(1, delayLineLength);
    delayLine.clear();

    if (delayReadPositions.empty())
    {
        for (auto delayMilliSec : multiTapDelayMilliSec)
        {
            delayReadPositions.push_back(calculateReadPosition(delayMilliSec, preDelayMilliSec));
        }
    }
}

int MultiTapDelayLine::calculateReadPosition(int delayMilliSec, float preDelayMilliSec)
{
    const int OFFSET_SAMPLE_NUM = 1;
    return (delayWritePosition - static_cast<int>((delayMilliSec + preDelayMilliSec) / ONE_IN_MILLI * sampleRate) + delayLineLength) % delayLineLength + OFFSET_SAMPLE_NUM;
}

void MultiTapDelayLine::recalculateReadPosition(float preDelayMilliSec)
{
    int i = 0;
    for (auto& dpr : delayReadPositions)
    {
        dpr = calculateReadPosition(multiTapDelayMilliSec[i++], preDelayMilliSec);
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
        for (int& dpr : delayReadPositions)
        {
            sample[buffNum] += delayData[dpr] * 0.005f * ++count;
            if (++dpr >= delayLineLength) dpr = 0;
        }
        if (++delayWritePosition >= delayLineLength) delayWritePosition = 0;
    }
}
