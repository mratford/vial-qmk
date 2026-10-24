#pragma once

#define VIAL_KEYBOARD_UID {0x1D, 0x7D, 0x0D, 0x98, 0x82, 0x80, 0xFA, 0x7D}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 4 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 15 }


/* keyboard.json sets this to 5; raise it for the two extra layers. */
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#define DYNAMIC_KEYMAP_LAYER_COUNT 6
