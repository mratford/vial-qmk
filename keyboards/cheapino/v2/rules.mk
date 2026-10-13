# SPDX-License-Identifier: GPL-2.0-or-later
CAPS_WORD_ENABLE = yes
CUSTOM_MATRIX = lite
RGBLIGHT_ENABLE = yes
DEFERRED_EXEC_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_DRIVER = custom
EEPROM_DRIVER = wear_leveling
WEAR_LEVELING_DRIVER = rp2040_flash
SRC += matrix.c ghosting.c cheapino_encoder.c
