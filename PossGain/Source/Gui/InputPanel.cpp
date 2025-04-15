#include "InputPanel.hpp"
#include "PossGain.hpp"

#include "Processing/InputSelectionProcessor.hpp"

InputPanel::InputPanel(PossGainProcessor& p)
    : processor(p),
      leftPhaseInvertButton("ϕL"),
      rightPhaseInvertButton("ϕR"),
      monoButton("Mono"),
      bassMonoButton("Bass Mono"),
      bassMonoCutoffButton("420 Hz"),
      bassMonoAudiationButton("🎧") {
    constexpr int width = 200;
    constexpr int height = 400;
    setSize(width, height);

    addAndMakeVisible(heading);
    heading.setText("Input", juce::dontSendNotification);

    using flags = juce::Justification::Flags;
    heading.setJustificationType(flags::verticallyCentred |
                                 flags::horizontallyCentred);

    addAndMakeVisible(leftPhaseInvertButton);
    addAndMakeVisible(rightPhaseInvertButton);

    addAndMakeVisible(inputMode);
    inputMode.addItemList(InputSelectionProcessor::inputModeNames(), 1);
    inputMode.setSelectedId(1);

    this->setupWidthSlider();

    addAndMakeVisible(monoButton);
    addAndMakeVisible(bassMonoButton);

    addAndMakeVisible(bassMonoCutoffButton);
    addAndMakeVisible(bassMonoAudiationButton);
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
    const auto height = area.getHeight();

    auto inputChannelPanel = area.removeFromTop(height / 5);
    auto widthSliderPanel = area.removeFromTop(2 * height / 5);
    auto monoPanel = area;

    heading.setBounds(headingPanel);

    auto phaseInversalPanel =
        inputChannelPanel.removeFromTop(inputChannelPanel.getHeight() / 2);
    leftPhaseInvertButton.setBounds(
        phaseInversalPanel.removeFromLeft(this->getWidth() / 2));
    rightPhaseInvertButton.setBounds(phaseInversalPanel);

    inputMode.setBounds(inputChannelPanel);

    constexpr int labelHeight = 20;
    widthLabel.setBounds(widthSliderPanel.removeFromTop(labelHeight));
    widthSlider.setBounds(widthSliderPanel);

    const auto monoPanelHeight = monoPanel.getHeight();
    monoButton.setBounds(monoPanel.removeFromTop(monoPanelHeight / 3));
    bassMonoButton.setBounds(monoPanel.removeFromTop(monoPanelHeight / 3));

    bassMonoCutoffButton.setBounds(
        monoPanel.removeFromLeft(7 * this->getWidth() / 10));
    bassMonoAudiationButton.setBounds(monoPanel);
}
