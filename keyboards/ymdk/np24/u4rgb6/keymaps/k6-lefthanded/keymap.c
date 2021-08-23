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

enum ortho_4x6_layers {
    L_QWE,
    L_POI,
    L_SYM,
    L_NUM,
    L_NAV,
    L_FN
};

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

static td_state_t td_state;

td_state_t cur_dance(qk_tap_dance_state_t *state);

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_QWE] = LAYOUT_ortho_4x6_left(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      LT(2,KC_BSPC),KC_A, KC_S,    KC_D,    KC_F,    KC_G,
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
      KC_LCTL,   MO(4),   KC_LGUI, KC_LALT, MO(3),   LT(1,KC_SPC)
    ),
    [L_POI] = LAYOUT_ortho_4x6_left(
      KC_ESC,    KC_P,    KC_O,    KC_I,    KC_U,    KC_Y,
      KC_ENT,    KC_QUOT, KC_L,    KC_K,    KC_J,    KC_H,
      KC_TRNS,   KC_SLSH, KC_DOT,  KC_COMM, KC_M,    KC_N,
      KC_TRNS,   KC_NO,   KC_TRNS, KC_TRNS, KC_NO,   KC_TRNS
    ),
    [L_SYM] = LAYOUT_ortho_4x6_left(
      KC_NO,     KC_BSLS, KC_PIPE, KC_LCBR, KC_RCBR, KC_NO,
      KC_TRNS,   KC_QUOT, KC_DQUO, KC_LBRC, KC_RBRC, KC_NO,
      KC_TRNS,   KC_SCLN, KC_COLN, KC_LT,   KC_GT,   KC_NO,
      KC_TRNS,   KC_NO,   KC_TRNS, KC_TRNS, KC_NO,   KC_NO
    ),
    [L_NUM] = LAYOUT_ortho_4x6_left(
      KC_1,      KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
      KC_7,      KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,
      KC_TRNS,   KC_TILD, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,
      KC_TRNS,   KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
    ),
    [L_NAV] = LAYOUT_ortho_4x6_left(
      KC_INS,    KC_NO,   KC_PSCR, LCTL(KC_LEFT),   KC_UP,   LCTL(KC_RGHT),
      KC_DEL,    KC_NO,   KC_SLCK, KC_LEFT, KC_DOWN, KC_RGHT,
      KC_TRNS,   TT(5),   KC_PAUS, KC_HOME, KC_PGUP, KC_END,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_LSFT
    ),
    [L_FN] = LAYOUT_ortho_4x6_left(
      KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      KC_F7,     KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      KC_TRNS,   KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_NO,   BL_TOGG
    )
};
