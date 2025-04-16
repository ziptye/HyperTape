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
    
    // Defines the bounds for the color selection LED's
    juce::Rectangle<int> colorALEDL {15, 128, 4, 4};
    juce::Rectangle<int> colorALEDR {98, 128, 4, 4};
    
    juce::Rectangle<int> colorBLEDL {15, 178, 4, 4};
    juce::Rectangle<int> colorBLEDR {98, 178, 4, 4};
    
    juce::Rectangle<int> colorCLEDL {15, 228, 4, 4};
    juce::Rectangle<int> colorCLEDR {98, 228, 4, 4};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HyperTapeAudioProcessorEditor)
};
