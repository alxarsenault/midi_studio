#include "ui/widgets/piano.h"
#include <iostream>

static inline void SendNoteOnEvent(juce::ListenerList<Piano::Listener>& listeners, uint8_t note) {
  listeners.call([note](Piano::Listener& l) { l.OnPianoNoteOn(note); });
}

static inline void SendNoteOffEvent(juce::ListenerList<Piano::Listener>& listeners, uint8_t note) {
  listeners.call([note](Piano::Listener& l) { l.OnPianoNoteOff(note); });
}

Piano::Piano() {

  _font.setHeight(10);
  _whiteNoteSize = juce::Point<float>{ 18.0f, 54.0f };
  _blackNoteSize = juce::Point<float>{ 12.0f, 30.0f };

  const float kBlackNotesOffset1 = _blackNoteSize.getX() + 1.0f;
  const float kBlackNotesOffset2 = _blackNoteSize.getX() + 1.0f;
  const float kBlackNotesOffset3 = _blackNoteSize.getX() + 1.0f;

  const float kBlackNotesOffset[piano_keys::kOctaveNoteCount] = { 0, kBlackNotesOffset1, 0, kBlackNotesOffset2, 0, 0,
    kBlackNotesOffset1, 0, kBlackNotesOffset3, 0, kBlackNotesOffset2, 0 };

  _noteStates.fill(false);
  float whiteNoteX = -2;
  const float whiteWidth = _whiteNoteSize.getX();

  const juce::Rectangle<float>** black = &_blackNotes[0];
  const juce::Rectangle<float>** white = &_whiteNotes[0];

  for (size_t i = 0; i < kNoteCount; i++) {
    uint8_t note = IndexToNote((uint8_t)i);
    uint8_t noteMod12Index = note % piano_keys::kOctaveNoteCount;

    if (piano_keys::kBlackNotesTable[noteMod12Index]) {
      _noteRects[i] = juce::Rectangle<float>(whiteNoteX - whiteWidth + kBlackNotesOffset[noteMod12Index], 0.0,
          _blackNoteSize.getX(), _blackNoteSize.getY());
      *black++ = &_noteRects[i];
    }
    else {
      _noteRects[i] = juce::Rectangle<float>(whiteNoteX + 1.0f, 0.0f, _whiteNoteSize.getX(), _whiteNoteSize.getY());
      *white++ = &_noteRects[i];
      whiteNoteX += whiteWidth;
    }
  }

  setSize((int)_noteRects.back().getRight(), (int)_whiteNoteSize.getY());

  //  std::cout << "size " << _noteRects.back().getRight() << std::endl;
}

Piano::~Piano() {}

int Piano::FindNote(juce::Point<float> pos) const {

  for (const juce::Rectangle<float>* r : _blackNotes) {
    if (r->contains(pos)) {
      return (int)(r - &_noteRects[0]);
    }
  }

  for (const juce::Rectangle<float>* r : _whiteNotes) {
    if (r->contains(pos)) {
      return (int)(r - &_noteRects[0]);
    }
  }

  return -1;
}

void Piano::mouseDown(const juce::MouseEvent& event) {
  int noteIndex = FindNote(event.position);

  if (noteIndex == _selectedNoteIndex) {
    return;
  }

  if (noteIndex == -1) {
    _noteStates[(size_t)_selectedNoteIndex] = false;
    SendNoteOffEvent(_listeners, IndexToNote((uint8_t)_selectedNoteIndex));
    _selectedNoteIndex = -1;
    repaint();
    return;
  }

  if (_selectedNoteIndex == -1) {
    _selectedNoteIndex = noteIndex;
    _noteStates[(size_t)_selectedNoteIndex] = true;
    SendNoteOnEvent(_listeners, IndexToNote((uint8_t)_selectedNoteIndex));
    repaint();
    return;
  }

  _noteStates[(size_t)_selectedNoteIndex] = false;
  SendNoteOffEvent(_listeners, IndexToNote((uint8_t)_selectedNoteIndex));

  _selectedNoteIndex = noteIndex;
  _noteStates[(size_t)_selectedNoteIndex] = true;
  SendNoteOnEvent(_listeners, IndexToNote((uint8_t)_selectedNoteIndex));
  repaint();
}

