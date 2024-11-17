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

    logGainSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    logGainSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 25);
    logGainSlider.setRange(-35.0f, 35.0f);
    logGainSlider.setValue(0.0f);
    logGainSlider.addListener(this);
    addAndMakeVisible(logGainSlider);
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
    logGainSlider.setBounds(getLocalBounds());
}

void PossGainEditor::sliderValueChanged(juce::Slider* slider) {
    if (slider == &logGainSlider) {
        audioProcessor.linearGain.store(
            static_cast<float>(pow(10, logGainSlider.getValue() / 20)));
    }
}
