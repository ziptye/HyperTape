/*
  ==============================================================================

  PLUGIN: HYPERTAPE
  AUTHOR: Zachary Pennington (ZIPTYEAUDIO)

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "myLookAndFeelv4.h"

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
    
    std::vector<juce::Component*> getComps();
    
    myLookAndFeelV1 myLookAndFeelV1;
        
    juce::Slider driveSlider;
    juce::Slider biasSlider;
    juce::Slider amountSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HyperTapeAudioProcessorEditor)
};
