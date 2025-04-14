#include "OutputPanel.hpp"
#include "PossGain.hpp"

OutputPanel::OutputPanel(PossGainProcessor& p) : processor(p) {}

OutputPanel::~OutputPanel() = default;

void OutputPanel::paint(juce::Graphics&) {}

void OutputPanel::resized() {}
