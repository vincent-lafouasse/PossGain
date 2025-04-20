/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "Processing/GainProcessor.hpp"
#include "Processing/PanProcessor.hpp"

//==============================================================================
/**
 */
class PossGainProcessor : public juce::AudioProcessor
#if JucePlugin_Enable_ARA
    ,
                          public juce::AudioProcessorARAExtension
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

    juce::AudioProcessorValueTreeState parameters;

    static const char* gainParameterID;
    static const char* gainParameterName;
    static const char* muteParameterID;
    static const char* muteParameterName;
    static const char* balanceParameterID;
    static const char* balanceParameterName;

   private:
    GainProcessor gainProcessor;
    PanProcessor panProcessor;

    static juce::AudioProcessorValueTreeState::ParameterLayout createLayout();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PossGainProcessor)
};
