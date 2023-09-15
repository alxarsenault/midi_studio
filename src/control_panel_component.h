#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class ControlPanelComponent : public juce::Component, private juce::Slider::Listener {
public:
  ControlPanelComponent();

  void paint(juce::Graphics&) override;
  void resized() override;

private:
  juce::Slider _pitchBend;
  juce::Slider _modWheel;
  juce::Slider _cc3;
  juce::TextButton _startButton;
  juce::TextButton _stopButton;
  juce::ComboBox _cc3_cc;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ControlPanelComponent)

  virtual void sliderValueChanged(juce::Slider* slider) override;
  virtual void sliderDragEnded(juce::Slider* slider) override;
};
