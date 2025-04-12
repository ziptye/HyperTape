/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HyperTapeAudioProcessorEditor::HyperTapeAudioProcessorEditor (HyperTapeAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (751, 450);
    background = juce::ImageCache::getFromMemory(BinaryData::HYPERTAPE1_png, BinaryData::HYPERTAPE1_pngSize);
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
}

void HyperTapeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
