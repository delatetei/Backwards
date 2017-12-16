/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BackwardsAudioProcessorEditor::BackwardsAudioProcessorEditor (BackwardsAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    setSize(WINDOW_WIDTH, WINDOW_HEIGHT);

    title.setFont(Font(40));
    title.setText("Backwards", dontSendNotification);

    roomSize.setSliderStyle(Slider::LinearHorizontal);
    roomSizeLabel.setText(valueTreeState.getParameter("roomsize")->name, dontSendNotification);

    delay.setSliderStyle(Slider::LinearHorizontal);
    delayLabel.setText(valueTreeState.getParameter("delay")->name, dontSendNotification);

    lowpassFilter.setSliderStyle(Slider::LinearHorizontal);
    lowpassFilterLabel.setText(valueTreeState.getParameter("lpf")->name, dontSendNotification);

    outputLevel.setSliderStyle(Slider::LinearHorizontal);
    outputLevelLabel.setText(valueTreeState.getParameter("out_lvl")->name, dontSendNotification);

    mixBalance.setSliderStyle(Slider::LinearHorizontal);
    mixBalanceLabel.setText(valueTreeState.getParameter("mix_bal")->name, dontSendNotification);

    thru.setButtonText(valueTreeState.getParameter("thru")->name);

    addAndMakeVisible(&title);
    addAndMakeVisible(&roomSize);
    addAndMakeVisible(&roomSizeLabel);
    addAndMakeVisible(&delay);
    addAndMakeVisible(&delayLabel);
    addAndMakeVisible(&lowpassFilter);
    addAndMakeVisible(&lowpassFilterLabel);
    addAndMakeVisible(&outputLevel);
    addAndMakeVisible(&outputLevelLabel);
    addAndMakeVisible(&mixBalance);
    addAndMakeVisible(&mixBalanceLabel);
    addAndMakeVisible(&thru);

    roomSizeAttachment      = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "roomsize", roomSize);
    delayAttachment         = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delay",    delay);
    lowpassFilterAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lpf",      lowpassFilter);
    outputLevelAttachment   = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "out_lvl",  outputLevel);
    mixBalanceAttachment    = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mix_bal",  mixBalance);
    thruAttachment          = new AudioProcessorValueTreeState::ButtonAttachment(valueTreeState, "thru",     thru);
}

BackwardsAudioProcessorEditor::~BackwardsAudioProcessorEditor()
{
}

//==============================================================================
void BackwardsAudioProcessorEditor::paint (Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));

    g.setColour(Colours::white);
    g.setFont(15.0f);

    getLookAndFeel().setColour(Slider::thumbColourId, Colours::darkorchid);
}

void BackwardsAudioProcessorEditor::resized()
{
    Rectangle<int> area(getLocalBounds());
    Rectangle<int> headerArea(area.removeFromTop(HEADER_HEIGHT));
    Rectangle<int> roomSizeArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> delayArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> lowpassFilterArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> outputLevelArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> mixBalanceArea(area.removeFromTop(ITEM_HEIGHT));

    title.setBounds(headerArea.removeFromTop(HEADER_HEIGHT));
    roomSizeLabel.setBounds(roomSizeArea.removeFromLeft(LABEL_WIDTH));
    roomSize.setBounds(roomSizeArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    delayLabel.setBounds(delayArea.removeFromLeft(LABEL_WIDTH));
    delay.setBounds(delayArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    lowpassFilterLabel.setBounds(lowpassFilterArea.removeFromLeft(LABEL_WIDTH));
    lowpassFilter.setBounds(lowpassFilterArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH - BYPASS_BUTTON_WIDTH));
    thru.setBounds(lowpassFilterArea.removeFromLeft(BYPASS_BUTTON_WIDTH));

    outputLevelLabel.setBounds(outputLevelArea.removeFromLeft(LABEL_WIDTH));
    outputLevel.setBounds(outputLevelArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    mixBalanceLabel.setBounds(mixBalanceArea.removeFromLeft(LABEL_WIDTH));
    mixBalance.setBounds(mixBalanceArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));

    changeLPFSliderState(valueTreeState.getParameter("thru")->getValue() == 0.0f ? true : false);
}

void BackwardsAudioProcessorEditor::changeLPFSliderState(bool state)
{
    lowpassFilter.setEnabled(state);
}
