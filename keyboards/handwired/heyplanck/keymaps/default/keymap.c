/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "heyplanck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;

enum heyplanck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _MY_MACROS
};

enum heyplanck_keycodes {
  QWERTY = SAFE_RANGE,
  TMUX_SV, // tmux split vertical
  TMUX_SH, // tmux split horizontal
  TMUX_CM, // tmux copy mode
  TMUX_P,  // tmux paste
  TMUX_LP, // tmux move to left pane
  TMUX_RP, // tmux move to right pane
  TMUX_TP, // tmux move to top pane
  TMUX_BP, // tmux move to bottom pane
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define MY_MACROS MO(_MY_MACROS)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Alt  |Super | Alt  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = {
  {KC_TAB,  KC_Q,      KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC},
  {KC_ESC,  KC_A,      KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT},
  {KC_LSFT, KC_Z,      KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT },
  {KC_LCTL, MY_MACROS, KC_LGUI, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT}
},

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      | Vol- | Vol+ | mute |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = {
  {KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN, KC_BSPC},
  {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS,    KC_PLUS,    KC_LCBR, KC_RCBR, KC_PIPE},
  {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  S(KC_NUHS), S(KC_NUBS), KC_HOME, KC_END,  _______},
  {_______, _______, _______, _______, _______, _______, _______, _______,    _______,    KC_VOLD, KC_VOLU, KC_MUTE}
},

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | back | Vol- | Vol+ |foward|
 * `-----------------------------------------------------------------------------------'
 */
  [_RAISE] = {
    {KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL},
    {KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS},
    {_______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, KC_PGUP, KC_PGDN, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, KC_WBAK, KC_VOLD, KC_VOLU, KC_WFWD}
  },

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------------------------------------------------.
   * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |      |      |      |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |      |      |      |      |      |      |      |      |      |      |      |      |
   * `-----------------------------------------------------------------------------------'
   */
  [_ADJUST] = {
    {_______, RESET,   DEBUG,    RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL },
    {_______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  _______, _______},
    {_______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______}
  },

  /* My macros
   */
  [_MY_MACROS] = {
    {_______, _______, _______, _______, _______, _______, _______, _______, _______, TMUX_CM, TMUX_P, _______},
    {_______, _______, _______, _______, _______, _______, TMUX_SH, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, TMUX_SV, _______, _______, _______, _______, _______, _______, _______},
    {_______, _______, _______, _______, _______, _______, _______, _______, TMUX_LP, TMUX_BP, TMUX_TP, TMUX_RP}
  }

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        print("mode just switched to qwerty and this is a huge string\n");
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    // Macros from MY_MACROS layer
    case TMUX_SV:
      if (record->event.pressed) {
        // ctrl + b -> %
        SEND_STRING(SS_LCTRL("b")"%");
        return false;
      }
      break;
    case TMUX_SH:
      if (record->event.pressed) {
        // ctrl + b -> "
        SEND_STRING(SS_LCTRL("b")"\" ");
        return false;
      }
      break;
    case TMUX_CM:
      if (record->event.pressed) {
        // ctrl + b -> [
        SEND_STRING(SS_LCTRL("b")"[");
        return false;
      }
      break;
    case TMUX_P:
      if (record->event.pressed) {
        // ctrl + b -> ]
        SEND_STRING(SS_LCTRL("b")"]");
        return false;
      }
      break;
    case TMUX_LP:
      if (record->event.pressed) {
        // ctrl + b -> left arrow
        SEND_STRING(SS_LCTRL("b")SS_TAP(X_LEFT));
        return false;
      }
      break;
    case TMUX_BP:
      if (record->event.pressed) {
        // ctrl + b -> down arrow
        SEND_STRING(SS_LCTRL("b")SS_TAP(X_DOWN));
        return false;
      }
      break;
    case TMUX_TP:
      if (record->event.pressed) {
        // ctrl + b -> up arrow
        SEND_STRING(SS_LCTRL("b")SS_TAP(X_UP));
        return false;
      }
      break;
    case TMUX_RP:
      if (record->event.pressed) {
        // ctrl + b -> right arrow
        SEND_STRING(SS_LCTRL("b")SS_TAP(X_RIGHT));
        return false;
      }
      break;
  }
  return true;
}
