// -*- c++ -*-

#include <Arduino.h>

#include <kaleidoglyph/Key.h>
#include <kaleidoglyph/KeyAddr.h>
#include <kaleidoglyph/Plugin.h>
#include <kaleidoglyph/Controller.h>
#include <kaleidoglyph/cKey.h>
#include <kaleidoglyph/EventHandlerResult.h>

#include "macros/MacrosKey.h"

namespace kaleidoglyph {
namespace macros {


class Plugin : public kaleidoglyph::Plugin {

 public:
  Plugin(Controller& controller) : controller_(controller) {}

  // This is where macros will be detected and where some of them can be processed. Just
  // about anything can be handled here, as long as it doesn't require more than one
  // injected key being added at a time. Even then, there is a workaround, but it's ugly
  // -- as long as we know we're going to clean up before the next real event is
  // processed, we can borrow empty keys on the keyboard and use their entries in
  // `active_keys_`.
  EventHandlerResult onKeyEvent(KeyEvent& event);

  // If we need to use two simultaneous injected keys from a macro, we'll need to use this
  // hook, where we have direct access to the keyboard report before it's sent. Using this
  // is potentially buggy, however, because if we want to release a keycode, there might
  // be another key held that's generating the same keycode, which can lead to undesirable
  // repeats. Another possible solution is to use a small supplemental KeyArray to play
  // macros from. Even very complex macros could probably be played on just four keys.
  //bool preKeyboardReport(hid::keyboard::Report& keyboard_report);

  //void postKeyboardReport(KeyEvent event);

  void pressKey(KeyAddr k, Key key);
  void releaseKey(KeyAddr k);
  void typeProgmemString(const char* pgm_string, KeyAddr k);

 private:
  Controller& controller_;

};

} // namespace macros
} // namespace kaleidoglyph {
