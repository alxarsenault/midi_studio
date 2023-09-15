#include "midi_manager.h"
#include "RtMidi.h"

// http://midi.teragonaudio.com/tech/midispec.htm
namespace mstd {

MidiManager& MidiManager::Instance() {
  static MidiManager midi;
  return midi;
}

// void mycallback( double deltatime, std::vector< unsigned char > *message, void *userData )
//{
//   unsigned int nBytes = message->size();
//   for ( unsigned int i=0; i<nBytes; i++ )
//     std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
//   if ( nBytes > 0 )
//     std::cout << "stamp = " << deltatime << std::endl;
// }

MidiManager::MidiManager() {
  CreateVirtualInputPort(kMainOutputPortName);
  CreateVirtualOutputPort(kMainOutputPortName);

  //  RtMidiIn *midiin = new RtMidiIn();
  //
  //    // Check available ports.
  //    unsigned int nPorts = midiin->getPortCount();
  //  std::cout << "nports " << nPorts << std::endl;
  //
  //  for(unsigned int i = 0; i < nPorts; i++) {
  //    std::cout << i << " port name " << midiin->getPortName(i) << std::endl;
  //  }
  //
  //  midiin->openPort(0);
  //  std::cout << "ispopen " << midiin->isPortOpen() << std::endl;
  //
  //  midiin->setCallback(&mycallback);
  //  midiin->ignoreTypes( false, false, false );
}

MidiManager::~MidiManager() {}

std::vector<std::string> MidiManager::GetOutputPortNames() const {

  RtMidiOut midi(RtMidi::Api::MACOSX_CORE, "MIDI Studio");

  const unsigned int count = midi.getPortCount();
  if (!count) {
    return {};
  }

  std::vector<std::string> names;
  names.resize(count);

  for (unsigned int i = 0; i < count; i++) {
    names[i] = midi.getPortName(i);
  }

  return names;
}

std::vector<std::string> MidiManager::GetInputPortNames() const {

  RtMidiIn midi(RtMidi::Api::MACOSX_CORE, "MIDI Studio");

  const unsigned int count = midi.getPortCount();
  if (!count) {
    return {};
  }

  std::vector<std::string> names;
  names.resize(count);

  for (unsigned int i = 0; i < count; i++) {
    names[i] = midi.getPortName(i);
  }

  return names;
}

void MidiManager::CreateVirtualInputPort(const char* name) {
  _inputPorts.emplace(name, std::make_unique<mstd::MidiInputPort>(name));
  //  std::cout << "DSLKDJSDKSJLDKS " << _outputPorts.back()->GetPort()->getPortCount() << std::endl;
}

void MidiManager::CreateVirtualOutputPort(const char* name) {
  //  _outputPorts.push_back();
  _outputPorts.emplace(name, std::make_unique<mstd::MidiOutputPort>(name));
  //  std::cout << "DSLKDJSDKSJLDKS " << _outputPorts.back()->GetPort()->getPortCount() << std::endl;
}

mstd::MidiInputPort* MidiManager::GetInputPort(const std::string& name) {
  auto it = _inputPorts.find(name);
  return it == _inputPorts.end() ? nullptr : it->second.get();
}

const mstd::MidiInputPort* MidiManager::GetInputPort(const std::string& name) const {
  auto it = _inputPorts.find(name);
  return it == _inputPorts.end() ? nullptr : it->second.get();
}

mstd::MidiOutputPort* MidiManager::GetOutputPort(const std::string& name) {
  auto it = _outputPorts.find(name);
  return it == _outputPorts.end() ? nullptr : it->second.get();
}

const mstd::MidiOutputPort* MidiManager::GetOutputPort(const std::string& name) const {
  auto it = _outputPorts.find(name);
  return it == _outputPorts.end() ? nullptr : it->second.get();
}

} // namespace mstd.
