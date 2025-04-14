#include "PluginEditor.hpp"
#include "PossGain.hpp"

PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p), outputPanel(p) {
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    addAndMakeVisible(outputPanel);
}

PossGainEditor::~PossGainEditor() = default;

void PossGainEditor::resized() {
    outputPanel.setBounds(getLocalBounds());
}

void PossGainEditor::paint(juce::Graphics& g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}
