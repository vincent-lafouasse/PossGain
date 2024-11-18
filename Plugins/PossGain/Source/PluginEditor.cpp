/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.hpp"
#include "PossGain.hpp"
#include <sstream>
#include <iomanip>

//==============================================================================
PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    gainSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    constexpr int value_textbox_width = 100;
    constexpr int value_textbox_height = 25;
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                               true, value_textbox_width, value_textbox_height);

    constexpr double maxGaindB = 35.0;
    const double maxGain = std::pow(10.0, maxGaindB / 20.0);
    gainSlider.setRange(0.0, maxGain);
    gainSlider.setSkewFactorFromMidPoint(1.0);
    gainSlider.setValue(1.0);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
}

PossGainEditor::~PossGainEditor() {}

juce::String GainKnob::getTextFromValue(double value) {
    if (value == 0.0)
        return "-inf dB";

    std::stringstream ss{};
    ss << std::fixed;
    ss << std::setprecision(1);
    ss << 20.0 * std::log10(value);
    ss << " dB";
    return ss.str();
}

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