void Piano::mouseDrag(const juce::MouseEvent& event) { mouseDown(event); }

void Piano::mouseUp(const juce::MouseEvent& event) {

  int noteIndex = FindNote(event.position);
  if (noteIndex != -1) {

    if (_noteStates[(size_t)noteIndex]) {
      _noteStates[(size_t)noteIndex] = false;
      SendNoteOffEvent(_listeners, IndexToNote((uint8_t)noteIndex));
    }
  }

  if (_selectedNoteIndex != -1) {

    if (_noteStates[(size_t)_selectedNoteIndex]) {
      _noteStates[(size_t)_selectedNoteIndex] = false;
      SendNoteOffEvent(_listeners, IndexToNote((uint8_t)_selectedNoteIndex));
    }
  }
  _selectedNoteIndex = -1;

  repaint();
}

inline static juce::Path getWhiteNotePath(const juce::Rectangle<float>& rect) {
  juce::Path p;
  constexpr float cornerRadius = 2.5f;
  p.addRoundedRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), cornerRadius, cornerRadius, false,
      false, true, true);
  return p;
}

inline static juce::Path getBlackNotePath(const juce::Rectangle<float>& rect) {
  juce::Path p;
  constexpr float cornerRadius = 1.5f;
  p.addRoundedRectangle(rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight(), cornerRadius, cornerRadius, false,
      false, true, true);
  return p;
}

inline static void fillWhiteNote(juce::Graphics& g, const juce::Rectangle<float>& rect) {
  g.fillPath(getWhiteNotePath(rect));
}

inline static void drawWhiteNote(juce::Graphics& g, const juce::Rectangle<float>& rect) {
  g.strokePath(
      getWhiteNotePath(rect), juce::PathStrokeType(1.5f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
}

inline static void fillBlackNote(juce::Graphics& g, const juce::Rectangle<float>& rect) {

  g.fillPath(getBlackNotePath(rect));
}

inline static void drawBlackNote(juce::Graphics& g, const juce::Rectangle<float>& rect) {
  g.strokePath(
      getBlackNotePath(rect), juce::PathStrokeType(1.5f, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
}

void Piano::paint(juce::Graphics& g) {

  // Draw white notes background.
  g.setColour(_style.whiteNoteBackground);
  for (const juce::Rectangle<float>* r : _whiteNotes) {
    fillWhiteNote(g, *r);
  }

  // Draw highlighted white notes contour.
  g.setColour(_style.whiteNoteHighlighted);
  for (size_t i = 0; i < _noteStates.size(); i++) {
    if (_noteStates[i] && piano_keys::IsWhiteNote(IndexToNote((uint8_t)i))) {
      fillWhiteNote(g, _noteRects[i]);
    }
  }

  // Draw white notes contour.
  g.setColour(_style.whiteNoteContour);
  for (const juce::Rectangle<float>* r : _whiteNotes) {
    drawWhiteNote(g, *r);
  }

  // Draw black notes background.
  g.setColour(_style.blackNoteBackground);
  for (const juce::Rectangle<float>* r : _blackNotes) {
    fillBlackNote(g, *r);
  }

  // Draw highlighted black notes.
  g.setColour(_style.blackNoteHighlighted);
  for (size_t i = 0; i < _noteStates.size(); i++) {
    if (_noteStates[i] && piano_keys::IsBlackNote(IndexToNote((uint8_t)i))) {
      fillBlackNote(g, _noteRects[i]);
    }
  }

  // Draw black notes contour.
  g.setColour(_style.blackNoteContour);
  for (const juce::Rectangle<float>* r : _blackNotes) {
    drawBlackNote(g, *r);
  }

  g.setFont(_font);
  g.setColour(_style.labelColor);
  g.drawText("C1", _noteRects[NoteToIndex(24)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C2", _noteRects[NoteToIndex(36)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C3", _noteRects[NoteToIndex(48)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C4", _noteRects[NoteToIndex(60)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C5", _noteRects[NoteToIndex(72)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C6", _noteRects[NoteToIndex(84)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C7", _noteRects[NoteToIndex(96)].translated(0, -3), juce::Justification::centredBottom);
  g.drawText("C8", _noteRects[NoteToIndex(108)].translated(0, -3), juce::Justification::centredBottom);
}
