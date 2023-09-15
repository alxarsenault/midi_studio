#include "application.h"
#include "RtMidi.h"

#include "midi_manager.h"
#include "midi_server.h"

int main(int argc, const char* argv[]) {

  mstd::MidiManager& midi = mstd::MidiManager::Instance();
  MidiServer midiServer(8910);

  midiServer.start();
  std::vector<std::string> outputs = midi.GetOutputPortNames();
  std::cout << "Outputs" << std::endl;
  for (const auto& n : outputs) {
    std::cout << n << std::endl;
  }

  std::vector<std::string> inputs = midi.GetInputPortNames();
  std::cout << "Inputs" << std::endl;
  for (const auto& n : inputs) {
    std::cout << n << std::endl;
  }

  return mstd::main(argc, (const char**)argv);
}
