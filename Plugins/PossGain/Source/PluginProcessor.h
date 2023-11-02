/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <shared_plugin_helpers/shared_plugin_helpers.h>
#include <array>

class StereoSignalSmoother
{
public:
    StereoSignalSmoother()
        : target(0)
        , forwardWeight(0.9f)
        , inertiaWeight(0.1f)
        , memory({0, 0})
    {
    }
    void setTarget(float newTarget) { this->target = newTarget; }
    void advance(size_t channel)
    {
        memory[channel] = forwardWeight * target + inertiaWeight * memory[channel];
    }
    float get(size_t channel)
    {
        advance(channel);
        return memory[channel];
    }

private:
    float target;
    float forwardWeight;
    float inertiaWeight;
    std::array<float, 2> memory;
};

//==============================================================================
/**
*/
class PossGainProcessor
    : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
    , public juce::AudioProcessorARAExtension
#endif
{
public:
    //==============================================================================
    PossGainProcessor();
    ~PossGainProcessor() override;

    //==============================================================================
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

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
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    std::atomic<float> linearGain;
    float a;
    float b;
    std::array<float, 2> z;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainProcessor)
};
