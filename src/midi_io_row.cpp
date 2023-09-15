#include "midi_io_row.h"
#include "midi_manager.h"

MidiIORow::MidiIORow(const std::string& name) {

  _label.setText(name, juce::NotificationType::dontSendNotification);
  _label.setBounds(10, 10, 100, 30);
  _label.setMinimumHorizontalScale(1.0f);
  _label.setColour(juce::Label::textColourId, juce::Colours::black);

  addAndMakeVisible(_label);
}
void MidiIORow::paint(juce::Graphics& g) {
  juce::Rectangle<int> bounds = getLocalBounds();

  g.fillAll(juce::Colours::white);

  g.setColour(juce::Colours::lightgrey);
  g.drawRect(bounds);
}

void MidiIORow::resized() {
  juce::Rectangle<int> bounds = getLocalBounds();
  _label.setTopLeftPosition(10, int((bounds.getHeight() - _label.getHeight()) * 0.5f));
}
