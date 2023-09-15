#pragma once

#include <stdint.h>

namespace piano_keys {
inline constexpr uint8_t kOctaveNoteCount = 12;

enum class Note : uint8_t { C, Cs, D, Ds, E, F, Fs, G, Gs, A, As, B };

#define ONE_OCTAVE 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11
inline constexpr uint8_t kNoteTable[128] = {
  ONE_OCTAVE, // 0
  ONE_OCTAVE, // 12
  ONE_OCTAVE, // 24
  ONE_OCTAVE, // 36
  ONE_OCTAVE, // 48
  ONE_OCTAVE, // 60
  ONE_OCTAVE, // 72
  ONE_OCTAVE, // 84
  ONE_OCTAVE, // 96
  ONE_OCTAVE, // 108,
  0, //    120
  1, //    121
  2, //    122
  3, //    123
  4, //    124
  5, //    125
  6, //    126
  7 //    127
};
#undef ONE_OCTAVE

inline constexpr const bool kBlackNotesTable[kOctaveNoteCount] = { 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 1, 0 };
inline constexpr const bool kWhiteNotesTable[kOctaveNoteCount] = { 1, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 1 };

inline constexpr const char* kNoteLabels[kOctaveNoteCount]
    = { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#", "B" };

inline static constexpr const char* NoteLabel(uint8_t note) { return kNoteLabels[kNoteTable[note]]; }

inline static constexpr bool IsBlackNote(uint8_t note) { return kBlackNotesTable[kNoteTable[note]]; }
inline static constexpr bool IsWhiteNote(uint8_t note) { return kWhiteNotesTable[kNoteTable[note]]; }

inline static constexpr uint8_t WhiteNoteCount(uint8_t startNote, uint8_t noteCount) {
  uint8_t count = 0;
  for (uint8_t i = startNote; i < startNote + noteCount; i++) {
    count += IsWhiteNote(i);
  }
  return count;
}

inline static constexpr uint8_t BlackNoteCount(uint8_t startNote, uint8_t noteCount) {
  return noteCount - WhiteNoteCount(startNote, noteCount);
}
} // namespace piano_keys
