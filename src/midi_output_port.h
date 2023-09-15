#pragma once

#include <cstddef>
#include <memory>

class RtMidiOut;

namespace mstd {
class MidiOutputPort {
public:
  MidiOutputPort(const char* name);
  MidiOutputPort(unsigned int index, const char* name);
  ~MidiOutputPort();

  void SendMessage(const unsigned char* message, size_t size);

  void SendNoteOn(uint8_t channel, uint8_t note, uint8_t velocity = 127);
  void SendNoteOff(uint8_t channel, uint8_t note, uint8_t velocity = 0);

  void SendPitchBend(float value);
  void SendCC(uint8_t channel, uint8_t cc, uint8_t value);

  void SendStart();
  void SendStop();

  inline RtMidiOut* GetPort() const { return _port.get(); }

private:
  std::unique_ptr<RtMidiOut> _port;
};

} // namespace mstd.
