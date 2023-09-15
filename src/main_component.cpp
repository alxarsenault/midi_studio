#include "main_component.h"
#include "midi_manager.h"

MainComponent::MainComponent() {
  setLookAndFeel(&_combo_box_style);
  addAndMakeVisible(_piano);
  addAndMakeVisible(_ctrlComponent);

  _piano.AddListener(this);

  mstd::MidiManager& midi = mstd::MidiManager::Instance();
  std::vector<std::string> inputs = midi.GetInputPortNames();
  for (size_t i = 0; i < inputs.size(); i++) {
    std::unique_ptr<MidiIORow> row = std::make_unique<MidiIORow>(inputs[i]);
    addAndMakeVisible(row.get());
    _midi_rows.push_back(std::move(row));
  }

  addAndMakeVisible(_ctrl_row);
  _ctrl_row.setBounds(0, 40, 300, 30);

  setSize(935, 800);
}

MainComponent::~MainComponent() { setLookAndFeel(nullptr); }

void MainComponent::paint(juce::Graphics& g) {
  g.fillAll(juce::Colour(0xFF222222));

  g.setFont(juce::Font(16.0f));
  g.setColour(juce::Colours::white);
  g.drawText("Hello World!", getLocalBounds(), juce::Justification::centred, true);
}

void MainComponent::resized() {

  int w = getWidth();
  int y = 0;
  for (size_t i = 0; i < _midi_rows.size(); i++) {
    _midi_rows[i]->setBounds(0, y, w, MidiIORow::kHeight);
    y += MidiIORow::kHeight - 1;
  }

  _ctrl_row.setBounds(0, y + 1, w, 30);

  _piano.setTopLeftPosition(0, getHeight() - _piano.getHeight());

  const int ctrlComponentHeight = 120;
  _ctrlComponent.setBounds(0, _piano.getY() - ctrlComponentHeight - 1, getWidth(), ctrlComponentHeight);
}

void MainComponent::OnPianoNoteOn(uint8_t note) {
  //  juce::ignoreUnused(note);
  mstd::MidiManager& midi = mstd::MidiManager::Instance();

  if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
    port->SendNoteOn(0, note, 80);
  }
  //  std::cout << "note on " << (int)note << std::endl;
}

void MainComponent::OnPianoNoteOff(uint8_t note) {
  mstd::MidiManager& midi = mstd::MidiManager::Instance();

  if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
    port->SendNoteOff(0, note);
  }
  // std::cout << "note off " << (int)note << std::endl;
}
