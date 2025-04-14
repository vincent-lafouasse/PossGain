#include "PluginEditor.hpp"
#include "PossGain.hpp"

PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      inputPanel(p),
      outputPanel(p) {
    constexpr int width = 400;
    constexpr int height = 400;
    setSize(width, height);

    addAndMakeVisible(inputPanel);
    addAndMakeVisible(outputPanel);
}

PossGainEditor::~PossGainEditor() = default;

void PossGainEditor::resized() {
    auto area = getLocalBounds();

    outputPanel.setBounds(area.removeFromRight(getWidth() / 2));
    inputPanel.setBounds(area);
}

void PossGainEditor::paint(juce::Graphics& g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}
