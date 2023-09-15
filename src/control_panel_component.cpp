#include "control_panel_component.h"
#include "midi_manager.h"

ControlPanelComponent::ControlPanelComponent() {

  _pitchBend.setRange(-1.0, 1.0);
  _pitchBend.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
  _pitchBend.setBounds(10, 10, 25, 80);
  _pitchBend.setScrollWheelEnabled(true);
  _pitchBend.setDoubleClickReturnValue(true, 0.0);
  addAndMakeVisible(_pitchBend);
  _pitchBend.addListener(this);

  _modWheel.setRange(0.0, 1.0);
  _modWheel.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
  _modWheel.setBounds(_pitchBend.getRight() + 10, 10, 30, 80);
  _modWheel.setScrollWheelEnabled(true);
  addAndMakeVisible(_modWheel);

  _modWheel.addListener(this);

  _cc3.setRange(0.0, 1.0);
  _cc3.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
  _cc3.setBounds(_modWheel.getRight() + 10, 10, 30, 80);
  _cc3.setScrollWheelEnabled(true);
  addAndMakeVisible(_cc3);

  _cc3.addListener(this);

  _cc3_cc.setBounds(_modWheel.getX(), _modWheel.getBottom(), _modWheel.getWidth(), 20);
  _cc3_cc.addItem("A", 1);
  _cc3_cc.addItem("B", 2);
  _cc3_cc.addItem("C", 3);
  addAndMakeVisible(_cc3_cc);

  //  box->setLookAndFeel(&_combo_box_style);
  _cc3_cc.setColour(juce::ComboBox::backgroundColourId, juce::Colour{ 245, 245, 245 });
  _cc3_cc.setColour(juce::ComboBox::outlineColourId, juce::Colour{ 189, 189, 189 });
  _cc3_cc.setColour(juce::ComboBox::textColourId, juce::Colour{ 33, 33, 33 });
  _cc3_cc.setColour(juce::ComboBox::arrowColourId, juce::Colour{ 97, 97, 97 });

  _startButton.setBounds(_cc3.getRight() + 10, 10, 30, 30);
  addAndMakeVisible(_startButton);
  _startButton.onClick = []() {
    mstd::MidiManager& midi = mstd::MidiManager::Instance();
    if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
      std::cout << "Send start" << std::endl;
      port->SendStart();
    }
  };

  _stopButton.setBounds(_startButton.getRight() + 10, 10, 30, 30);
  addAndMakeVisible(_stopButton);
  _stopButton.onClick = []() {
    mstd::MidiManager& midi = mstd::MidiManager::Instance();
    if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
      std::cout << "Send stop" << std::endl;
      port->SendStop();
    }
  };
}

void ControlPanelComponent::paint(juce::Graphics& g) {
  g.fillAll(juce::Colours::red);
  g.setColour(juce::Colours::black);
  g.drawLine(0, 0, getWidth(), 0, 5.0f);
}

void ControlPanelComponent::resized() {}

void ControlPanelComponent::sliderValueChanged(juce::Slider* slider) {

  if (slider == &_pitchBend) {
    mstd::MidiManager& midi = mstd::MidiManager::Instance();
    if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
      const float value = float(slider->getValue()) * 0.5f + 0.5f;
      port->SendPitchBend(value);
    }
  }
  else if (slider == &_modWheel) {
    mstd::MidiManager& midi = mstd::MidiManager::Instance();
    if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
      const uint8_t value = (uint8_t)(slider->getValue() * 127);
      std::cout << "VAlue " << (int)value << std::endl;
      port->SendCC(0, 0x01, value);
    }
  }
  else if (slider == &_cc3) {
    mstd::MidiManager& midi = mstd::MidiManager::Instance();
    if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
      const uint8_t value = (uint8_t)(slider->getValue() * 127);
      std::cout << "VAlue " << (int)value << std::endl;
      port->SendCC(0, 0x02, value);
    }
  }

  //
}

void ControlPanelComponent::sliderDragEnded(juce::Slider* slider) {
  std::cout << "sliderDragEnded " << slider->getValue() << std::endl;

  if (slider == &_pitchBend) {
    // Go back to zero.
    //    slider->setValue(0.0);
  }
}
