/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PossFilterEditor.hpp"
#include "PossFilter.hpp"

//==============================================================================
PossFilterEditor::PossFilterEditor(PossFilterProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);
}

PossFilterEditor::~PossFilterEditor() {}

//==============================================================================
void PossFilterEditor::paint(juce::Graphics& g) {
    // (Our component is opaque, so we must completely fill the background with
    // a solid colour)
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PossFilterEditor::resized() {}

void PossFilterEditor::sliderValueChanged(juce::Slider* slider) {}
