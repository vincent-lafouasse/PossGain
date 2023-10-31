#include "PluginProcessor.h"
#include "PluginEditor.h"

PossFilterEditor::PossFilterEditor(PossFilterProcessor& p)
    : AudioProcessorEditor(&p)
{
    addAndMakeVisible(editor);
    setSize(400, 300);
}

void PossFilterEditor::paint(juce::Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void PossFilterEditor::resized()
{
    editor.setBounds(getLocalBounds());
}
