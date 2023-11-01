/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p)
    , audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(200, 400);

    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0f, 0.0f);
    gainSlider.setValue(-6.0f);
    gainSlider.addListener(this);
    addAndMakeVisible(gainSlider);
}

PossGainEditor::~PossGainEditor()
{
}

//==============================================================================
void PossGainEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PossGainEditor::resized()
{
    gainSlider.setBounds(getLocalBounds());
}

void PossGainEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.gain = pow(10, gainSlider.getValue() / 20);
    }
}