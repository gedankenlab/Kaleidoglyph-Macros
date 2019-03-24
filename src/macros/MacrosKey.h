// -*- c++ -*-

#pragma once

#include <Arduino.h>

#include <assert.h>
#include "kaleidoglyph/Key.h"
#include "kaleidoglyph/Key/PluginKey.h"

#if defined(KALEIDOGLYPH_MACROS_CONSTANTS_H)
#include KALEIDOGLYPH_MACROS_CONSTANTS_H
#else
namespace kaleidoglyph {
namespace macros {

constexpr byte key_type_id{0b0000011};

}  // namespace macros
}  // namespace kaleidoglyph
#endif

namespace kaleidoglyph {
namespace macros {

typedef PluginKey<key_type_id> MacrosKey;

constexpr
bool isMacrosKey(Key key) {
  return MacrosKey::verifyType(key);
}

}  // namespace macros
}  // namespace kaleidoglyph
