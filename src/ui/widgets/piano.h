#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <vector>
#include "utils/piano_keys.h"

/// Description
class Piano : public juce::Component {
  static constexpr uint8_t kMidiStartNote = 21;
  static constexpr uint8_t kNoteCount = 88;

  static constexpr uint8_t kWhiteNoteCount = piano_keys::WhiteNoteCount(kMidiStartNote, kNoteCount);
  static constexpr uint8_t kBlackNoteCount = piano_keys::BlackNoteCount(kMidiStartNote, kNoteCount);

  inline static constexpr uint8_t IndexToNote(uint8_t index, uint8_t startNote = kMidiStartNote) {
    return index + startNote;
  }

  inline static constexpr uint8_t NoteToIndex(uint8_t note, uint8_t startNote = kMidiStartNote) {
    return note - startNote;
  }

public:
  struct Style {
    juce::Colour whiteNoteBackground = juce::Colour{ 0xFFFFFFFF };
    juce::Colour whiteNoteContour = juce::Colour{ 0xFF1E1E1E };
    juce::Colour whiteNoteHighlighted = juce::Colour(0xFF882222);

    juce::Colour blackNoteBackground = juce::Colour{ 0xFF000505 };
    juce::Colour blackNoteContour = juce::Colour{ 0xFF1E1E1E };
    juce::Colour blackNoteHighlighted = juce::Colour(0xFF882222);

    juce::Colour labelColor = juce::Colour(0xFF000000);
  };

  inline juce::Rectangle<float> GetNoteRect(uint8_t note) const { return _noteRects[NoteToIndex(note)]; }

  class Listener {
  public:
    virtual ~Listener() = default;

    virtual void OnPianoNoteOn(uint8_t note) { juce::ignoreUnused(note); }
    virtual void OnPianoNoteOff(uint8_t note) { juce::ignoreUnused(note); }
  };

  Piano();

  virtual ~Piano() override;

  inline void AddListener(Listener* l) { _listeners.add(l); }

protected:
  virtual void mouseDown(const juce::MouseEvent& event) override;
  virtual void mouseDrag(const juce::MouseEvent& event) override;
  virtual void mouseUp(const juce::MouseEvent& event) override;
  virtual void paint(juce::Graphics& g) override;

private:
  juce::Point<float> _whiteNoteSize;
  juce::Point<float> _blackNoteSize;
  int _selectedNoteIndex = -1;

  std::array<bool, kNoteCount> _noteStates;
  std::array<juce::Rectangle<float>, kNoteCount> _noteRects;
  std::array<const juce::Rectangle<float>*, kWhiteNoteCount> _whiteNotes;
  std::array<const juce::Rectangle<float>*, kBlackNoteCount> _blackNotes;

  juce::ListenerList<Listener> _listeners;

  Style _style;
  juce::Font _font;

  int FindNote(juce::Point<float> pos) const;
};
