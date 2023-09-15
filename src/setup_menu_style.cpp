#include "setup_menu_style.h"

void SetupMenuStyle::drawComboBox(
    juce::Graphics& g, int width, int height, bool, int, int, int, int, juce::ComboBox& box) {
  const float cornerSize = 2.0f;
  const juce::Rectangle<int> boxBounds(0, 0, width, height);

  g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
  g.fillRoundedRectangle(boxBounds.toFloat(), cornerSize);

  g.setColour(box.findColour(juce::ComboBox::outlineColourId));
  g.drawRoundedRectangle(boxBounds.toFloat().reduced(0.5f, 0.5f), cornerSize, 1.0f);

  g.setColour(box.findColour(juce::ComboBox::arrowColourId));
  juce::Path triangle;
  triangle.addTriangle(box.getWidth() - 20, 7, box.getWidth() - 10, 7, box.getWidth() - 15, 13);
  g.fillPath(triangle);
}

juce::Font SetupMenuStyle::getComboBoxFont(juce::ComboBox&) {
  //      return Font(jmin(16.0f, box.getHeight() * 0.85f));
  return juce::Font("Helvetica", 12, 0);
}

void SetupMenuStyle::positionComboBoxText(juce::ComboBox& box, juce::Label& label) {
  label.setBounds(1, 2, box.getWidth() - 30, box.getHeight() - 2);
  label.setFont(getComboBoxFont(box));
}

juce::Label* SetupMenuStyle::createComboBoxTextBox(juce::ComboBox&) {
  return new juce::Label(juce::String(), juce::String());
}

void SetupMenuStyle::drawPopupMenuBackground(juce::Graphics& g, int width, int height) {
  g.fillAll({ 238, 238, 238 });
  juce::ignoreUnused(width, height);
}

void SetupMenuStyle::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area, const bool isSeparator,
    const bool isActive, const bool isHighlighted, const bool isTicked, const bool hasSubMenu, const juce::String& text,
    const juce::String& shortcutKeyText, const juce::Drawable* icon, const juce::Colour* const textColourToUse) {
  const juce::Colour txtColor{ 33, 33, 33 };
  const juce::Colour highlightTxtColor{ 33, 33, 33 };
  const juce::Colour highlightColor{ 224, 224, 224 };

  if (isSeparator) {
    auto r = area.reduced(5, 0);
    r.removeFromTop(juce::roundToInt((r.getHeight() * 0.5f) - 0.5f));

    g.setColour(txtColor.withAlpha(0.3f));
    g.fillRect(r.removeFromTop(1));
  }
  else {
    auto textColour = (textColourToUse == nullptr ? txtColor : *textColourToUse);

    auto r = area.reduced(1);

    if (isHighlighted && isActive) {
      g.setColour(highlightColor);
      g.fillRect(r);

      g.setColour(highlightTxtColor);
    }
    else {
      g.setColour(textColour.withMultipliedAlpha(isActive ? 1.0f : 0.5f));
    }

    r.reduce(juce::jmin(5, area.getWidth() / 20), 0);

    auto font = juce::Font("Helvetica", 12, 0);

    const auto maxFontHeight = r.getHeight() / 1.3f;

    if (font.getHeight() > maxFontHeight)
      font.setHeight(maxFontHeight);

    g.setFont(font);

    auto iconArea = r.removeFromLeft(juce::roundToInt(maxFontHeight)).toFloat();

    if (icon != nullptr) {
      icon->drawWithin(
          g, iconArea, juce::RectanglePlacement::centred | juce::RectanglePlacement::onlyReduceInSize, 1.0f);
    }
    else if (isTicked) {
      const auto tick = getTickShape(1.0f);
      g.fillPath(tick, tick.getTransformToScaleToFit(iconArea.reduced(iconArea.getWidth() / 5, 0).toFloat(), true));
    }

    if (hasSubMenu) {
      const auto arrowH = 0.6f * getPopupMenuFont().getAscent();

      const auto x = (float)r.removeFromRight((int)arrowH).getX();
      const auto halfH = (float)r.getCentreY();

      juce::Path path;
      path.startNewSubPath(x, halfH - arrowH * 0.5f);
      path.lineTo(x + arrowH * 0.6f, halfH);
      path.lineTo(x, halfH + arrowH * 0.5f);

      g.strokePath(path, juce::PathStrokeType(2.0f));
    }

    r.removeFromRight(3);
    g.drawFittedText(text, r, juce::Justification::centredLeft, 1);

    if (shortcutKeyText.isNotEmpty()) {
      auto f2 = font;
      f2.setHeight(f2.getHeight() * 0.75f);
      f2.setHorizontalScale(0.95f);
      g.setFont(f2);

      g.drawText(shortcutKeyText, r, juce::Justification::centredRight, true);
    }
  }
}

void SetupMenuStyle::drawScrollbar(juce::Graphics& g, juce::ScrollBar& scrollbar, int x, int y, int width, int height,
    bool isScrollbarVertical, int thumbStartPosition, int thumbSize, bool isMouseOver, bool isMouseDown) {
  juce::ignoreUnused(isMouseDown, scrollbar);

  juce::Rectangle<int> thumbBounds;

  if (isScrollbarVertical) {
    thumbBounds = { x, thumbStartPosition, width, thumbSize };
  }
  else {
    thumbBounds = { thumbStartPosition, y, thumbSize, height };
  }

  const juce::Colour c{ 117, 117, 117 };
  g.setColour(isMouseOver ? c.brighter(0.25f) : c);
  g.fillRoundedRectangle(thumbBounds.reduced(1).toFloat(), 4.0f);
}

void SetupMenuStyle::drawPopupMenuUpDownArrow(juce::Graphics& g, int width, int height, bool isScrollUpArrow) {
  const float hw = width * 0.5f;
  const float arrowW = height * 0.3f;
  const float y1 = height * (isScrollUpArrow ? 0.6f : 0.3f);
  const float y2 = height * (isScrollUpArrow ? 0.3f : 0.6f);

  juce::Path p;
  p.addTriangle(hw - arrowW, y1, hw + arrowW, y1, hw, y2);
  g.setColour(juce::Colour{ 97, 97, 97 }.withAlpha(0.5f));
  g.fillPath(p);
}
