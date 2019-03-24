// -*- c++ -*-

// TODO: decide the file names
#include "macros/macros.h"

#include <Arduino.h>

#include <kaleidoglyph/Key.h>
#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/KeyArray.h>
#include <kaleidoglyph/KeyEvent.h>
#include <kaleidoglyph/KeyState.h>
#include <kaleidoglyph/Plugin.h>

#if defined(KALEIDOGLYPH_SKETCH_H)
#include KALEIDOGLYPH_SKETCH_H
#endif

#if defined(KALEIDOGLYPH_MACROS_INC)
#include KALEIDOGLYPH_MACROS_INC
#else
namespace kaleidoglyph {
namespace macros {

enum class MacroAction : byte __attribute__((weak)) {
  none,
};

__attribute__((weak))
Key handleMacro(byte /*index*/) {
  return cKey::clear;
}

} //
} //
#endif


namespace kaleidoglyph {
namespace macros {


// Event handler
EventHandlerResult Plugin::onKeyEvent(KeyEvent& event) {

  if (event.state.toggledOn()) {
    if (isMacrosKey(event.key)) {
      MacrosKey macro_event_key{event.key};
      byte macro_index = macro_event_key.data();
      event.key = handleMacro(macro_index);
      if (event.key.isEmpty()) {
        return EventHandlerResult::abort;
      }
    }
  }
  return EventHandlerResult::proceed;
}


// This could be used for checking `controller.active_keys_` for held Macro keys, and
// adding/removing any number of keycodes based on that.

// After looking at Kaleidoscope-Macros, I think the thing to do for keyboard macros is to
// use this hook, but it may require changes to the Controller so that it gets called for
// keypress events other than KeyboardKey type.
// bool Plugin::preKeyboardReport(hid::keyboard::Report& keyboard_report) {
//   return true;
// }

const PROGMEM
Key ascii_to_key_map[] = {
  // 0x21 - 0x30
  lShift(Key_1),
  lShift(Key_Quote),
  lShift(Key_3),
  lShift(Key_4),
  lShift(Key_5),
  lShift(Key_7),
  Key_Quote,
  lShift(Key_9),
  lShift(Key_0),
  lShift(Key_8),
  lShift(Key_Equals),
  Key_Comma,
  Key_Minus,
  Key_Period,
  Key_Slash,
  Key_0,

  // 0x3a ... 0x40
  lShift(Key_Semicolon),
  Key_Semicolon,
  lShift(Key_Comma),
  Key_Equals,
  lShift(Key_Period),
  lShift(Key_Slash),
  lShift(Key_2),

  // 0x5b ... 0x60
  Key_LeftBracket,
  Key_Backslash,
  Key_RightBracket,
  lShift(Key_6),
  lShift(Key_Minus),
  Key_Backtick,

  // 0x7b ... 0x7e
  lShift(Key_LeftBracket),
  lShift(Key_Backslash),
  lShift(Key_RightBracket),
  lShift(Key_Backtick),
};

Key translateFromAscii(byte keycode) {
  byte modifier_flags{0};
  byte i{0};

  switch (keycode) {
    case 0x08 ... 0x09:
      keycode -= 0x08;
      keycode += cKeyboardKey::Delete.keycode();
      break;
    case 0x0A:
      return cKeyboardKey::Enter;
    case 0x1B:
      return cKeyboardKey::Escape;
    case 0x20:
      return cKeyboardKey::Spacebar;
    case 0x21 ... 0x30:
      i = keycode - 0x21;
      return Key(pgm_read_word(&ascii_to_key_map[i]));
    case 0x31 ... 0x39:
      keycode -= 0x31;
      keycode += cKeyboardKey::_1.keycode();
      break;
    case 0x3A ... 0x40:
      i = keycode - 0x3A;
      return Key(pgm_read_word(&ascii_to_key_map[i + 16]));
    case 0x41 ... 0x5A:
      keycode -= 0x41;
      keycode += cKeyboardKey::A.keycode();
      modifier_flags = KeyboardKey::mod_flag_shift;
      break;
    case 0x5B ... 0x60:
      i = keycode - 0x5B;
      return Key(pgm_read_word(&ascii_to_key_map[i + 23]));
    case 0x61 ... 0x7A:
      keycode -= 0x61;
      keycode += cKeyboardKey::A.keycode();
      break;
    case 0x7B ... 0x7E:
      i = keycode - 0x7B;
      return Key(pgm_read_word(&ascii_to_key_map[i + 29]));
    default:
      return cKey::blank;
  }
  KeyboardKey key{keycode, modifier_flags};
  return Key(key);
}

// void typeProgmemString(const char* pgm_string, KeyAddr k) {
//   byte ascii_code;
//   while (ascii_code = pgm_read_byte(pgm_string++)) {
//     Key key = translateFromAscii(ascii_code);
//     if (key == cKey::blank) continue;
//     //pressKey(k, key);
//     //releaseKey(k);
//   }
// }

// void playProgmemMacro(const Macro* macro_p) {
  
// }

} // namespace macros {
} // namespace kaleidoglyph {
