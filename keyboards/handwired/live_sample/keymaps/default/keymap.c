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

// Camadas
enum livesample_layers {
  _DEFAULT,
  _LOWER,
  _RAISE
};

// Código de botões personalizados
enum livesample_keycodes {
  DEFAULT = SAFE_RANGE,
  LOWER, // Código para ativar a camada LOWER
  RAISE, // Código para ativar a camada RAISE
  BTW // Código de uma macro pré definida
};

#define LOWER MO(_LOWER)  // Define a momentary layer keycode
#define RAISE MO(_RAISE)  // Define a momentary layer keycode

// Tap Dance
//Tap Dance Declarations
enum {
  TD_9_ENTER = 0
};

// Tap Dance
qk_tap_dance_action_t tap_dance_actions[] = {
  // Pressione a tecla uma vez para enviar 9, duas vezes para enviar ENTER
  [TD_9_ENTER] = ACTION_TAP_DANCE_DOUBLE(KC_9, KC_ENTER)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Camada padrão */
[_DEFAULT] = {
  {    KC_1,      KC_2,       KC_3                 },
  {    KC_4,      KC_5,       MT(MOD_LSFT, KC_6)   },
  {    KC_7,      KC_8,       TD(TD_9_ENTER)       },
  {    LOWER,     KC_SPACE,   RAISE},
},

/* Camada Lower */
[_LOWER] = {
  {    KC_A,        KC_MS_U,     KC_C      },
  {    KC_MS_L,     KC_MS_D,     KC_MS_R   },
  {    BTW,         KC_I,        KC_J      },
  {    _______,     KC_BSPACE,   _______   },
},

/* Camada Raise */
[_RAISE] = {
  {    RGB_TOG,     RGB_MOD,    RGB_RMOD   },
  {    KC_D,        KC_F,       RESET      },
  {    DM_REC1,     DM_RSTP,    DM_PLY1    },
  {    _______,     KC_BSPACE,  _______    },
},

};

// Função utilizada para sobreescrever o comportamento de um botão existente ou definir um novo.
// Estamos usando essa função para enviar uma mensagem quando o botão definido como BTW for pressionado
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BTW:
      if (record->event.pressed) {
        // Quando o botão BTW for pressionado
        SEND_STRING("Eu uso Arch BTW...");
      } else {
        // when keycode BTW is released
      }
      break;
  }
  return true;
}


#ifdef OLED_DRIVER_ENABLE

// Função chamada quando uma mensagem é recebida por HID
void raw_hid_receive(uint8_t *data, uint8_t length) {
    raw_hid_send(data, length);
    oled_clear();
    oled_write_P(PSTR("\n"), false);
    oled_write((char *) data, false);
    oled_render();
}

// Função chamada na inicialização do OLED, adicionei uma espera aqui para aguardar
// a inicialização do OLED e contornar um bug.
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    _delay_ms(2500);
    return rotation;
}

// Função de controle do display OLED, é chamada uma vez a cada loop do firmware
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
