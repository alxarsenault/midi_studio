#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

class SetupMenuStyle : public juce::LookAndFeel_V4 {
public:
  virtual void drawComboBox(
      juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) override;

  virtual juce::Font getComboBoxFont(juce::ComboBox& box) override;

  virtual void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override;

  virtual juce::Label* createComboBoxTextBox(juce::ComboBox&) override;

  virtual void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override;

  virtual void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area, const bool isSeparator,
      const bool isActive, const bool isHighlighted, const bool isTicked, const bool hasSubMenu,
      const juce::String& text, const juce::String& shortcutKeyText, const juce::Drawable* icon,
      const juce::Colour* const textColourToUse) override;

  virtual void drawScrollbar(juce::Graphics& g, juce::ScrollBar& scrollbar, int x, int y, int width, int height,
      bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) override;

  virtual void drawPopupMenuUpDownArrow(juce::Graphics& g, int width, int height, bool isScrollUpArrow) override;
};
