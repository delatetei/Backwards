/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class BackwardsAudioProcessorEditor
    : public AudioProcessorEditor, private Slider::Listener, private Timer
{
public:
    BackwardsAudioProcessorEditor (BackwardsAudioProcessor&);
    ~BackwardsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BackwardsAudioProcessor& processor;

    //==============================================================================
    void sliderValueChanged(Slider *changedSlider) override;
    void timerCallback() override;

    //==============================================================================
    const int WINDOW_HEIGHT = 200;
    const int WINDOW_WIDTH = 400;
    const int HEADER_HEIGHT = 50;
    const int ITEM_HEIGHT= 24;
    const int LABEL_WIDTH= 100;

    //==============================================================================
    Label title;

    //==============================================================================
    Slider roomSize;
    Slider liveness;
    Slider delay;
    Slider lowpassFilter;
    Slider outputLevel;
    Slider mixBalance;
    Label roomSizeLabel;
    Label livenessLabel;
    Label delayLabel;
    Label lowpassFilterLabel;
    Label outputLevelLabel;
    Label mixBalanceLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackwardsAudioProcessorEditor)
};
