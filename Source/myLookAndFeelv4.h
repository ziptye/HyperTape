/*
  ==============================================================================

    myLookAndFeelv4.h
    Created: 16 Apr 2025 3:02:15pm
    Author:  Zachary Pennington

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class myLookAndFeelV1 : public juce::LookAndFeel_V4
{
public:
    myLookAndFeelV1();

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override;

private:
    juce::Image img1;

};
