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

enum td_keycodes {
    SPCPOI,
    BSPSYM
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

#define MODNUM MO(L_NUM)
#define MODNAV MO(L_NAV)
#define TOFUN TO(L_FN)
#define OFFFUN TG(L_FN)
#define QCKLF LCTL(KC_LEFT)
#define QCKRT LCTL(KC_RGHT)
#define LTBKSY LT(L_SYM,KC_BSPC)
#define TDBSSY TD(BSPSYM)
#define TDSPPO TD(SPCPOI)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_QWE] = LAYOUT_ortho_4x6_left(
      KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
      LTBKSY,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
      KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
      KC_LCTL,   MODNAV,  KC_LGUI, KC_LALT, MODNUM,  TDSPPO
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
      KC_EQL,    KC_MINS, KC_0,    KC_9,    KC_8,    KC_7,      
      KC_TRNS,   KC_TILD, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS,
      KC_TRNS,   KC_GRV,  KC_TRNS, KC_TRNS, KC_TRNS, KC_NO
    ),
    [L_NAV] = LAYOUT_ortho_4x6_left(
      KC_INS,    KC_CAPS, KC_PSCR, QCKLF,   KC_UP,   QCKRT,
      KC_DEL,    KC_NO,   KC_SLCK, KC_LEFT, KC_DOWN, KC_RGHT,
      KC_TRNS,   TOFUN,   KC_PAUS, KC_HOME, KC_PGUP, KC_END,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_PGDN, KC_LSFT
    ),
    [L_FN] = LAYOUT_ortho_4x6_left(
      KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
      KC_F7,     KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
      KC_TRNS,   OFFFUN,  RGB_TOG, RGB_MOD, RGB_SAI, RGB_HUI,
      KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, RGB_SAD, BL_TOGG
    )
};

td_state_t cur_dance(qk_tap_dance_state_t *state) {
    switch(state->count){
        case 1:
            if((state->interrupted && !state->pressed) || !state->pressed) return TD_SINGLE_TAP;
            else return TD_SINGLE_HOLD;
        case 2:
            if (state->interrupted && !state->pressed) return TD_DOUBLE_SINGLE_TAP;
            else if ((state->interrupted && state->pressed) || state->pressed) return TD_DOUBLE_HOLD;
            else return TD_DOUBLE_TAP;
        default:
            return TD_UNKNOWN;
    }
}

void spcpoi_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            register_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_POI);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_SPC);
            layer_on(L_POI);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;

    }
}

void spcpoi_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_off(L_POI);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(L_POI);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
    }
}

void bspsym_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            register_code16(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            layer_on(L_SYM);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_BSPC);
            register_code16(KC_BSPC);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_BSPC);
            layer_on(L_SYM);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_BSPC);
            register_code16(KC_BSPC);
            break;

    }
}

void bspsym_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            unregister_code16(KC_BSPC);
            break;
        case TD_SINGLE_HOLD:
            layer_off(L_SYM);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_BSPC);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(L_SYM);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_BSPC);
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SPCPOI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, spcpoi_finished, spcpoi_reset),
    [BSPSYM] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, bspsym_finished, bspsym_reset)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(SPCPOI):
            return 200;
        case TD(BSPSYM):
            return 200;
        default:
            return TAPPING_TERM;
    }
}

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(C6);
  backlight_level(255);
  writePinLow(C6);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case BL_TOGG:
      if (record->event.pressed) {
        if(is_backlight_enabled()) {
            writePinHigh(C6);
        } else {
            writePinLow(C6);
            backlight_level(255);
            return false;
        }
      } else {
        // Do something else when release
      }
      return true; // Skip all further processing of this key
    default:
      return true; // Process all other keycodes normally
  }
}