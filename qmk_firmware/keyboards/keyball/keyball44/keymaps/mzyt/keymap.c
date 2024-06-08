/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default (VIA)
  [0] = LAYOUT_universal(
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y      , KC_U     , KC_I     , KC_O     , KC_P     , KC_DEL   ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H      , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    KC_LCTL  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N      , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_INT1  ,
               KC_BTN2  , KC_BTN1  , KC_LGUI  , MO(1)    , KC_SPC   ,                                        KC_ENT    , MO(2)    , _______  , _______  , KC_RALT
  ),

  [1] = LAYOUT_universal(
    _______  , KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  ,                                         KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_LPRN  , KC_RPRN  , _______  ,
    _______  , _______  , _______  , _______  , KC_QUOT  , KC_GRV   ,                                         KC_BSLS  , KC_MINS  , KC_EQL   , KC_LBRC  , KC_RBRC  , _______  ,
    _______  , _______  , _______  , _______  , KC_DQUO  , KC_TILD  ,                                         KC_PIPE  , KC_UNDS  , KC_PLUS  , KC_LCBR  , KC_RCBR  , _______  ,
              XXXXXXX   , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                         XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),

  [2] = LAYOUT_universal(
    _______  ,KC_1      , KC_2     , KC_3     , KC_4     , KC_5    ,                                          KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , _______  ,
    _______  ,_______   , _______  , _______  , _______  , KC_LNG1 ,                                          KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  , _______  ,
    _______  ,_______   , _______  , _______  , _______  , KC_LNG2 ,                                          _______  , _______  , _______  , _______  , _______  , _______  ,
              XXXXXXX   , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                         XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX
  ),

  [3] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
               _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______
  ),
  // スクロールレイヤー
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______ , _______  ,
               _______  , _______  , _______  , _______  , _______ ,                                        _______  , _______  , _______  , _______ , _______
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 4);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif
