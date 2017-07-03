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
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    userParameters.insert(std::make_pair(ControlParameter::RoomSize, 0.0f));
    userParameters.insert(std::make_pair(ControlParameter::Liveness, 0.0f));
    userParameters.insert(std::make_pair(ControlParameter::Delay, 0.0f));
    userParameters.insert(std::make_pair(ControlParameter::LPF, 0.0f));
    userParameters.insert(std::make_pair(ControlParameter::OutputLevel, 0.7f));
    userParameters.insert(std::make_pair(ControlParameter::MixBalance, 0.0f));
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
    // initialisation that you need..
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
}

//==============================================================================
bool BackwardsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* BackwardsAudioProcessor::createEditor()
{
    return new BackwardsAudioProcessorEditor (*this);
}

//==============================================================================
void BackwardsAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    XmlElement root("Root");
    XmlElement *el;
    el = root.createNewChildElement("RoomSize");
    el->addTextElement(String(userParameters[ControlParameter::RoomSize]));
    el = root.createNewChildElement("Liveness");
    el->addTextElement(String(userParameters[ControlParameter::Liveness]));
    el = root.createNewChildElement("Delay");
    el->addTextElement(String(userParameters[ControlParameter::Delay]));
    el = root.createNewChildElement("LPF");
    el->addTextElement(String(userParameters[ControlParameter::LPF]));
    el = root.createNewChildElement("OutputLevel");
    el->addTextElement(String(userParameters[ControlParameter::OutputLevel]));
    el = root.createNewChildElement("MixBalance");
    el->addTextElement(String(userParameters[ControlParameter::MixBalance]));
    copyXmlToBinary(root, destData);

}

void BackwardsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    XmlElement* pRoot = getXmlFromBinary(data, sizeInBytes);
    if (pRoot != nullptr)
    {
        forEachXmlChildElement((*pRoot), pChild)
        {
            String text = pChild->getAllSubText();
            if (pChild->hasTagName("RoomSize"))
            {
                setParameter(static_cast<int>(ControlParameter::RoomSize), text.getFloatValue());
            }
            else if (pChild->hasTagName("Liveness"))
            {
                setParameter(static_cast<int>(ControlParameter::Liveness), text.getFloatValue());
            }
            else if (pChild->hasTagName("Delay"))
            {
                setParameter(static_cast<int>(ControlParameter::Delay), text.getFloatValue());
            }
            else if (pChild->hasTagName("LPF"))
            {
                setParameter(static_cast<int>(ControlParameter::LPF), text.getFloatValue());
            }
            else if (pChild->hasTagName("OutputLevel"))
            {
                setParameter(static_cast<int>(ControlParameter::OutputLevel), text.getFloatValue());
            }
            else if (pChild->hasTagName("MixBalance"))
            {
                setParameter(static_cast<int>(ControlParameter::MixBalance), text.getFloatValue());
            }
        }
        delete pRoot;
    }
}

//==============================================================================
int BackwardsAudioProcessor::getNumParameters()
{
    return static_cast<int>(ControlParameter::totalNum);
}

float BackwardsAudioProcessor::getParameter(int index)
{
    auto parameterIterator = userParameters.find(static_cast<ControlParameter>(index));
    if (parameterIterator == userParameters.end()) return 0;
    return parameterIterator->second;
}

void BackwardsAudioProcessor::setParameter(int index, float value)
{
    const ControlParameter& controlParameterIndex = static_cast<ControlParameter>(index);
    auto parameterIterator = userParameters.find(controlParameterIndex);
    if (parameterIterator == userParameters.end()) return;

    auto& parameterValue = parameterIterator->second;
    parameterValue = value;
}

const String BackwardsAudioProcessor::getParameterName(int index)
{
    const ControlParameter& controlParameterIndex = static_cast<ControlParameter>(index);
    return controlParameterIndex == ControlParameter::RoomSize ? "ROOMSIZE"
        : controlParameterIndex == ControlParameter::Liveness ? "LIVENESS"
        : controlParameterIndex == ControlParameter::Delay ? "DELAY"
        : controlParameterIndex == ControlParameter::LPF ? "LPF"
        : controlParameterIndex == ControlParameter::OutputLevel ? "OUT LVL"
        : controlParameterIndex == ControlParameter::MixBalance ? "MIX BAL"
        : String::empty;
}

const String BackwardsAudioProcessor::getParameterText(int index)
{
    const ControlParameter& controlParameterIndex = static_cast<ControlParameter>(index);
    auto parameterIterator = userParameters.find(controlParameterIndex);
    if (parameterIterator == userParameters.end()) return String();

    return String(parameterIterator->second);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new BackwardsAudioProcessor();
}
