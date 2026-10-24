/* Copyright 2023 ~ 2025 @ Keychron (https://www.keychron.com)
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

enum layers{
  MAC_BASE,
  WIN_BASE,
  MAC_FN1,
  WIN_FN1,
  FN2,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_iso_68(
        HYPR_T(KC_GRV),   KC_1,             KC_2,             KC_3,             KC_4,             KC_5,             KC_6,             KC_7,             KC_8,             KC_9,             KC_0,             KC_MINS,          KC_EQL,           KC_BSPC,          KC_MPLY,
        MEH_T(KC_TAB),    KC_Q,             KC_W,             KC_E,             KC_R,             KC_T,             KC_Y,             KC_U,             KC_I,             KC_O,             KC_P,             KC_LBRC,          KC_RBRC,          KC_PGDN,
        LT(2,KC_ESC),     KC_A,             KC_S,             KC_D,             KC_F,             HYPR_T(KC_G),     HYPR_T(KC_H),     KC_J,             KC_K,             KC_L,             KC_SCLN,          KC_QUOT,          KC_NUHS,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_NUBS,          LGUI_T(KC_Z),     LALT_T(KC_X),     LCTL_T(KC_C),     LSFT_T(KC_V),     MEH_T(KC_B),      MEH_T(KC_N),      RSFT_T(KC_M),     RCTL_T(KC_COMM),  RALT_T(KC_DOT),   RGUI_T(KC_SLSH),  KC_RSFT,          KC_UP,
        KC_LCTL,          KC_LALT,          KC_LGUI,          LT(1,KC_SPC),     KC_RGUI,          MO(3),            KC_RCTL,          KC_LEFT,          KC_DOWN,          KC_RGHT),

    [1] = LAYOUT_iso_68(
        KC_TRNS,          KC_F1,            KC_F2,            KC_F3,            KC_F4,            KC_F5,            KC_F6,            KC_F7,            KC_F8,            KC_F9,            KC_F10,           KC_F11,           KC_F12,           KC_TRNS,          KC_MUTE,
        KC_TRNS,          KC_LCBR,          KC_RCBR,          KC_PIPE,          KC_COLN,          KC_TILD,          KC_HASH,          KC_7,             KC_8,             KC_9,             KC_PAST,          KC_AT,            KC_SPC,           KC_TRNS,
        TO(2),            KC_LPRN,          KC_RPRN,          KC_UNDS,          KC_DQUO,          HYPR_T(KC_GRV),   HYPR_T(KC_EQL),   KC_4,             KC_5,             KC_6,             KC_PMNS,          KC_BSPC,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_SPC,           LGUI_T(KC_LBRC),  LALT_T(KC_RBRC),  LCTL_T(KC_BSLS),  LSFT_T(KC_QUOT),  MEH_T(KC_SLSH),   MEH_T(KC_0),      RSFT_T(KC_1),     RCTL_T(KC_2),     RALT_T(KC_3),     RGUI_T(KC_PPLS),  KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS),

    [2] = LAYOUT_iso_68(
        KC_TRNS,          KC_1,             KC_2,             KC_3,             KC_4,             KC_5,             KC_6,             KC_7,             KC_8,             KC_9,             KC_0,             KC_MINS,          KC_EQL,           KC_BSPC,          KC_MUTE,
        KC_TRNS,          KC_NO,            KC_UP,            KC_NO,            KC_NO,            KC_NO,            KC_HOME,          KC_PGDN,          KC_PGUP,          KC_END,           KC_NO,            KC_NO,            KC_NO,            KC_PGDN,
        TO(0),            KC_LEFT,          KC_DOWN,          KC_RGHT,          KC_NO,            KC_NO,            KC_LEFT,          KC_DOWN,          KC_UP,            KC_RGHT,          KC_NO,            KC_NO,            KC_NO,            KC_ENT,           KC_HOME,
        KC_LSFT,          KC_NUBS,          KC_LGUI,          KC_LALT,          KC_LCTL,          KC_LSFT,          KC_NO,            KC_NO,            KC_LSFT,          KC_RCTL,          KC_RALT,          KC_RGUI,          KC_RSFT,          KC_UP,
        KC_LCTL,          KC_LGUI,          KC_LALT,          KC_SPC,           KC_RALT,          MO(3),            KC_RCTL,          KC_LEFT,          KC_DOWN,          KC_RGHT),

    [3] = LAYOUT_iso_68(
        QK_BOOT,          KC_F1,            KC_F2,            KC_F3,            KC_F4,            KC_F5,            KC_F6,            KC_F7,            KC_F8,            KC_F9,            KC_F10,           KC_F11,           KC_F12,           KC_TRNS,          KC_TRNS,
        RM_TOGG,          RM_NEXT,          RM_VALU,          RM_HUEU,          RM_SATU,          RM_SPDU,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          RM_PREV,          RM_VALD,          RM_HUED,          RM_SATD,          RM_SPDD,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          NK_TOGG,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS),

    [4] = LAYOUT_iso_68(
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS),

    [5] = LAYOUT_iso_68(
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,
        KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS,          KC_TRNS)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [1] = {ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [2] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [3] = {ENCODER_CCW_CW(RM_VALD, RM_VALU) },
    [4] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [5] = {ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif // ENCODER_MAP_ENABLE
