#include "control_row.h"
#include "midi_manager.h"

ControlRow::ControlRow() {

  _cc_box.setBounds(0, 0, 200, 20);

  _cc_box.addItemList(
      {
          "0 Bank Select",
          "1 Modulation Wheel",
          "2 Breath Controller",
          "3 Control Change",
          "4 Foot Controller",
          "5 Portamento Time",
          "6 Data Entry MSB",
          "7 Channel Volume",
          "8 Balance",
          "9 Control Change",
          "10 Pan",
          "11 Expression Controller",
          "12 Effect Control 1",
          "13 Effect Control 2",
          "14 Control Change",
          "15 Control Change",
          "16 Control Change",
          "17 Control Change",
          "18 Control Change",
          "19 Control Change",
          "20 Control Change",
          "21 Control Change",
          "22 Control Change",
          "23 Control Change",
          "24 Control Change",
          "25 Control Change",
          "26 Control Change",
          "27 Control Change",
          "28 Control Change",
          "29 Control Change",
          "30 Control Change",
          "31 Control Change",
          "32 Control Change",
          "33 Control Change",
          "34 Control Change",
          "35 Control Change",
          "36 Control Change",
          "37 Control Change",
          "38 Control Change",
          "39 Control Change",
          "40 Control Change",
          "41 Control Change",
          "42 Control Change",
          "43 Control Change",
          "44 Control Change",
          "45 Control Change",
          "46 Control Change",
          "47 Control Change",
          "48 Control Change",
          "49 Control Change",
          "50 Control Change",
          "51 Control Change",
          "52 Control Change",
          "53 Control Change",
          "54 Control Change",
          "55 Control Change",
          "56 Control Change",
          "57 Control Change",
          "58 Control Change",
          "59 Control Change",
          "60 Control Change",
          "61 Control Change",
          "62 Control Change",
          "63 Control Change",
          "64 Damper Pedal (Sustain)",
          "65 Portamento",
          "66 Sostenuto",
          "67 Soft Pedal",
          "68 Legato",
          "69 Hold 2",
          "70 Control Change",
          "71 Control Change",
          "72 Control Change",
          "73 Control Change",
          "74 Control Change",
          "75 Control Change",
          "76 Control Change",
          "77 Control Change",
          "78 Control Change",
          "79 Control Change",
          "80 Control Change",
          "81 Control Change",
          "82 Control Change",
          "83 Control Change",
          "84 Control Change",
          "85 Control Change",
          "86 Control Change",
          "87 Control Change",
          "88 Control Change",
          "89 Control Change",
          "90 Control Change",
          "91 Control Change",
          "92 Control Change",
          "93 Control Change",
          "94 Control Change",
          "95 Control Change",
          "96 Control Change",
          "97 Control Change",
          "98 Control Change",
          "99 Control Change",
          "100 Control Change",
          "101 Control Change",
          "102 Control Change",
          "103 Control Change",
          "104 Control Change",
          "105 Control Change",
          "106 Control Change",
          "107 Control Change",
          "108 Control Change",
          "109 Control Change",
          "110 Control Change",
          "111 Control Change",
          "112 Control Change",
          "113 Control Change",
          "114 Control Change",
          "115 Control Change",
          "116 Control Change",
          "117 Control Change",
          "118 Control Change",
          "119 Control Change",
          "120 Control Change",
          "121 Control Change",
          "122 Control Change",
          "123 Control Change",
          "124 Control Change",
          "125 Control Change",
          "126 Control Change",
          "127 Control Change",

      },
      1);

  _cc_box.setSelectedId(2);
  _cc_box.addListener(this);
  addAndMakeVisible(_cc_box);

  //  box->setLookAndFeel(&_combo_box_style);
  _cc_box.setColour(juce::ComboBox::backgroundColourId, juce::Colour{ 245, 245, 245 });
  _cc_box.setColour(juce::ComboBox::outlineColourId, juce::Colour{ 189, 189, 189 });
  _cc_box.setColour(juce::ComboBox::textColourId, juce::Colour{ 33, 33, 33 });
  _cc_box.setColour(juce::ComboBox::arrowColourId, juce::Colour{ 97, 97, 97 });

  _slider.setRange(0.0, 127.0);
  _slider.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
  _slider.setBounds(_cc_box.getRight(), 10, 300, 25);
  _slider.setScrollWheelEnabled(true);
  addAndMakeVisible(_slider);
  _slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, true, 45, 25);
  _slider.addListener(this);
  _slider.setColour(juce::Slider::textBoxTextColourId, juce::Colour{ 97, 97, 97 });
  _slider.setNumDecimalPlacesToDisplay(0);
}

//    backgroundColourId          = 0x1001200,  /**< A colour to use to fill the slider's background. */
//    thumbColourId               = 0x1001300,  /**< The colour to draw the thumb with. It's up to the look
//                                                   and feel class how this is used. */
//    trackColourId               = 0x1001310,  /**< The colour to draw the groove that the thumb moves along. */
//    rotarySliderFillColourId    = 0x1001311,  /**< For rotary sliders, this colour fills the outer curve. */
//    rotarySliderOutlineColourId = 0x1001312,  /**< For rotary sliders, this colour is used to draw the outer curve's
//    outline. */
//
//    textBoxTextColourId         = 0x1001400,  /**< The colour for the text in the text-editor box used for editing the
//    value. */ textBoxBackgroundColourId   = 0x1001500,  /**< The background colour for the text-editor box. */
//    textBoxHighlightColourId    = 0x1001600,  /**< The text highlight colour for the text-editor box. */
//    textBoxOutlineColourId      = 0x1001700   /**< The colour to use for a border around the text-editor box. */
//};
void ControlRow::paint(juce::Graphics& g) { g.fillAll(juce::Colours::white); }

void ControlRow::resized() {
  juce::Rectangle<int> bounds = getLocalBounds();

  _cc_box.setTopLeftPosition(10, int((bounds.getHeight() - _cc_box.getHeight()) * 0.5f));
  _slider.setTopLeftPosition(_cc_box.getRight() + 10, int((bounds.getHeight() - _slider.getHeight()) * 0.5f));
  // _slider.setBoundsRelative(float proportionalX, float proportionalY, float proportionalWidth, float
  // proportionalHeight)
}

void ControlRow::comboBoxChanged(juce::ComboBox* comboBoxThatHasChanged) { juce::ignoreUnused(comboBoxThatHasChanged); }

void ControlRow::sliderValueChanged(juce::Slider* slider) {

  if (slider == &_slider) {
    mstd::MidiManager& midi = mstd::MidiManager::Instance();
    if (mstd::MidiOutputPort* port = midi.GetMainOutputPort()) {
      const uint8_t cc = (uint8_t)(_cc_box.getSelectedId() - 1);
      const uint8_t value = (uint8_t)slider->getValue();
      std::cout << (int)cc << " VAlue " << (int)value << std::endl;
      port->SendCC(0, cc, value);
    }
  }
}

void ControlRow::sliderDragEnded(juce::Slider*) {}
