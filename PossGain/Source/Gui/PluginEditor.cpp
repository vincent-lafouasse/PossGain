#include "PluginEditor.hpp"
#include <cmath>
#include <iomanip>
#include <sstream>
#include "PossGain.hpp"

PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      muteButton("Mute"),
      dcCutButton("DC"),
      outputPanel(p),
      gainSliderAttachment(p.parameters,
                           PossGainProcessor::gainParameterID,
                           this->gainSlider),
      balanceSliderAttachment(p.parameters,
                              PossGainProcessor::balanceParameterID,
                              this->balanceSlider),
      muteButtonAttachment(p.parameters,
                           PossGainProcessor::muteParameterID,
                           this->muteButton) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    addAndMakeVisible(outputPanelLabel);
    outputPanelLabel.setText("Output", juce::dontSendNotification);

    using flags = juce::Justification::Flags;
    outputPanelLabel.setJustificationType(flags::verticallyCentred |
                                          flags::horizontallyCentred);

    this->setupGainKnob();
    this->setupBalanceKnob();

    addAndMakeVisible(muteButton);
    muteButton.setClickingTogglesState(true);

    addAndMakeVisible(dcCutButton);
    dcCutButton.setClickingTogglesState(true);
}

PossGainEditor::~PossGainEditor() = default;

void PossGainEditor::setupGainKnob() {
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    constexpr int value_textbox_width = 100;
    constexpr int value_textbox_height = 25;
    gainSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                               true, value_textbox_width, value_textbox_height);
    gainSlider.setDoubleClickReturnValue(true, 1.0);

    addAndMakeVisible(gainLabel);
    gainLabel.setText("Gain", juce::dontSendNotification);

    using flags = juce::Justification::Flags;
    gainLabel.setJustificationType(flags::verticallyCentred |
                                   flags::horizontallyCentred);
}

void PossGainEditor::setupBalanceKnob() {
    addAndMakeVisible(balanceSlider);
    balanceSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    constexpr int value_textbox_width = 100;
    constexpr int value_textbox_height = 25;
    balanceSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxBelow, true,
        value_textbox_width, value_textbox_height);
    balanceSlider.setDoubleClickReturnValue(true, 0.5);

    // will be taken care of by APVTS:
    balanceSlider.setRange(0.0, 1.0);
    balanceSlider.setValue(0.5);

    addAndMakeVisible(balanceLabel);
    balanceLabel.setText("Balance", juce::dontSendNotification);

    using flags = juce::Justification::Flags;
    balanceLabel.setJustificationType(flags::verticallyCentred |
                                      flags::horizontallyCentred);
}

void PossGainEditor::resized() {
    juce::Rectangle<int> window = this->getLocalBounds();

    const auto outputPanelLabelPanel = window.removeFromTop(30);
    auto muteButtonPanel = window.removeFromBottom(40);
    auto gainKnobPanel = window.removeFromTop(window.getHeight() / 2);
    auto balanceKnobPanel = window;

    outputPanelLabel.setBounds(outputPanelLabelPanel);

    constexpr int gainLabelHeight = 20;
    gainLabel.setBounds(gainKnobPanel.removeFromTop(gainLabelHeight));
    gainSlider.setBounds(gainKnobPanel);

    constexpr int balanceLabelHeight = 20;
    balanceLabel.setBounds(balanceKnobPanel.removeFromTop(balanceLabelHeight));
    balanceSlider.setBounds(balanceKnobPanel);

    muteButton.setBounds(
        muteButtonPanel.removeFromLeft(muteButtonPanel.getWidth() / 2));
    dcCutButton.setBounds(muteButtonPanel);
}

void PossGainEditor::paint(juce::Graphics& g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}
