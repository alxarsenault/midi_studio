#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include "control_panel_component.h"

class ControlRow : public juce::Component, private juce::Slider::Listener, private juce::ComboBox::Listener {
public:
  ControlRow();

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  juce::Slider _slider;
  juce::ComboBox _cc_box;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlRow)

  virtual void comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) override;
  virtual void sliderValueChanged(juce::Slider* slider) override;
  virtual void sliderDragEnded(juce::Slider* slider) override;
};
