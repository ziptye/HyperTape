/*
  ==============================================================================

  PLUGIN: HYPERTAPE
  AUTHOR: Zachary Pennington (ZIPTYEAUDIO)

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HyperTapeAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HyperTapeAudioProcessorEditor (HyperTapeAudioProcessor&);
    ~HyperTapeAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    HyperTapeAudioProcessor& audioProcessor;
    
    juce::Image background;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HyperTapeAudioProcessorEditor)
};
