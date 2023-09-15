#pragma once

#include <memory>
#include <string>
#include <vector>

#include <unordered_map>
#include "midi_output_port.h"
#include "midi_input_port.h"

namespace mstd {
class MidiManager {
public:
  static constexpr const char* kMainInputPortName = "Midi Studio";
  static constexpr const char* kMainOutputPortName = "Midi Studio";

  static MidiManager& Instance();
  ~MidiManager();

  std::vector<std::string> GetOutputPortNames() const;
  std::vector<std::string> GetInputPortNames() const;

  void CreateVirtualInputPort(const char* name);
  void CreateVirtualOutputPort(const char* name);

  inline mstd::MidiInputPort* GetMainInputPort() { return GetInputPort(kMainInputPortName); }
  inline const mstd::MidiInputPort* GetMainInputPort() const { return GetInputPort(kMainInputPortName); }

  inline mstd::MidiOutputPort* GetMainOutputPort() { return GetOutputPort(kMainOutputPortName); }
  inline const mstd::MidiOutputPort* GetMainOutputPort() const { return GetOutputPort(kMainOutputPortName); }

  mstd::MidiInputPort* GetInputPort(const std::string& name);
  const mstd::MidiInputPort* GetInputPort(const std::string& name) const;

  mstd::MidiOutputPort* GetOutputPort(const std::string& name);
  const mstd::MidiOutputPort* GetOutputPort(const std::string& name) const;

private:
  std::unordered_map<std::string, std::unique_ptr<mstd::MidiOutputPort>> _outputPorts;
  std::unordered_map<std::string, std::unique_ptr<mstd::MidiInputPort>> _inputPorts;

  MidiManager();
};
} // namespace mstd.
