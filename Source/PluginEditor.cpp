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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);

    title.setFont(Font(40));
    title.setText("Backwards", dontSendNotification);

    roomSize.setSliderStyle(Slider::LinearHorizontal);
    roomSizeLabel.setText(valueTreeState.getParameter("roomsize")->name, dontSendNotification);

    liveness.setSliderStyle(Slider::LinearHorizontal);
    livenessLabel.setText(valueTreeState.getParameter("liveness")->name, dontSendNotification);

    delay.setSliderStyle(Slider::LinearHorizontal);
    delayLabel.setText(valueTreeState.getParameter("delay")->name, dontSendNotification);

    lowpassFilter.setSliderStyle(Slider::LinearHorizontal);
    lowpassFilterLabel.setText(valueTreeState.getParameter("lpf")->name, dontSendNotification);

    outputLevel.setSliderStyle(Slider::LinearHorizontal);
    outputLevelLabel.setText(valueTreeState.getParameter("out_lvl")->name, dontSendNotification);

    mixBalance.setSliderStyle(Slider::LinearHorizontal);
    mixBalanceLabel.setText(valueTreeState.getParameter("mix_bal")->name, dontSendNotification);

    addAndMakeVisible(&title);
    addAndMakeVisible(&roomSize);
    addAndMakeVisible(&roomSizeLabel);
    addAndMakeVisible(&liveness);
    addAndMakeVisible(&livenessLabel);
    addAndMakeVisible(&delay);
    addAndMakeVisible(&delayLabel);
    addAndMakeVisible(&lowpassFilter);
    addAndMakeVisible(&lowpassFilterLabel);
    addAndMakeVisible(&outputLevel);
    addAndMakeVisible(&outputLevelLabel);
    addAndMakeVisible(&mixBalance);
    addAndMakeVisible(&mixBalanceLabel);

    roomSizeAttachment      = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "roomsize", roomSize);
    livenessAttachment      = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "liveness", liveness);
    delayAttachment         = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "delay",    delay);
    lowpassFilterAttachment = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "lpf",      lowpassFilter);
    outputLevelAttachment   = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "out_lvl",  outputLevel);
    mixBalanceAttachment    = new AudioProcessorValueTreeState::SliderAttachment(valueTreeState, "mix_bal",  mixBalance);
}

BackwardsAudioProcessorEditor::~BackwardsAudioProcessorEditor()
{
}

//==============================================================================
void BackwardsAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
}

void BackwardsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    Rectangle<int> area(getLocalBounds());
    Rectangle<int> headerArea(area.removeFromTop(HEADER_HEIGHT));
    Rectangle<int> roomSizeArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> livenessArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> delayArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> lowpassFilterArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> outputLevelArea(area.removeFromTop(ITEM_HEIGHT));
    Rectangle<int> mixBalanceArea(area.removeFromTop(ITEM_HEIGHT));
    
    title.setBounds(headerArea.removeFromTop(HEADER_HEIGHT));
    roomSizeLabel.setBounds(roomSizeArea.removeFromLeft(LABEL_WIDTH));
    roomSize.setBounds(roomSizeArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    livenessLabel.setBounds(livenessArea.removeFromLeft(LABEL_WIDTH));
    liveness.setBounds(livenessArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    delayLabel.setBounds(delayArea.removeFromLeft(LABEL_WIDTH));
    delay.setBounds(delayArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    lowpassFilterLabel.setBounds(lowpassFilterArea.removeFromLeft(LABEL_WIDTH));
    lowpassFilter.setBounds(lowpassFilterArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    outputLevelLabel.setBounds(outputLevelArea.removeFromLeft(LABEL_WIDTH));
    outputLevel.setBounds(outputLevelArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
    mixBalanceLabel.setBounds(mixBalanceArea.removeFromLeft(LABEL_WIDTH));
    mixBalance.setBounds(mixBalanceArea.removeFromLeft(WINDOW_WIDTH - LABEL_WIDTH));
}