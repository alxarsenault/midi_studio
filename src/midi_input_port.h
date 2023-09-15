#pragma once

#include <cstddef>
#include <memory>

class RtMidiIn;

namespace mstd {
class MidiInputPort {
public:
  MidiInputPort(const char* name);
  ~MidiInputPort();

  inline RtMidiIn* GetPort() const { return _port.get(); }

private:
  struct Helper;

  std::unique_ptr<RtMidiIn> _port;
};
} // namespace mstd.
