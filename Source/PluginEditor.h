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
    
    // Defines bounds of Color Selectors
    juce::Rectangle<int> colorA {39, 110, 40, 40};
    juce::Rectangle<int> colorB {39, 160, 40, 40};
    juce::Rectangle<int> colorC {39, 210, 40, 40};
    
    // Defines the bounds for the color + speed selection LED's
    juce::Rectangle<int> colorALEDL {15, 128, 4, 4}; // Default ON
    juce::Rectangle<int> colorALEDR {98, 128, 4, 4};
    
    juce::Rectangle<int> colorBLEDL {15, 178, 4, 4};
    juce::Rectangle<int> colorBLEDR {98, 178, 4, 4};
    
    juce::Rectangle<int> colorCLEDL {15, 228, 4, 4};
    juce::Rectangle<int> colorCLEDR {98, 228, 4, 4};
    
    juce::Rectangle<int> speed7_5 {123, 407, 3, 3}; // Default ON
    juce::Rectangle<int> speed15 {183, 407, 3, 3};
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> driveAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> biasAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> amountAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HyperTapeAudioProcessorEditor)
};
