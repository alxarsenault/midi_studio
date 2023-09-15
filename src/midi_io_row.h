#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class MidiIORow : public juce::Component {
public:
  static constexpr int kHeight = 40;
  MidiIORow(const std::string& name);

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  juce::Label _label;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MidiIORow)
};
