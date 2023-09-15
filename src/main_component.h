#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "ui/widgets/piano.h"
#include "control_panel_component.h"
#include "setup_menu_style.h"
#include "control_row.h"
#include "midi_io_row.h"

class MainComponent : public juce::Component, private Piano::Listener {
public:
  MainComponent();
  virtual ~MainComponent() override;
  void paint(juce::Graphics&) override;
  void resized() override;

protected:
  virtual void OnPianoNoteOn(uint8_t note) override;
  virtual void OnPianoNoteOff(uint8_t note) override;

private:
  ControlRow _ctrl_row;
  std::vector<std::unique_ptr<MidiIORow>> _midi_rows;
  ControlPanelComponent _ctrlComponent;
  Piano _piano;

  SetupMenuStyle _combo_box_style;

  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
