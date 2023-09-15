#include "midi_input_port.h"
#include "RtMidi.h"
#include <span>

namespace mstd {

// // https://www.midi.org/specifications-old/item/table-2-expanded-messages-list-status-bytes

struct MidiInputPort::Helper {
  static void MidiInputPortErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData) {
    (void)userData;
    std::cout << "ERROR " << errorText << " " << type << std::endl;
  }

  static void MidiInputPortCallback(double deltatime, std::vector<unsigned char>* message, void* userData) {
    (void)userData;

    if (!message) {
      return;
    }

    std::span<unsigned char> data(*message);
    if (data.empty()) {
      return;
    }

    if (data[0] == 0xF8) {
      //      std::cout << "Time Clock stamp = " << deltatime << std::endl;
      return;
    }

    for (size_t i = 0; i < data.size(); i++) {
      std::cout << "Byte " << i << " = " << (int)message->at(i) << ", ";
    }

    std::cout << "stamp = " << deltatime << std::endl;
  }
};

MidiInputPort::MidiInputPort(const char* name) {
  _port = std::make_unique<RtMidiIn>(RtMidi::Api::MACOSX_CORE, "MIDI Studio");
  _port->openVirtualPort(name);
  _port->setCallback(&Helper::MidiInputPortCallback, this);
  _port->setErrorCallback(&Helper::MidiInputPortErrorCallback, this);
  _port->ignoreTypes(false, false, false);
}

MidiInputPort::~MidiInputPort() {
  if (_port) {
    _port->closePort();
    _port.reset();
  }
}
} // namespace mstd.
