/*
  ==============================================================================

  PLUGIN: HYPERTAPE
  AUTHOR: Zachary Pennington (ZIPTYEAUDIO)

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ProtectYourEars.h"

//==============================================================================
/**
*/
class HyperTapeAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    HyperTapeAudioProcessor();
    ~HyperTapeAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState apvts;
    
    std::atomic<float>* colorAState = nullptr;
    std::atomic<float>* colorBState = nullptr;
    std::atomic<float>* colorCState = nullptr;
    
    std::atomic<float>* speed7_5State = nullptr;
    std::atomic<float>* speed15State = nullptr;
    
    juce::dsp::StateVariableTPTFilter<float> tapeLPF, tapeHPF;

private:
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HyperTapeAudioProcessor)
};
