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

void MultiTapDelayLine::init(double sampleRate, float maxDelayMilliSec, float preDelayMilliSec, float liveness)
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
    if (livenessCoefficients.empty())
    {
        for (int i = 1; i <= delayReadPositions.size(); ++i)
        {
            livenessCoefficients.push_back(calculateLivenessCoefficient(i, liveness));
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
    for (auto& drp : delayReadPositions)
    {
        drp = calculateReadPosition(multiTapDelayMilliSec[i++], preDelayMilliSec);
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

float MultiTapDelayLine::calculateLivenessCoefficient(int count, float liveness)
{
    return pow(count / float(delayReadPositions.size()), 5.0f - 0.4f * liveness) / 4.0f;
}

void MultiTapDelayLine::recalculateLivenessCoefficient(float liveness)
{
    int i = 0;
    for (auto& lc : livenessCoefficients)
    {
        lc = calculateLivenessCoefficient(++i, liveness);
    }
}
