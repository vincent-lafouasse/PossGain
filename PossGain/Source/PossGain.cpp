/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PossGain.hpp"
#include "PluginEditor.hpp"
#include "StereoSignalSmoother.tpp"

//==============================================================================
PossGainProcessor::PossGainProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
              )

#endif
      ,
      linearGain(0) {
}

PossGainProcessor::~PossGainProcessor() = default;

void PossGainProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                     juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    const auto totalNumInputChannels =
        static_cast<size_t>(getTotalNumInputChannels());
    // size_t totalNumOutputChannels =
    // static_cast<size_t>(getTotalNumOutputChannels());

    smoothedGain.setTarget(linearGain.load());

    for (size_t channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(static_cast<int>(channel));

        for (size_t sample = 0;
             sample < static_cast<size_t>(buffer.getNumSamples()); sample++) {
            channelData[sample] =
                smoothedGain.get(channel) * channelData[sample];
        }
    }
}

void PossGainProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need...
    (void)sampleRate;
    (void)samplesPerBlock;
}

void PossGainProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

//================== boiler plate =============================================

const juce::String PossGainProcessor::getName() const {
    return JucePlugin_Name;
}

bool PossGainProcessor::acceptsMidi() const {
    return true;
}

bool PossGainProcessor::producesMidi() const {
    return false;
}

bool PossGainProcessor::isMidiEffect() const {
    return false;
}

double PossGainProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int PossGainProcessor::getNumPrograms() {
    return 1;  // NB: some hosts don't cope very well if you tell them there are
               // 0 programs, so this should be at least 1, even if you're not
               // really implementing programs.
}

int PossGainProcessor::getCurrentProgram() {
    return 0;
}

void PossGainProcessor::setCurrentProgram(int index) {
    (void)index;
}

const juce::String PossGainProcessor::getProgramName(int index) {
    (void)index;
    return "PossGain";
}

void PossGainProcessor::changeProgramName(int index,
                                          const juce::String& newName) {
    (void)index;
    (void)newName;
}

//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool PossGainProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const {
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}
#endif

//==============================================================================

bool PossGainProcessor::hasEditor() const {
    return true;  // (change this to false if you choose to not supply an
                  // editor)
}

juce::AudioProcessorEditor* PossGainProcessor::createEditor() {
    return new PossGainEditor(*this);
}

//==============================================================================
void PossGainProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    (void)destData;
}

void PossGainProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
    (void)data;
    (void)sizeInBytes;
}

//==============================================================================
// This creates new instances of the plugin...
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new PossGainProcessor();
}
