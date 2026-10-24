/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#pragma once

/* Enable caps-lock LED */
#define CAPS_LOCK_LED_INDEX 29

#define RGB_MATRIX_KEYPRESSES
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_DEFAULT_HUE 0
#define RGB_MATRIX_DEFAULT_SAT 0
#define RGB_MATRIX_DEFAULT_VAL 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE

#define PERMISSIVE_HOLD
#ifndef CHORDAL_HOLD      // Vial's QMK settings build already passes -DCHORDAL_HOLD
#    define CHORDAL_HOLD
#endif
