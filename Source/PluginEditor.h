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
    : public AudioProcessorEditor
{
public:
    BackwardsAudioProcessorEditor (BackwardsAudioProcessor&, AudioProcessorValueTreeState&);
    ~BackwardsAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    void changeLPFSliderState(bool state);
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BackwardsAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;

    //==============================================================================
    const int WINDOW_HEIGHT = 200;
    const int WINDOW_WIDTH = 400;
    const int HEADER_HEIGHT = 50;
    const int ITEM_HEIGHT= 24;
    const int LABEL_WIDTH= 100;
    const int BYPASS_BUTTON_WIDTH = 70;

    //==============================================================================
    Label title;

    //==============================================================================
    Slider roomSize;
    Slider liveness;
    Slider delay;
    Slider lowpassFilter;
    Slider outputLevel;
    Slider mixBalance;
    ToggleButton thru;
    Label roomSizeLabel;
    Label livenessLabel;
    Label delayLabel;
    Label lowpassFilterLabel;
    Label outputLevelLabel;
    Label mixBalanceLabel;

    //==============================================================================
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> livenessAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> delayAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lowpassFilterAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> outputLevelAttachment;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> mixBalanceAttachment;
    ScopedPointer<AudioProcessorValueTreeState::ButtonAttachment> thruAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BackwardsAudioProcessorEditor)
};
