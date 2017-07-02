/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
BackwardsAudioProcessorEditor::BackwardsAudioProcessorEditor (BackwardsAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (WINDOW_WIDTH, WINDOW_HEIGHT);

    title.setFont(Font(40));
    title.setText("Backwards", dontSendNotification);

    roomSize.setSliderStyle(Slider::LinearHorizontal);
    roomSize.setRange(0.1, 20, 0.1);
    roomSize.setValue(0.8);
    roomSizeLabel.setText("ROOMSIZE", dontSendNotification);

    liveness.setSliderStyle(Slider::LinearHorizontal);
    liveness.setRange(0, 10, 1);
    liveness.setValue(6);
    livenessLabel.setText("LIVENESS", dontSendNotification);

    delay.setSliderStyle(Slider::LinearHorizontal);
    delay.setRange(0, 500, 0.1);
    delay.setValue(15);
    delay.setTextValueSuffix("ms");
    delayLabel.setText("DELAY", dontSendNotification);

    lowpassFilter.setSliderStyle(Slider::LinearHorizontal);
    lowpassFilter.setRange(1.0, 11, 0.1);
    lowpassFilter.setValue(3.2);
    lowpassFilter.setTextValueSuffix("kHz");
    lowpassFilterLabel.setText("LPF", dontSendNotification);

    outputLevel.setSliderStyle(Slider::LinearHorizontal);
    outputLevel.setRange(0, 100, 1);
    outputLevel.setValue(80);
    outputLevel.setTextValueSuffix("%");
    outputLevelLabel.setText("OUT LVL", dontSendNotification);

    mixBalance.setSliderStyle(Slider::LinearHorizontal);
    mixBalance.setRange(0, 100, 1);
    mixBalance.setValue(100);
    mixBalance.setTextValueSuffix("%");
    mixBalanceLabel.setText("MIX BAL", dontSendNotification);

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

    roomSize.addListener(this);
    liveness.addListener(this);
    delay.addListener(this);
    lowpassFilter.addListener(this);
    outputLevel.addListener(this);
    mixBalance.addListener(this);

    startTimer(30);

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

void BackwardsAudioProcessorEditor::sliderValueChanged(Slider * changedSlider)
{
    if (changedSlider == &roomSize)
    {
        processor.setParameterNotifyingHost(static_cast<int>(ControlParameter::RoomSize), static_cast<float>(roomSize.getValue()));
    }
    else if (changedSlider == &liveness)
    {
        processor.setParameterNotifyingHost(static_cast<int>(ControlParameter::Liveness), static_cast<float>(liveness.getValue()));
    }
    else if (changedSlider == &delay)
    {
        processor.setParameterNotifyingHost(static_cast<int>(ControlParameter::Delay), static_cast<float>(delay.getValue()));
    }
    else if (changedSlider == &lowpassFilter)
    {
        processor.setParameterNotifyingHost(static_cast<int>(ControlParameter::LPF), static_cast<float>(lowpassFilter.getValue()));
    }
    else if (changedSlider == &outputLevel)
    {
        processor.setParameterNotifyingHost(static_cast<int>(ControlParameter::OutputLevel), static_cast<float>(outputLevel.getValue()));
    }
    else if (changedSlider == &mixBalance)
    {
        processor.setParameterNotifyingHost(static_cast<int>(ControlParameter::MixBalance), static_cast<float>(mixBalance.getValue()));
    }
}

void BackwardsAudioProcessorEditor::timerCallback()
{
    roomSize.setValue(processor.getParameter(static_cast<int>(ControlParameter::RoomSize)), dontSendNotification);
    liveness.setValue(processor.getParameter(static_cast<int>(ControlParameter::Liveness)), dontSendNotification);
    delay.setValue(processor.getParameter(static_cast<int>(ControlParameter::Delay)), dontSendNotification);
    lowpassFilter.setValue(processor.getParameter(static_cast<int>(ControlParameter::LPF)), dontSendNotification);
    outputLevel.setValue(processor.getParameter(static_cast<int>(ControlParameter::OutputLevel)), dontSendNotification);
    mixBalance.setValue(processor.getParameter(static_cast<int>(ControlParameter::MixBalance)), dontSendNotification);
}
