/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <vector>
#include <list>

//==============================================================================
/**
*/
class BackwardsAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    BackwardsAudioProcessor();
    ~BackwardsAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    struct DelayParameterListener : AudioProcessorValueTreeState::Listener
    {
    public:
        DelayParameterListener(BackwardsAudioProcessor& p);
        void parameterChanged(const String& parameterID, float newValue) override;
    private:
        BackwardsAudioProcessor& _p;

    };
    //==============================================================================
    int calculateReadPosition(int delayMiliSec, double sampleRate);

    //==============================================================================
    const float ONE_IN_MILLI = 1000.0f;

    //==============================================================================
    AudioProcessorValueTreeState parameters;
    AudioSampleBuffer delayLine;
    int delayLineLength;
    const std::vector<int> multiTapDelayMilliSec{   2,   3,   5,   7,  11,  13,  17,  19,  23,  29,
                                                   31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
                                                   73,  79,  83,  89,  97, 101, 103, 107, 109, 113,
                                                  127, 131, 137, 139, 149, 151, 157, 163, 167, 173,
                                                  179, 181, 191, 193, 197, 199, 211, 223, 227, 229 };
    std::list<int> delayReadPositions;
    int delayWritePosition;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackwardsAudioProcessor)
};

static String valueToTextFunction(float value)
{
    return String(value);
};
