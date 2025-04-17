/*
  ==============================================================================

  PLUGIN: HYPERTAPE
  AUTHOR: Zachary Pennington (ZIPTYEAUDIO)

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HyperTapeAudioProcessor::HyperTapeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "HyperTape Params", createParameterLayout())
#endif
{
}

HyperTapeAudioProcessor::~HyperTapeAudioProcessor()
{
}

//==============================================================================
const juce::String HyperTapeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HyperTapeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HyperTapeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HyperTapeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HyperTapeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HyperTapeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HyperTapeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HyperTapeAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HyperTapeAudioProcessor::getProgramName (int index)
{
    return {};
}

void HyperTapeAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HyperTapeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HyperTapeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HyperTapeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HyperTapeAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
    
#if JUCE_DEBUG
    protectYourEars(buffer);
#endif
}

//==============================================================================
bool HyperTapeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HyperTapeAudioProcessor::createEditor()
{
    return new HyperTapeAudioProcessorEditor (*this);
}

//==============================================================================
void HyperTapeAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HyperTapeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HyperTapeAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout HyperTapeAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto LPFRange = juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.25f);
    auto HPFRange = juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.25f);
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Low-Pass" , 1), "Low-Pass", LPFRange, 20000.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("High-Pass" , 1), "High-Pass", HPFRange, 20.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Color A", 1), "Color A", true)); // Default
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Color B", 1), "Color B", false));
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Color C", 1), "Color C", false));
    
    auto Amount = juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f, 0.25f);
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Amount" , 1), "Amount", Amount, 0.0f));
    
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Speed 7.5", 1), "Speed 7.5", true)); // Default
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("Speed 15", 1), "Speed 15", false));
    
    auto DriveAmount = juce::NormalisableRange<float>(0.0f, 100.0f, 1.0f, 0.25f);
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Drive" , 1), "Drive", DriveAmount, 0.0f));
    
    auto BiasAmount = juce::NormalisableRange<float>(-1.0f, 1.0f, 0.01f);
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("Bias" , 1), "Bias", BiasAmount, -1.0f));
    
    return {    params.begin(), params.end()    };
}
