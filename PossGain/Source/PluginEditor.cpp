#include "PluginEditor.hpp"
#include <iomanip>
#include <sstream>
#include "PossGain.hpp"

PossGainEditor::PossGainEditor(PossGainProcessor& p)
    : AudioProcessorEditor(&p),
      audioProcessor(p),
      muteButton("Mute"),
      gainSliderAttachment(p.parameters,
                           PossGainProcessor::gainParameterID,
                           this->gainSlider),
      muteButtonAttachment(p.parameters,
                           PossGainProcessor::muteParameterID,
                           this->muteButton) {
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    this->setupGainKnob();

    addAndMakeVisible(muteButton);
    muteButton.setClickingTogglesState(true);
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
    gainLabel.setJustificationType(flags::verticallyCentred | flags::horizontallyCentred);
}

void PossGainEditor::resized() {
    juce::Rectangle<int> window = this->getLocalBounds();

    muteButton.setBounds(window.removeFromBottom(40));

    constexpr int gainLabelHeight = 40;
    gainLabel.setBounds(window.removeFromBottom(gainLabelHeight));
    gainSlider.setBounds(window);
}

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

void PossGainEditor::paint(juce::Graphics& g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}
