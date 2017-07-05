/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
BackwardsAudioProcessor::BackwardsAudioProcessor()
:
#ifndef JucePlugin_PreferredChannelConfigurations
       AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),
#endif
    parameters(*this, nullptr),
    delayLine(2, 1)
{
    parameters.createAndAddParameter("roomsize", "ROOMSIZE", "",    NormalisableRange<float>(0.1f, 20.0f,  0.1f), 0.8f,   valueToTextFunction, nullptr);
    parameters.createAndAddParameter("liveness", "LIVENESS", "",    NormalisableRange<float>(0.0f, 10.0f,  1.0f), 6.0f,   valueToTextFunction, nullptr);
    parameters.createAndAddParameter("delay",    "DELAY",    "ms",  NormalisableRange<float>(0.0f, 500.0f, 0.1f), 15.0f,  valueToTextFunction, nullptr);
    parameters.createAndAddParameter("lpf",      "LPF",      "kHz", NormalisableRange<float>(1.0f, 11.0f,  0.1f), 3.2f,   valueToTextFunction, nullptr);
    parameters.createAndAddParameter("out_lvl",  "OUT LVL",  "%",   NormalisableRange<float>(0.0f, 100.0f, 1.0f), 80.0f,  valueToTextFunction, nullptr);
    parameters.createAndAddParameter("mix_bal",  "MIX BAL",  "%",   NormalisableRange<float>(0.0f, 100.0f, 1.0f), 100.0f, valueToTextFunction, nullptr);

    parameters.state = ValueTree(Identifier("Backwards"));
}

BackwardsAudioProcessor::~BackwardsAudioProcessor()
{
}

//==============================================================================
const String BackwardsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool BackwardsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool BackwardsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double BackwardsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int BackwardsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int BackwardsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void BackwardsAudioProcessor::setCurrentProgram (int index)
{
}

const String BackwardsAudioProcessor::getProgramName (int index)
{
    return {};
}

void BackwardsAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void BackwardsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..jj
    delayLineLength = static_cast<int>(((multiTapDelayMiliSec.back() + parameters.getParameterRange("delay").end) / ONE_IN_MILLI) * sampleRate);
    if(delayLineLength < 1) delayLineLength = 1;
    delayLine.setSize(2, delayLineLength);
    delayLine.clear();
}

void BackwardsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool BackwardsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void BackwardsAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
    // Output Level
    // [0, 100]  -> [0, 0.7]
    float normalizedOutputValue = *(parameters.getRawParameterValue("out_lvl")) / parameters.getParameterRange("out_lvl").end * 0.7;
    buffer.applyGain(pow(normalizedOutputValue, 2) * 2.0f);
}

//==============================================================================
bool BackwardsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BackwardsAudioProcessor::createEditor()
{
    return new BackwardsAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void BackwardsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
   ScopedPointer<XmlElement> xml(parameters.state.createXml());
   copyXmlToBinary(*xml, destData);
}

void BackwardsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));
    if (xmlState != nullptr)
        if (xmlState->hasTagName(parameters.state.getType()))
            parameters.state = ValueTree::fromXml(*xmlState);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BackwardsAudioProcessor();
}
