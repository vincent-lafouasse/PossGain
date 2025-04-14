#include "InputPanel.hpp"
#include "PossGain.hpp"

InputPanel::InputPanel(PossGainProcessor& p) : processor(p) {
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    addAndMakeVisible(heading);
    heading.setText("Input", juce::dontSendNotification);

    using flags = juce::Justification::Flags;
    heading.setJustificationType(flags::verticallyCentred |
                                 flags::horizontallyCentred);

    this->setupWidthSlider();
}

InputPanel::~InputPanel() = default;

void InputPanel::setupWidthSlider() {
    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(
        juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    constexpr int value_textbox_width = 100;
    constexpr int value_textbox_height = 25;
    widthSlider.setTextBoxStyle(
        juce::Slider::TextEntryBoxPosition::TextBoxBelow, true,
        value_textbox_width, value_textbox_height);
    widthSlider.setDoubleClickReturnValue(true, 1.0);

    // remove when attaching to apvts
    widthSlider.setRange(0.0, 2.0);
    widthSlider.setValue(1.0);

    addAndMakeVisible(widthLabel);
    widthLabel.setText("Width", juce::dontSendNotification);

    using flags = juce::Justification::Flags;
    widthLabel.setJustificationType(flags::verticallyCentred |
                                    flags::horizontallyCentred);
}

void InputPanel::paint(juce::Graphics& g) {
    g.fillAll(
        getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void InputPanel::resized() {
    juce::Rectangle<int> area = this->getLocalBounds();

    const auto headingPanel = area.removeFromTop(30);
    auto widthSliderPanel = area;

    heading.setBounds(headingPanel);

    constexpr int labelHeight = 20;
    widthLabel.setBounds(widthSliderPanel.removeFromTop(labelHeight));
    widthSlider.setBounds(widthSliderPanel);
}
