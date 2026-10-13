// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Preserve the Cheapino V2 identity so existing .vil exports remain compatible.
#define VIAL_KEYBOARD_UID {0x79, 0xED, 0x40, 0xBB, 0x09, 0x8B, 0xC1, 0x9E}
// Hold the outer thumb on each half (Shift and Backspace in Mike's base layer).
#define VIAL_UNLOCK_COMBO_ROWS {6, 2}
#define VIAL_UNLOCK_COMBO_COLS {11, 5}
#define DYNAMIC_KEYMAP_LAYER_COUNT 14

// Space for all 14 layers, 32 tap dances/combos/overrides and runtime settings.
#define WEAR_LEVELING_LOGICAL_SIZE 8192
#define WEAR_LEVELING_BACKING_SIZE 16384
