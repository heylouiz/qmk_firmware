/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define MANUFACTURER    Live_sample
#define PRODUCT         Live Sample Keyboard
#define DESCRIPTION     A sample keyboard
#define DEVICE_VER      0x0001

// RAW HID configuration
#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

/* key matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 3

/* Keyboard pinout */
#define MATRIX_ROW_PINS { E6, B3, B1, B2 }
#define MATRIX_COL_PINS { B4, B5, B6 }
#define UNUSED_PINS

// RGB configurations
#define RGB_DI_PIN F4  // Pin used to control the RGB Strip
#define RGBLED_NUM 50  // Number of leds in the led strip
#define RGBLIGHT_ANIMATIONS  // Enable rgb animations

// Tap dancing timeout
#define TAPPING_TERM 200

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW


// Other stuff

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */
#define BACKLIGHT_LEVELS 0

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

#endif
