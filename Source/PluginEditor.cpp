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
    setSize (753, 450);
    background = juce::ImageCache::getFromMemory(BinaryData::HYPERTAPE11_png, BinaryData::HYPERTAPE11_pngSize);
    
    for (auto* comps : getComps())
    {
        addAndMakeVisible(comps); // Renders all components
    }
    
    // TODO: REPLACE WITH APVTS PARAMS
    driveSlider.setLookAndFeel(&myLookAndFeelV1);
    driveSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    driveSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    driveSlider.setRange(0.f, 1.f, 0.0001);
    driveSlider.setValue(0.0);
    
    biasSlider.setLookAndFeel(&myLookAndFeelV1);
    biasSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    biasSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    biasSlider.setRange(0.f, 1.f, 0.0001);
    biasSlider.setValue(0.0);
    
    amountSlider.setLookAndFeel(&myLookAndFeelV1);
    amountSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    amountSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    amountSlider.setRange(0.f, 1.f, 0.0001);
    amountSlider.setValue(0.0);
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
