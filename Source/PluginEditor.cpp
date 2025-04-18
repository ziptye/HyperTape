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
    
    lpfAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "Low-Pass", lowPassSlider);
    
    hpfAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "High-Pass", highPassSlider);

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
    
    lowPassSlider.setLookAndFeel(&myLookAndFeelV1);
    lowPassSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    lowPassSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    
    highPassSlider.setLookAndFeel(&myLookAndFeelV1);
    highPassSlider.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    highPassSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 60, 20);
    
}

HyperTapeAudioProcessorEditor::~HyperTapeAudioProcessorEditor()
{
}

//==============================================================================
void HyperTapeAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.drawImageAt(background, 0, 0);
    
    g.setColour(audioProcessor.colorAState-> load() > 0.5f ? juce::Colours::red : juce::Colours::transparentWhite);
    g.fillEllipse(colorALEDL.toFloat());
    
    g.setColour(audioProcessor.colorAState-> load() > 0.5f ? juce::Colours::red : juce::Colours::transparentWhite);
    g.fillEllipse(colorALEDR.toFloat());
    
    g.setColour(audioProcessor.colorBState-> load() > 0.5f ? juce::Colours::red : juce::Colours::transparentWhite);
    g.fillEllipse(colorBLEDL.toFloat());
    
    g.setColour(audioProcessor.colorBState-> load() > 0.5f ? juce::Colours::red : juce::Colours::transparentWhite);
    g.fillEllipse(colorBLEDR.toFloat());
    
    g.setColour(audioProcessor.colorCState-> load() > 0.5f ? juce::Colours::red : juce::Colours::transparentWhite);
    g.fillEllipse(colorCLEDL.toFloat());
    
    g.setColour(audioProcessor.colorCState-> load() > 0.5f ? juce::Colours::red : juce::Colours::transparentWhite);
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
    lowPassSlider.setBounds(661, 158, 65, 65);
    highPassSlider.setBounds(661, 272, 65, 65);
}

std::vector<juce::Component*>HyperTapeAudioProcessorEditor::getComps()
{
    return
    {
        &driveSlider,
        &biasSlider,
        &amountSlider,
        &lowPassSlider,
        &highPassSlider,
    };
}

void HyperTapeAudioProcessorEditor::mouseDown(const juce::MouseEvent &event)
{
    juce::Point<int> clickPos = event.getPosition();
    
    // TODO: Need to make these mutually exclusive + add speed selection
    
    if (colorA.contains(clickPos))
    {
        bool currentState = audioProcessor.colorAState -> load() > 0.5f;
        audioProcessor.apvts.getParameter("Color A")-> setValueNotifyingHost(currentState ? 0.0f : 1.0f);
        repaint();
    }
    else if (colorB.contains(clickPos))
    {
        bool currentState = audioProcessor.colorBState -> load() > 0.5f;
        audioProcessor.apvts.getParameter("Color B")-> setValueNotifyingHost(currentState ? 0.0f : 1.0f);
        repaint();
    }
    else if (colorC.contains(clickPos))
    {
        bool currentState = audioProcessor.colorCState -> load() > 0.5f;
        audioProcessor.apvts.getParameter("Color C")-> setValueNotifyingHost(currentState ? 0.0f : 1.0f);
        repaint();
    }
}
