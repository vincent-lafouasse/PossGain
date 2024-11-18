/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.hpp"
#include "PossGain.hpp"

//==============================================================================
PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(200, 400);

    gainSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                               true, 100, 25);

    constexpr double maxGaindB = 35.0;
    const double maxGain = std::pow(10.0, maxGaindB / 20.0);
    gainSlider.setRange(0.0, maxGain);
    gainSlider.setSkewFactorFromMidPoint(1.0);
    gainSlider.setValue(1.0);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
}

PossGainEditor::~PossGainEditor() {}

//==============================================================================
void PossGainEditor::paint(juce::Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with
    // a solid colour)
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PossGainEditor::resized() {
    gainSlider.setBounds(getLocalBounds());
}

void PossGainEditor::sliderValueChanged(juce::Slider* slider) {
    if (slider == &gainSlider) {
        audioProcessor.linearGain.store(
            static_cast<float>(gainSlider.getValue()));
    }
}
