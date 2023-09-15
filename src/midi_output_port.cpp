#include "midi_output_port.h"
#include "RtMidi.h"
#include <algorithm>

namespace mstd {

static void MidiOutputPortErrorCallback(RtMidiError::Type type, const std::string& errorText, void* userData) {
  (void)userData;
  std::cout << "ERROR " << errorText << " " << type << std::endl;
}

MidiOutputPort::MidiOutputPort(const char* name) {
  _port = std::make_unique<RtMidiOut>(RtMidi::Api::MACOSX_CORE, "MIDI Studio");
  _port->openVirtualPort(name);
  _port->setErrorCallback(MidiOutputPortErrorCallback, this);
  //  _port->ignoreTypes( false, false, false );
}

MidiOutputPort::MidiOutputPort(unsigned int index, const char* name) {
  _port = std::make_unique<RtMidiOut>(RtMidi::Api::MACOSX_CORE, "MIDI Studio");
  _port->openPort(index, name);
  _port->setErrorCallback(MidiOutputPortErrorCallback, this);
}

MidiOutputPort::~MidiOutputPort() {
  if (_port) {
    _port->closePort();
    _port.reset();
  }
}

void MidiOutputPort::SendMessage(const unsigned char* message, size_t size) {
  if (_port) {
    _port->sendMessage(message, size);
  }
}

void MidiOutputPort::SendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (_port) {
    uint8_t data[3] = { uint8_t(0x90 + channel), note, velocity };
    _port->sendMessage((const unsigned char*)data, 3);
  }
}

void MidiOutputPort::SendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity) {
  if (_port) {
    uint8_t data[3] = { uint8_t(0x80 + channel), note, velocity };
    _port->sendMessage((const unsigned char*)data, 3);
  }
}

void MidiOutputPort::SendPitchBend(float value) {
  if (_port) {
    const uint16_t pitchbend = (uint16_t)std::min((int)(16384 - 1), (int)(value * (float)16384));
    const uint8_t data[3] = { (uint8_t)0xE0, (uint8_t)(pitchbend & 0x7F), (uint8_t)(pitchbend >> 7) };
    _port->sendMessage((const unsigned char*)data, 3);
  }
}

void MidiOutputPort::SendCC(uint8_t channel, uint8_t cc, uint8_t value) {
  if (_port) {
    const uint8_t data[3] = { (uint8_t)(0xB0 + channel), cc, value };
    _port->sendMessage((const unsigned char*)data, 3);
  }
}

void MidiOutputPort::SendStart() {
  if (_port) {
    const uint8_t data[3] = { (uint8_t)0xB0, (uint8_t)0x20, (uint8_t)127 };
    std::cout << "SendStart -- " << std::endl;
    _port->sendMessage((const unsigned char*)data, 3);
  }
}

void MidiOutputPort::SendStop() {
  if (_port) {
    const uint8_t data[3] = { (uint8_t)0xFC, (uint8_t)0, (uint8_t)0 };
    _port->sendMessage((const unsigned char*)data, 3);
  }
}
} // namespace mstd.
