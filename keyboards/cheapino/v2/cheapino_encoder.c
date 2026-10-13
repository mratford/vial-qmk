// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later
// Matrix decoder adapted from tompi/vial-qmk's cheapinov2 branch.
#include "cheapino_encoder.h"
#include "encoder.h"

#define ENC_ROW 3
#define ENC_A_MASK ((matrix_row_t)1 << 2)
#define ENC_B_MASK ((matrix_row_t)1 << 4)

static bool both_pressed;
static bool last_clockwise;
static uint8_t turns;

void encoder_driver_init(void) {
    both_pressed = false;
    last_clockwise = false;
    turns = 0;
}

void encoder_driver_task(void) {
    // matrix_scan_custom samples the contacts and queues events. QMK drains
    // them here in encoder_task, outside matrix scanning and tap/hold handling.
}

static void turned(bool clockwise) {
    if (clockwise != last_clockwise) {
        last_clockwise = clockwise;
        turns = 0;
    }
    if (++turns >= ENCODER_RESOLUTION) {
        turns = 0;
        encoder_queue_event(0, clockwise);
    }
}

void fix_encoder_action(matrix_row_t current_matrix[]) {
    const matrix_row_t contacts = current_matrix[ENC_ROW] & (ENC_A_MASK | ENC_B_MASK);
    if (contacts == (ENC_A_MASK | ENC_B_MASK)) {
        both_pressed = true;
    } else {
        if (both_pressed && contacts) {
            // A+B followed by A is clockwise, followed by B counter-clockwise.
            turned(contacts == ENC_A_MASK);
        }
        both_pressed = false;
    }
    // Contacts are not keys: hide them before debouncing so encoder rotation
    // cannot produce phantom key presses or interrupt a pending mod/layer tap.
    // The encoder button at [3,0] remains a normal, debounced matrix key.
    current_matrix[ENC_ROW] &= ~(ENC_A_MASK | ENC_B_MASK);
}
