/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PossFilter.hpp"
#include "PossFilterEditor.hpp"

//==============================================================================
PossFilterProcessor::PossFilterProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
          BusesProperties()
#if !JucePlugin_IsMidiEffect
#if !JucePlugin_IsSynth
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
#endif
              .withOutput("Output", juce::AudioChannelSet::stereo(), true)
#endif
      )

#endif
{
}

PossFilterProcessor::~PossFilterProcessor() {}

void PossFilterProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                       juce::MidiBuffer&) {
    juce::ScopedNoDenormals noDenormals;
    size_t totalNumInputChannels =
        static_cast<size_t>(getTotalNumInputChannels());
    // size_t totalNumOutputChannels =
    // static_cast<size_t>(getTotalNumOutputChannels());

    for (size_t channel = 0; channel < totalNumInputChannels; ++channel) {
        auto* channelData = buffer.getWritePointer(static_cast<int>(channel));

        for (size_t sample = 0;
             sample < static_cast<size_t>(buffer.getNumSamples()); sample++) {
            channelData[sample] = 0.0;
        }
    }
}

void PossFilterProcessor::prepareToPlay(double sampleRate,
                                        int samplesPerBlock) {
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    (void)sampleRate;
    (void)samplesPerBlock;
}

void PossFilterProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

//================== boiler plate =============================================

const juce::String PossFilterProcessor::getName() const {
    return JucePlugin_Name;
}

bool PossFilterProcessor::acceptsMidi() const {
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool PossFilterProcessor::producesMidi() const {
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool PossFilterProcessor::isMidiEffect() const {
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double PossFilterProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int PossFilterProcessor::getNumPrograms() {
    return 1;  // NB: some hosts don't cope very well if you tell them there are
               // 0 programs, so this should be at least 1, even if you're not
               // really implementing programs.
}

int PossFilterProcessor::getCurrentProgram() {
    return 0;
}

void PossFilterProcessor::setCurrentProgram(int index) {
    (void)index;
}

const juce::String PossFilterProcessor::getProgramName(int index) {
    (void)index;
    return {};
}

void PossFilterProcessor::changeProgramName(int index,
                                            const juce::String& newName) {
    (void)index;
    (void)newName;
}

//==============================================================================

#ifndef JucePlugin_PreferredChannelConfigurations
bool PossFilterProcessor::isBusesLayoutSupported(
    const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused(layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

        // This checks if the input layout matches the output layout
#if !JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif

    return true;
#endif
}
#endif

//==============================================================================

bool PossFilterProcessor::hasEditor() const {
    return true;  // (change this to false if you choose to not supply an
                  // editor)
}

juce::AudioProcessorEditor* PossFilterProcessor::createEditor() {
    return new PossFilterEditor(*this);
}

//==============================================================================
void PossFilterProcessor::getStateInformation(juce::MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    (void)destData;
}

void PossFilterProcessor::setStateInformation(const void* data,
                                              int sizeInBytes) {
    // You should use this method to restore your parameters from this memory
    // block, whose contents will have been created by the getStateInformation()
    // call.
    (void)data;
    (void)sizeInBytes;
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new PossFilterProcessor();
}
