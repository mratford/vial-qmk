#!/usr/bin/env python3
# SPDX-License-Identifier: GPL-2.0-or-later
"""Host-side regression tests for the matrix encoder driver; no board required."""
from pathlib import Path
import subprocess
import tempfile
import unittest

DRIVER = Path(__file__).resolve().parents[1] / 'cheapino_encoder.c'

HARNESS = r'''
#include <assert.h>
#include <string.h>
#include "matrix.h"
#include "encoder.h"
void fix_encoder_action(matrix_row_t matrix[]);
static unsigned count;
static bool directions[16];
bool encoder_queue_event(uint8_t index, bool clockwise) {
    assert(index == 0);
    assert(count < 16);
    directions[count++] = clockwise;
    return true;
}
static void sample(unsigned contacts) {
    matrix_row_t matrix[8] = {0x21, 0x03, 0x30, 1, 0x840, 0x180, 0x600, 0};
    matrix_row_t expected[8];
    memcpy(expected, matrix, sizeof(matrix));
    matrix[3] |= contacts;
    fix_encoder_action(matrix);
    // The A/B bits vanish, but the button and every other row are untouched.
    assert(memcmp(matrix, expected, sizeof(matrix)) == 0);
}
static void detent(bool clockwise) {
    sample(0);
    sample(clockwise ? 16 : 4);
    sample(20);
    sample(20); // remaining on a contact cannot retrigger
    sample(clockwise ? 4 : 16);
    sample(clockwise ? 4 : 16);
    sample(0);
}
int main(void) {
    encoder_driver_init();
    encoder_driver_task();
    sample(4); sample(0); sample(16); sample(0);
    assert(count == 0); // no AB transition, no turn
    sample(20); sample(0); sample(4); sample(0);
    assert(count == 0); // interrupted transition must not leave a stale latch
    for (int i = 0; i < ENCODER_RESOLUTION; ++i) detent(true);
    assert(count == 1 && directions[0]);
    for (int i = 0; i < ENCODER_RESOLUTION; ++i) detent(false);
    assert(count == 2 && !directions[1]);
#if ENCODER_RESOLUTION > 1
    // A change of direction discards incomplete travel in the old direction.
    detent(true);
    detent(false);
    assert(count == 2);
    for (int i = 1; i < ENCODER_RESOLUTION; ++i) detent(false);
    assert(count == 3 && !directions[2]);
#endif
    unsigned old_count = count;
    sample(20);
    encoder_driver_init();
    sample(4); sample(0);
    assert(count == old_count);
    return 0;
}
'''


class EncoderTests(unittest.TestCase):
    def test_contacts_and_queued_directions(self):
        for resolution in (1, 2):
            with self.subTest(resolution=resolution), tempfile.TemporaryDirectory() as tmp:
                root = Path(tmp)
                (root / 'matrix.h').write_text(
                    '#pragma once\n#include <stdint.h>\n#include <stdbool.h>\n'
                    'typedef uint16_t matrix_row_t;\n'
                )
                (root / 'encoder.h').write_text(
                    '#pragma once\n#include "matrix.h"\n'
                    'bool encoder_queue_event(uint8_t index, bool clockwise);\n'
                    'void encoder_driver_init(void);\nvoid encoder_driver_task(void);\n'
                )
                (root / 'test.c').write_text(HARNESS)
                exe = root / 'test'
                subprocess.run([
                    'cc', '-std=c11', '-Wall', '-Wextra', '-Werror',
                    f'-DENCODER_RESOLUTION={resolution}', '-I', str(root),
                    str(DRIVER), str(root / 'test.c'), '-o', str(exe),
                ], check=True)
                subprocess.run([str(exe)], check=True)


if __name__ == '__main__':
    unittest.main()
