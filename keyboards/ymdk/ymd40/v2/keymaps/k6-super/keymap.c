/* Copyright 2021 Trent Hoh
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

enum ortho_4x12_layers {
    _SUQWER,
    _SUPKEY,
    _SUSYM,
    _SUFUNC,
    _ADJUST

};

enum td_keycodes {
    SUPSPC,
    SUPSHF,
    SUPFUN
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

#define SUPKEY LT(_SUPKEY, KC_SPC)
#define SUSYM LT(_SUSYM, KC_SPC)
#define SUQSYM LT(_SUSYM, KC_QUOT)
#define SUFNAP LT(_SUFUNC, KC_APP)
#define ADJUST MO(_ADJUST)
#define TDSUSP TD(SUPSPC)
#define TDSUSF TD(SUPSHF)
#define TDSUFN TD(SUPFUN)
#define SUFUNC MO(_SUFUNC)

#define SHFTUP RSFT_T(KC_UP)
#define SHFTDN RSFT_T(KC_DOWN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 /* SUQWER
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │   Y  │   U  │   I  │   O  │   P  │ Bksp │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Bksp │   A  │   S  │   D  │   F  │   G  │   H  │   J  │   K  │   L  │SUQSYM│ Enter│
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │SUFUNC│   Z  │   X  │   C  │   V  │   B  │   N  │   M  │   ,  │   .  │   /  │  Up  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Ctrl │ Shft │ Gui  │ Alt  │ SUSYM│    SUPKEY   │ Space│SUFUNC│ Left │ Right│ Down │
 * └──────┴──────┴──────┴──────┴──────┴─────────────┴──────┴──────┴──────┴──────┴──────┘
 */
    [_SUQWER] = LAYOUT_ortho_4x12_1x2uC(
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_BSPC,
        KC_BSPC,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   SUQSYM, KC_ENT,     
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,SHFTUP,
        KC_LCTL,TDSUFN, KC_LGUI,KC_LALT,TDSUSF, TDSUSP, KC_SPC,         SUFNAP, KC_LEFT,KC_RGHT,SHFTDN
        ),
/* SUPKEY
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ Esc  │   P  │   O  │   I  │   U  │   Y  │ Tab  │   7  │   8  │   9  │   -  │  =   │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │Enter │   '  │   L  │   K  │   J  │   H  │Enter │   4  │   5  │   6  │   *  │   /  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   /  │   .  │   ,  │   M  │   N  │ Bksp │   1  │   2  │   3  │   +  │   -  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │             │   0  │   0  │   .  │   `  │  Del │
 * └──────┴──────┴──────┴──────┴──────┴─────────────┴──────┴──────┴──────┴──────┴──────┘
 */
    [_SUPKEY] = LAYOUT_ortho_4x12_1x2uC(
        KC_ESC, KC_P,   KC_O,   KC_I,   KC_U,   KC_Y,   KC_TAB, KC_7,   KC_8,   KC_9,   KC_MINS,KC_EQL,
        KC_ENT, KC_QUOT,KC_L,   KC_K,   KC_J,   KC_H,   KC_ENT, KC_4,   KC_5,   KC_6,   KC_PAST,KC_PSLS,
        KC_TRNS,KC_SLSH,KC_DOT, KC_COMM,KC_M,   KC_N,   KC_BSPC,KC_1,   KC_2,   KC_3,   KC_PPLS,KC_PMNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_0,   KC_0,   KC_DOT, KC_GRV, KC_DEL
        ),
/* SUSYM
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ Esc  │      │  \   │  [   │  ]   │      │      │  [   │  ]   │  \   │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   '  │   ;  │   (  │   )  │      │      │   (  │   )  │   :  │   '  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │   /  │      │   <  │   >  │      │      │   <  │   >  │   ;  │   /  │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │Space        │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴─────────────┴──────┴──────┴──────┴──────┴──────┘
 */
    [_SUSYM] = LAYOUT_ortho_4x12_1x2uC(
        KC_ESC, KC_NO,  KC_BSLS,KC_LBRC,KC_RBRC,KC_NO,  KC_NO,  KC_LBRC,KC_RBRC,KC_BSLS,KC_NO,  KC_NO,  
        KC_NO,  KC_QUOT,KC_SCLN,KC_LPRN,KC_RPRN,KC_NO,  KC_NO,  KC_LPRN,KC_RPRN,KC_COLN, KC_TRNS,KC_NO,
        KC_TRNS,KC_SLSH,KC_NO,  KC_LABK,KC_RABK,KC_NO,  KC_NO,  KC_LABK,KC_RABK,KC_SCLN,KC_SLSH,KC_NO,  
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_LSFT,        KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO
        ),
