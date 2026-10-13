// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD
#define WS2812_PIO_USE_PIO1
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB
#define TAPPING_TERM 230
#define MAX_DEFERRED_EXECUTORS 32

// The encoder contacts are scanned through the duplex matrix, not GPIO pins.
#define NUM_ENCODERS 1
#define ENCODER_RESOLUTION 1
#define ENCODER_MAP_KEY_DELAY 10
