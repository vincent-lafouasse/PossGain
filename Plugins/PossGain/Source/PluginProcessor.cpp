#include "PluginProcessor.h"

void PossGainProcessor::processBlock(juce::AudioBuffer<float>& buffer,
                                       juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused(midiMessages);
    buffer.clear();
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginGain()
{
    return new PossGainProcessor();
}
