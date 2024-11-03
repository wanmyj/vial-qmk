/*
Copyright 2012,2013 gezhaoyou <gezhaoyou@126.com>

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
enum layer_names {
    _BASE,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
               KC_ESC,     MO(1),   KC_EQL,     KC_LPRN,    KC_RPRN,    KC_CALCULATOR,  KC_BSPC,
               KC_INSERT,  KC_HOME, KC_PGUP,    KC_NUM_LOCK,    KC_PSLS,    KC_PAST,        KC_PMNS,
               KC_DEL,     KC_END,  KC_PGDN,    KC_P7,      KC_P8,      KC_P9,
                                                KC_P4,      KC_P5,      KC_P6,          KC_PPLS,
                           KC_UP,               KC_P1,      KC_P2,      KC_P3,
               KC_LEFT,    KC_DOWN, KC_RGHT,                KC_P0,      KC_PDOT,        KC_PENT),
   [_FN] = LAYOUT(
               KC_TRNS,             KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS,               KC_TRNS, QK_BOOTLOADER,
               RGB_TOG,   RGB_HUI, RGB_MOD,  KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS,
               KC_TRNS,             RGB_HUD, RGB_RMOD,  KC_TRNS, KC_TRNS, KC_TRNS,
                                                                KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS,
                        RGB_VAI,                                KC_TRNS, KC_TRNS, KC_TRNS,
               RGB_SPD, RGB_VAD, RGB_SPI,                       KC_TRNS, KC_TRNS, QK_CLEAR_EEPROM),
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  debug_matrix=true;
  // debug_keyboard=true;
  // debug_mouse=true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    // uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif 
  return true;
}