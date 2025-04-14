/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PossGain.hpp"
#include <atomic>
#include "PluginEditor.hpp"

#define LEFT 0
#define RIGHT 1

const char* PossGainProcessor::gainParameterID = "gainID";
const char* PossGainProcessor::gainParameterName = "gainName";
const char* PossGainProcessor::muteParameterID = "muteID";
const char* PossGainProcessor::muteParameterName = "muteName";
const char* PossGainProcessor::balanceParameterID = "balanceID";
const char* PossGainProcessor::balanceParameterName = "balanceName";

//==============================================================================
PossGainProcessor::PossGainProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(
          BusesProperties()
              .withInput("Input", juce::AudioChannelSet::stereo(), true)
              .withOutput("Output", juce::AudioChannelSet::stereo(), true))

#endif
      ,
      parameters(*this,
                 nullptr,
                 "Parameters",
                 PossGainProcessor::createLayout())

{
}

PossGainProcessor::~PossGainProcessor() = default;

namespace {
std::array<float, 2> rawBalancetoBalance(const float value) {
    float reducedGain = 1.0f - 2.0f * std::fabs(value - 0.5f);

    if (value > 0.5f) {
        // left
        return {reducedGain, 1.0f};
    } else {
        // right
        return {1.0f, reducedGain};
    }
}
}  // namespace

void PossGainProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                     juce::MidiBuffer&) {
    auto* leftChannel = buffer.getWritePointer(LEFT);
    auto* rightChannel = buffer.getWritePointer(RIGHT);

    const bool muteButtonPressed =
        parameters.getRawParameterValue(muteParameterID)->load() > 0.5;

    if (muteButtonPressed && juce::approximatelyEqual(this->gain, 0.0f)) {
        buffer.clear();
        return;
    }

    const float targetGain =
        muteButtonPressed
            ? 0.0f
            : parameters.getRawParameterValue(gainParameterID)->load();

    const std::array<float, 2> targetBalance = rawBalancetoBalance(
        parameters.getRawParameterValue(PossGainProcessor::balanceParameterID)
            ->load());

    const auto nSamples = buffer.getNumSamples();
    for (auto sample = 0; sample < nSamples; sample++) {
        leftChannel[sample] =
            this->gain * this->balance[LEFT] * leftChannel[sample];
        rightChannel[sample] =
            this->gain * this->balance[RIGHT] * rightChannel[sample];

        if (!juce::approximatelyEqual(this->gain, targetGain)) {
            constexpr float forwardWeight = 0.05f;
            this->gain = (1.0f - forwardWeight) * this->gain +
                         forwardWeight * targetGain;
        }

        if (!juce::approximatelyEqual(this->balance[LEFT],
                                      targetBalance[LEFT])) {
            constexpr float forwardWeight = 0.1f;
            this->balance[LEFT] = (1.0f - forwardWeight) * this->balance[LEFT] +
                                  forwardWeight * targetBalance[LEFT];
        }
        if (!juce::approximatelyEqual(this->balance[RIGHT],
                                      targetBalance[RIGHT])) {
            constexpr float forwardWeight = 0.1f;
            this->balance[RIGHT] =
                (1.0f - forwardWeight) * this->balance[RIGHT] +
                forwardWeight * targetBalance[RIGHT];
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

juce::AudioProcessorValueTreeState::ParameterLayout
PossGainProcessor::createLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters{};

    constexpr float maxGaindB = 35.0f;
    const float maxGain = std::powf(10.0f, maxGaindB / 20.0f);
    constexpr float unityGain = 1.0f;

    juce::NormalisableRange<float> gainRange(0.0f, maxGain);
    gainRange.setSkewForCentre(unityGain);

    std::unique_ptr<juce::AudioParameterFloat> gainParam(
        new juce::AudioParameterFloat(PossGainProcessor::gainParameterID,
                                      PossGainProcessor::gainParameterName,
                                      gainRange, unityGain));
    parameters.push_back(std::move(gainParam));

    std::unique_ptr<juce::AudioParameterBool> mute(new juce::AudioParameterBool(
        PossGainProcessor::muteParameterID,
        PossGainProcessor::muteParameterName, false));
    parameters.push_back(std::move(mute));

    const juce::NormalisableRange balanceRange(0.0f, 1.0f);
    std::unique_ptr<juce::AudioParameterFloat> balanceParam(
        new juce::AudioParameterFloat(PossGainProcessor::balanceParameterID,
                                      PossGainProcessor::balanceParameterName,
                                      balanceRange, 0.5f));
    parameters.push_back(std::move(balanceParam));

    return {parameters.begin(), parameters.end()};
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
