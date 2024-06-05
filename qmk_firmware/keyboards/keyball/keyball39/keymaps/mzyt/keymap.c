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

enum {
  TD_QESC = 0, // タップダンスの識別子
};

enum custom_keycodes {
    KC_MY_BTN1 = KEYBALL_SAFE_RANGE,  //0x5DBB
    KC_MY_BTN2,
    KC_MY_BTN3,
    KC_MY_CMD_X,                      // CMD+X
    KC_MY_CMD_C,                      // CMD+C
    KC_MY_CMD_V,                      // CMD+V
    KC_MY_CMD_Z,                      // CMD+Z
    KC_MY_CMD_SHIFT_Z,                // CMD+SHIFT_Y
    KC_TEST,
};

tap_dance_action_t  tap_dance_actions[] = {
    [TD_QESC] = ACTION_TAP_DANCE_DOUBLE(KC_Q, KC_ESC) 
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // azn
  // ボタン押下でマウスレイヤー
  [0] = LAYOUT_universal(
    TD(TD_QESC) , KC_W    , KC_E    , KC_R           , KC_T          ,                                     KC_Y         , KC_U    , KC_I    , KC_O    , KC_P          ,
    KC_A        , KC_S    , KC_D    , KC_F           , KC_G          ,                                     KC_H         , KC_J    , KC_K    , KC_L    , LT(4,KC_SCLN) ,
    KC_Z        , KC_X    , KC_C    , KC_V           , KC_B          ,                                     KC_N         , KC_M    , KC_COMM , KC_DOT  , LT(3,KC_SLSH) ,
    KC_LCTL     , KC_LALT , KC_LGUI , KC_LGUI , LT(1,KC_BSPC) , LSFT_T(KC_SPC)   , LCTL_T(KC_ENT) , LT(2,KC_TAB) , XXXXXXX , XXXXXXX , XXXXXXX  , TG(3)
  ),
  // 記号のレイヤー
  [1] = LAYOUT_universal(
    KC_EXLM      , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  ,                            KC_CIRC  , KC_AMPR  , KC_ASTR  , KC_LPRN  , KC_RPRN  ,
    _______      , KC_DOT   , XXXXXXX  , KC_QUOT  , KC_GRV   ,                            KC_BSLS  , KC_MINS  , KC_EQL   , KC_LBRC  , KC_RBRC  ,
    _______      , KC_RABK  , XXXXXXX  , KC_DQUO  , KC_TILD  ,                            KC_PIPE  , KC_UNDS  , KC_PLUS  , KC_LCBR  , KC_RCBR  ,
    KC_MY_CMD_C  , _______  , _______  , _______  , _______  , LSFT(KC_SPC)  ,      _______  , _______  , _______  , _______  , _______  , _______
  ),
  // 数字キーレイヤー
  [2] = LAYOUT_universal(
    KC_1     , KC_2     , KC_3    , KC_4     , KC_5    ,                                   KC_6     , KC_7     , KC_8     , KC_9     , KC_0     ,
    KC_TEST  , _______  , _______ , _______  , _______ ,                                   KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  ,
    _______  , _______  , _______ , _______  , _______ ,                                   _______  , _______  , KC_BTN1  , KC_BTN2  , _______  ,
    _______  , _______  , _______ , _______  , _______ , _______  ,             _______  , _______  , _______  , _______  , _______  , _______
  ),
  // マウスキーのレイヤー
  [3] = LAYOUT_universal(
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    KC_TEST  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                                XXXXXXX  , XXXXXXX  , KC_BTN1  , KC_BTN2  , XXXXXXX  ,
    XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  ,          XXXXXXX ,  XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______
  ),
  // スクロールレイヤー
  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  ,                                _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                                _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  ,                                _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,          _______ ,  _______  , _______  , _______  , _______  , _______
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

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_enable(true);
}
#endif



bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MY_CMD_C:
            if (record->event.pressed) {
#ifdef IS_MACOS
                // macOS specific code
                register_code(KC_LGUI);
                register_code(KC_C);
                unregister_code(KC_C);
                unregister_code(KC_LGUI);
#else
                // Windows specific code
                register_code(KC_LCTL);
                register_code(KC_C);
                unregister_code(KC_C);
                unregister_code(KC_LCTL);
#endif
            }
            return false; // Return false to handle the keycode internally
        case KC_TEST:
            if (record->event.pressed) {
                // キーが押されたときの処理を実行する
                keyball_set_cpi(4U);
            } else {
                // キーが離されたときの処理を実行する
                keyball_set_cpi(8U);
            }
            break;
    }
    return true; // Let QMK handle all other keycodes
}