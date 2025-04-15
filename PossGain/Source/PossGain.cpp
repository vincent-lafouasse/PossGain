/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PossGain.hpp"
#include <atomic>
#include "Gui/PluginEditor.hpp"

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

void PossGainProcessor::processBlock(juce::AudioBuffer<float>& juceBuffer,
                                     juce::MidiBuffer&) {
    const bool muteButtonPressed =
        parameters.getRawParameterValue(muteParameterID)->load() > 0.5;

    if (muteButtonPressed &&
        juce::approximatelyEqual(this->gainProcessor.getCurrentGain(), 0.0f)) {
        juceBuffer.clear();
        return;
    }

    StereoBuffer buffer(juceBuffer);

    Poss::Buffer __buffer{buffer.leftOutput, buffer.rightOutput,
                          static_cast<std::size_t>(buffer.sz)};
    const float targetGain =
        muteButtonPressed
            ? 0.0f
            : parameters.getRawParameterValue(gainParameterID)->load();

    this->gainProcessor.setTargetGain(targetGain);
    this->gainProcessor.processBlock(__buffer);

    const float targetPan =
        parameters.getRawParameterValue(PossGainProcessor::balanceParameterID)
            ->load();
    this->applyPan(buffer, targetPan);
}

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

void PossGainProcessor::applyPan(StereoBuffer& buffer, float pan) {
    const std::array<float, 2> targetBalance = rawBalancetoBalance(pan);

    for (auto sample = 0; sample < buffer.sz; sample++) {
        buffer.leftOutput[sample] =
            this->balance[LEFT] * buffer.leftInput[sample];
        buffer.rightOutput[sample] =
            this->balance[RIGHT] * buffer.rightInput[sample];

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
    this->gainProcessor.prepareToPlay(sampleRate, samplesPerBlock);
}

void PossGainProcessor::releaseResources() {
    this->gainProcessor.releaseResources();
}

juce::AudioProcessorValueTreeState::ParameterLayout
PossGainProcessor::createLayout() {
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> parameters{};

    // gain parameter
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

    // mute parameter
    std::unique_ptr<juce::AudioParameterBool> mute(new juce::AudioParameterBool(
        PossGainProcessor::muteParameterID,
        PossGainProcessor::muteParameterName, false));
    parameters.push_back(std::move(mute));

    // balance parameter
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
    return 1;
}

int PossGainProcessor::getCurrentProgram() {
    return 0;
}

void PossGainProcessor::setCurrentProgram(int /*index*/) {}

const juce::String PossGainProcessor::getProgramName(int /*index*/) {
    return "PossGain";
}

void PossGainProcessor::changeProgramName(int /*index*/,
                                          const juce::String& /*newName*/) {}

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
    return true;
}

juce::AudioProcessorEditor* PossGainProcessor::createEditor() {
    return new PossGainEditor(*this);
}

//==============================================================================
void PossGainProcessor::getStateInformation(juce::MemoryBlock& /*destData*/) {}

void PossGainProcessor::setStateInformation(const void* /*data*/,
                                            int /*sizeInBytes*/) {}

//==============================================================================
// This creates new instances of the plugin...
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new PossGainProcessor();
}
