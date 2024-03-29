/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#ifndef PLUGINEDITOR_H_INCLUDED
#define PLUGINEDITOR_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"


//==============================================================================
/**
*/
class ChannelFilterAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    ChannelFilterAudioProcessorEditor (ChannelFilterAudioProcessor&, AudioProcessorValueTreeState& vts);
    ~ChannelFilterAudioProcessorEditor();
	typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
	Peels::MiddleLookAndFeel lookAndFeel;
    ChannelFilterAudioProcessor& processor;
	AudioProcessorValueTreeState& valueTreeState;
	Label midiChannelLabel;
	Slider midiChannelSlider;
	ScopedPointer<SliderAttachment> midiChannelSliderAttachment;
	int paramSliderWidth = 300;
	int paramLabelWidth = 100;
	int paramControlHeight = 200;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelFilterAudioProcessorEditor)
};


#endif  // PLUGINEDITOR_H_INCLUDED
