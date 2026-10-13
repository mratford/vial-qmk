# Mike's Cheapino V2 Vial profile

Built for Vial-QMK `dd43959ae5c08d8a28d38a1acf7b04e86b14a344`
(2026-07-26), the upstream `vial` branch head checked on 2026-09-09.

- 14 dynamic layers, with default key and encoder assignments from `cheapino.vil`.
- Original Cheapino V2 UID and 8x12 matrix, including the encoder button at `3,0`.
- Vial runtime settings, tap dance, combos, overrides and RGB controls.
- 8 KiB of emulated EEPROM backed by 16 KiB of RP2040 flash.
- Vial unlock: hold the outer thumb on each half (Shift and Backspace on layer 0).
- Bootmagic: hold Q (physical top-left key, matrix `4,10`) while connecting USB.
  This resets EEPROM and enters the bootloader; use BOOT/RESET for ordinary updates.

## Build

From the repository root:

```sh
qmk compile -kb cheapino/v2 -km mikevial
```

Output: `cheapino_v2_mikevial.uf2` in the repository root.

## Flash and restore

1. Save your current settings in Vial if they have changed since the included export.
2. Hold BOOT on the RP2040-Zero while connecting USB, or hold BOOT and press RESET.
3. Copy `cheapino_v2_mikevial.uf2` onto the `RPI-RP2` drive. It will reboot.
4. Open Vial and load `cheapino.vil` from this profile to restore the complete
   configuration, including runtime tapping and mouse settings. Unlock when prompted
   using the two outer thumb keys described above.
5. Check all 36 keys, encoder press and both turn directions, then save a fresh export.

The compiled defaults contain the key and encoder maps. Runtime settings and
other dynamic data are restored by loading the export; old EEPROM contents
are not assumed compatible with this newer Vial version and storage size.
The firmware has been built and checked in software; physical operation needs
verification on the keyboard after flashing.
