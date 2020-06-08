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
#include "live_sample.h"
#include "action_layer.h"
#include "raw_hid.h"

extern keymap_config_t keymap_config;

// Layers
enum livesample_layers {
  _DEFAULT,
  _LOWER,
  _RAISE
};

// Custom keycode numbers
enum livesample_keycodes {
  DEFAULT = SAFE_RANGE,
  LOWER, // Keycode to enable the LOWER layer
  RAISE, // Keycode to enable the RAISE layer
  CONSAGRADOS // Keycode of a custom macro
};

#define LOWER MO(_LOWER)  // Define a momentary layer keycode
#define RAISE MO(_RAISE)  // Define a momentary layer keycode

// Tap Dance
//Tap Dance Declarations
enum {
  TD_9_ENTER = 0
};

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  //Tap once for number 9, twice for Enter
  [TD_9_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_ENTER)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Default layer */
[_DEFAULT] = {
  {    KC_1,      KC_2,       KC_3                 },
  {    KC_4,      KC_5,       MT(MOD_LSFT, KC_6)   },
  {    KC_7,      KC_8,       TD(TD_9_ENTER)       },
  {    LOWER,     KC_SPACE,   RAISE},
},

/* Lower layer */
[_LOWER] = {
  {    KC_A,        KC_MS_U,     KC_C      },
  {    KC_MS_L,     KC_MS_D,     KC_MS_R   },
  {    CONSAGRADOS, KC_I,        KC_J      },
  {    _______,     KC_BSPACE,   _______   },
},

/* Raise layer */
[_RAISE] = {
  {    RGB_TOG,     RGB_MOD,    RGB_RMOD   },
  {    KC_D,        KC_F,       RESET      },
  {    DM_REC1,     DM_RSTP,    DM_PLY1    },
  {    _______,     KC_BSPACE,  _______    },
},

};

// This function is used to override a behavior of an existing key or to define a new one
// Here we are sending an string when the keycode CONSAGRADOS is pressed
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CONSAGRADOS:
      if (record->event.pressed) {
        // when keycode CONSAGRADOS is pressed
        SEND_STRING("Boa noite meus consagrados!");
      } else {
        // when keycode CONSAGRADOS is released
      }
      break;
  }
  return true;
}


#ifdef OLED_DRIVER_ENABLE

// Function that is called when something is received by HID
void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);
    oled_clear();
    oled_write_P(PSTR("\n"), false);
    oled_write((char *) data, false);
    oled_render();
}

// Function called then the firmware inits the oled
// I am adding a delay to wait for the display to start
// This function is used to rotate the display
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    _delay_ms(2500);
    return rotation;
}

// Function where you can control the display, it is called at every firmware loop
void oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _DEFAULT:
            oled_write_P(PSTR("Default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("Raise\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }
}
#endif
