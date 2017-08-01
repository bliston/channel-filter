/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
ChannelFilterAudioProcessorEditor::ChannelFilterAudioProcessorEditor (ChannelFilterAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), valueTreeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	midiChannelLabel.setText("Midi Channel", dontSendNotification);
	addAndMakeVisible(midiChannelLabel);
	addAndMakeVisible(midiChannelSlider);
	midiChannelSliderAttachment = new SliderAttachment(valueTreeState, "midiChannel", midiChannelSlider);
	setSize(paramSliderWidth + paramLabelWidth, paramControlHeight);
}

ChannelFilterAudioProcessorEditor::~ChannelFilterAudioProcessorEditor()
{
}

//==============================================================================
void ChannelFilterAudioProcessorEditor::paint (Graphics& g)
{
}

void ChannelFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
	midiChannelSlider.setBounds(88, 8, 288, 24);
	midiChannelLabel.setBounds(3, 8, 79, 24);
}
