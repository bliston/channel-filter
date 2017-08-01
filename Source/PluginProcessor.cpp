/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ChannelFilterAudioProcessor::ChannelFilterAudioProcessor():parameters(*this, nullptr)
#ifndef JucePlugin_PreferredChannelConfigurations
     , AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	parameters.createAndAddParameter("midiChannel",       // parameter ID
		"Midi Channel",       // parameter name
		String(),     // parameter label (suffix)
		NormalisableRange<float>(0.0f, 16.0f, 1.0f),    // range
		0.0f,         // default value
		nullptr,
		nullptr);

	parameters.state = ValueTree(Identifier("ChannelFilter"));
}

ChannelFilterAudioProcessor::~ChannelFilterAudioProcessor()
{
}

//==============================================================================
const String ChannelFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChannelFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ChannelFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double ChannelFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChannelFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChannelFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChannelFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String ChannelFilterAudioProcessor::getProgramName (int index)
{
    return String();
}

void ChannelFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ChannelFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void ChannelFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ChannelFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ChannelFilterAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	int time;
	MidiMessage m;
	MidiBuffer processedMidi;
	for (MidiBuffer::Iterator i(midiMessages); i.getNextEvent(m, time);)
	{
		int midiChannelToLetPass = (int) *parameters.getRawParameterValue("midiChannel");
		if (m.getChannel() == midiChannelToLetPass || midiChannelToLetPass == 0)
		{
			processedMidi.addEvent(m, time);
		}
	}
	midiMessages.swapWith(processedMidi);
}

//==============================================================================
bool ChannelFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ChannelFilterAudioProcessor::createEditor()
{
    return new ChannelFilterAudioProcessorEditor (*this, parameters);
}

//==============================================================================
void ChannelFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
	ScopedPointer<XmlElement> xml(parameters.state.createXml());
	copyXmlToBinary(*xml, destData);
}

void ChannelFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
	ScopedPointer<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState != nullptr)
	{
		if (xmlState->hasTagName(parameters.state.getType()))
		{
			parameters.state = ValueTree::fromXml(*xmlState);
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ChannelFilterAudioProcessor();
}
