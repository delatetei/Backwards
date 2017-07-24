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
    delayLineLength = static_cast<int>(((multiTapDelayMilliSec.back() + maxDelayMilliSec) / ONE_IN_MILLI) * sampleRate);
    if (delayLineLength < 1) delayLineLength = 1;
    delayLine.setSize(1, delayLineLength);
    delayLine.clear();

    if (delayReadPositions.empty())
    {
        delayReadPositions.resize(multiTapDelayMilliSec.size());
        updateDelayReadPosition(sampleRate, preDelayMilliSec);
    }

    if (livenessCoefficients.empty())
    {
        livenessCoefficients.resize(multiTapDelayMilliSec.size());
        updateLivenessCoefficient(liveness);
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

void MultiTapDelayLine::updateDelayReadPosition(double sampleRate, float preDelayMilliSec)
{
    const int OFFSET_SAMPLE_NUM = 1;
    for (int i = 0; i < delayReadPositions.size(); ++i)
    {
        delayReadPositions[i] = (delayWritePosition - static_cast<int>((multiTapDelayMilliSec[i] + preDelayMilliSec) / ONE_IN_MILLI * sampleRate) + delayLineLength) % delayLineLength + OFFSET_SAMPLE_NUM;
    }
}

void MultiTapDelayLine::updateLivenessCoefficient(float liveness)
{
    for (int i = 0; i < livenessCoefficients.size(); ++i)
    {
        livenessCoefficients[i] = pow((i + 1) / float(livenessCoefficients.size()), 5.0f - 0.4f * liveness) / 4.0f;
    }
}