/* SUFUNC
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │  F1  │  F2  │  F3  │  F4  │  F5  │  F6  │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │  F7  │  F8  │  F9  │  F10 │  F11 │  F12 │  Ins │ Home │ PgUp │ Vol- │ Vol+ │ Mute │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │ Caps │ADJUST│PrtScn│ ScrLk│ Paus │  Del │  End │ PgDn │ Brt- │ Brt+ │ PgUp │
 * ├──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │             │      │      │ Home │  End │ PgDn │
 * └──────┴──────┴──────┴──────┴──────┴─────────────┴──────┴──────┴──────┴──────┴──────┘
 */
    [_SUFUNC] = LAYOUT_ortho_4x12_1x2uC(
        KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12,
        KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_INS, KC_HOME,KC_PGUP,KC_VOLD,KC_VOLU,KC_MUTE,
        KC_TRNS,KC_CAPS,ADJUST, KC_PSCR,KC_SLCK,KC_PAUS,KC_DEL, KC_END, KC_PGDN,KC_BRID,KC_BRIU,KC_PGUP,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_NO,  KC_NO,  KC_NO,          KC_TRNS,KC_HOME,KC_END, KC_PGDN
        ),
    /* ADJUST
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │      │      │      │      │      │      │      │      │      │      │      │ Reset│
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │      │      │      │      │      │      │      │
 * ├──────┼──────┼──────┼──────┼──────┼──────┴──────┼──────┼──────┼──────┼──────┼──────┤
 * │      │      │      │      │      │             │      │      │      │      │      │
 * └──────┴──────┴──────┴──────┴──────┴─────────────┴──────┴──────┴──────┴──────┴──────┘
 */
    [_ADJUST] = LAYOUT_ortho_4x12_1x2uC(
        KC_NO,  BL_TOGG,RGB_TOG,RGB_MOD,RGB_HUI,RGB_HUD,RGB_SAI,RGB_SAD,RGB_VAI,RGB_VAD,KC_NO,  RESET,
        KC_NO,  BL_STEP,KC_NO,  KC_NO,  MU_MOD, AU_ON,  AU_OFF, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_TRNS,BL_BRTG,KC_TRNS,KC_NO,  MUV_DE, MUV_IN, MU_ON,  MU_OFF, KC_NO,  KC_NO,  KC_NO,  KC_NO,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_TRNS,KC_NO,  KC_NO,  KC_NO
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

void supspc_finished(qk_tap_dance_state_t *state, void *user_data) {
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
            layer_on(_SUPKEY);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            tap_code16(KC_SPC);
            layer_on(_SUPKEY);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;

    }
}

void supspc_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            layer_off(_SUPKEY);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_SUPKEY);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
    }
}

void supshf_finished(qk_tap_dance_state_t *state, void *user_data) {
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
            register_code(KC_LSFT);
            layer_on(_SUPKEY);
            break;
        case TD_DOUBLE_TAP:
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_SUSYM);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            tap_code16(KC_SPC);
            register_code16(KC_SPC);
            break;

    }
}

void supshf_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            layer_off(_SUPKEY);
            break;
        case TD_DOUBLE_TAP:
            unregister_code16(KC_SPC);
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_SUSYM);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            unregister_code16(KC_SPC);
            break;
    }
}

void supfun_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_state = cur_dance(state);
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_on(_SUFUNC);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;

    }
}

void supfun_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_state) {
        case TD_NONE:
            break;
        case TD_UNKNOWN:
            break;
        case TD_SINGLE_TAP:
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_LSFT);
            break;
        case TD_DOUBLE_TAP:
            break;
        case TD_DOUBLE_HOLD:
            layer_off(_SUFUNC);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            break;
    }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [SUPSPC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supspc_finished, supspc_reset),
    [SUPSHF] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supshf_finished, supshf_reset),
    [SUPFUN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, supfun_finished, supfun_reset)
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(SUPSPC):
            return 200;
        case TD(SUPSHF):
            return 200;
        case TD(SUPFUN):
            return 200;
        case RCTL_T(KC_DOWN):
            return 200;
        case RSFT_T(KC_UP):
            return 200;
        default:
            return TAPPING_TERM;
    }
}
