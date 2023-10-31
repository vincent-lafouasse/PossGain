#include "PluginProcessor.h"
#include "PluginEditor.h"

PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void PossGainEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PossGainEditor::resized()
{
    editor.setBounds(getLocalBounds());
}
