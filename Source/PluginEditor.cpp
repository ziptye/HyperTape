/*
  ==============================================================================

  PLUGIN: HYPERTAPE
  AUTHOR: Zachary Pennington (ZIPTYEAUDIO)

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HyperTapeAudioProcessorEditor::HyperTapeAudioProcessorEditor (HyperTapeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    driveAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "Drive", driveSlider);

    biasAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "Bias", biasSlider);

    amountAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.apvts, "Amount", amountSlider);

    setSize (753, 450);
    background = juce::ImageCache::getFromMemory(BinaryData::HYPERTAPE11_png, BinaryData::HYPERTAPE11_pngSize);
    
    for (auto* comps : getComps())
    {
        addAndMakeVisible(comps); // Renders all components
    }
    
    driveSlider.setLookAndFeel(&myLookAndFeelV1);
    driveSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    
    biasSlider.setLookAndFeel(&myLookAndFeelV1);
    biasSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    biasSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    
    amountSlider.setLookAndFeel(&myLookAndFeelV1);
    amountSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    amountSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
}

HyperTapeAudioProcessorEditor::~HyperTapeAudioProcessorEditor()
{
}

//==============================================================================
void HyperTapeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.drawImageAt(background, 0, 0);\
    
    
    // TODO: REFACTOR THIS CODE TO DRAW THE LEDS FOR THE COLOR SELECTION SECTION
    g.setColour(juce::Colours::red);
    g.fillEllipse(colorALEDL.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(colorALEDR.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(colorBLEDL.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(colorBLEDR.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(colorCLEDL.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(colorCLEDR.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(speed7_5.toFloat());
    
    g.setColour(juce::Colours::red);
    g.fillEllipse(speed15.toFloat());
}

void HyperTapeAudioProcessorEditor::resized()
{
    driveSlider.setBounds(342, 390, 65, 65);
    biasSlider.setBounds(572, 390, 65, 65);
    amountSlider.setBounds(28, 313, 65, 65);
}

std::vector<juce::Component*>HyperTapeAudioProcessorEditor::getComps()
{
    return
    {
        &driveSlider,
        &biasSlider,
        &amountSlider
    };
}
