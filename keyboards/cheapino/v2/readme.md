# Cheapino V2

Vial port for Thomas Haukland's Cheapino V2, with one RP2040-Zero controller
and a passive right half connected by RJ45. This is the V2 duplex matrix;
it is not suitable for Cheapino V1.

Hardware sources: [tompi/vial-qmk, cheapinov2](https://github.com/tompi/vial-qmk/tree/9100f29f3e811968614aa6c5e7c8b02662922e9d/keyboards/cheapino),
commit `9100f29f3e811968614aa6c5e7c8b02662922e9d` (GPL-2.0-or-later).
The original GPIO matrix and V2 ghost suppression are retained. The encoder
uses QMK's custom driver and event queue; its A/B contacts are removed from
the key matrix before debouncing. Vial and QMK use the physical Vial layout,
including rotated thumbs, encoder button and explicit left/right handedness.

Build Mike's profile from the repository root:

```sh
qmk compile -kb cheapino/v2 -km mikevial
```

See [the profile notes](keymaps/mikevial/readme.md) for flashing and restoring
the saved configuration.

Run the host encoder regression tests:

```sh
python3 keyboards/cheapino/v2/tests/test_encoder.py
```
