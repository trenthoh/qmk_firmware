/* Copyright 2021 Simon Arlott
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
#include QMK_KEYBOARD_H

enum layer_names {
    L_NUM,
    L_BL,
    L_RGB
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_NUM] = LAYOUT_ortho_6x4(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      LT(2,KC_BSPC),KC_A, KC_S,    KC_D,    KC_F,    KC_G,
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
      KC_LCTL,   MO(4),   KC_LGUI, KC_LALT, MO(3),   LT(1,KC_SPC)
    ),
    [L_BL] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, BL_ON,   _______, BL_INC,
        _______, BL_TOGG, _______, BL_INC,
        _______, BL_OFF,  _______, BL_DEC,
        BL_BRTG, _______, _______, BL_DEC
    ),
    [L_RGB] = LAYOUT_ortho_6x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, RGB_MOD, _______, RGB_VAI,
        _______, RGB_TOG, _______, RGB_VAI,
        _______, RGB_RMOD,_______, RGB_VAD,
        RGB_M_R, _______, _______, RGB_VAD
    )
};
