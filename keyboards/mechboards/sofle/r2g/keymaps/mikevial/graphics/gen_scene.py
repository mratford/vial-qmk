#!/usr/bin/env python3
# Copyright 2026 Mike Ratford
# SPDX-License-Identifier: GPL-2.0-or-later
"""Build the right-hand LCD typing scene from avatar_src.png.

Renders a 135x240 scene (the avatar sat at a desk typing on a split keyboard),
crops every animated region into an opaque "patch" image, writes
scene_layout.h with the patch positions, and converts each image to QGF with
`qmk painter-convert-graphics`.

Drawing a patch both shows a state and restores the background, so the
firmware never needs transparency or partial redraws.

Run with a Python that has Pillow (the qmk CLI's own interpreter does):
    python gen_scene.py [preview_dir]
"""
import colorsys
import subprocess
import sys
from pathlib import Path

from PIL import Image, ImageDraw

HERE = Path(__file__).resolve().parent

W, H = 135, 240
SS = 4  # supersampling factor; everything is drawn at SS x and scaled down
AVATAR = 135  # the 200x200 avatar is scaled to AVATAR x AVATAR at the top
SRC = 200

BG = (18, 21, 38)
SKIN = (253, 202, 175)
SKIN_SHADE = (205, 140, 112)
SUIT = (70, 78, 67)
SUIT_DARK = (40, 45, 38)
CUFF = (240, 244, 246)
DESK = (104, 68, 44)
DESK_EDGE = (150, 104, 68)
DESK_FRONT = (62, 40, 26)
CASE = (36, 38, 46)
CASE_EDGE = (70, 74, 88)
KEYCAP = (196, 200, 212)
KEYCAP_DOWN = (110, 114, 132)
EYELID = (40, 20, 10)
SWEAT = (110, 196, 255)
SWEAT_HI = (230, 246, 255)
ZZZ = (225, 232, 255)

DESK_Y = 150
FRONT_Y = 216  # desk front panel; WPM is drawn here at runtime
KB_Y = 170
KB_LEFT_X, KB_RIGHT_X = 8, 73
KEY, PITCH, KB_COLS, KB_ROWS = 7, 8, 6, 3

# Patch rectangles in scene coordinates: (x0, y0, x1, y1), x1/y1 exclusive.
PATCHES = {
    "HAND_L": (0, 136, 67, 208),
    "HAND_R": (67, 136, 135, 208),
    "EYES": (64, 48, 118, 70),
    "SWEAT": (100, 24, 134, 46),
    "ZZZ": (0, 0, 38, 60),
}

# Pupil centres in source-avatar pixels, used to close the eyes.
PUPILS = [(112, 87), (154.5, 86)]


def s(v):
    """Scene coordinate -> supersampled canvas coordinate."""
    return round(v * SS)


def a(v):
    """Source-avatar coordinate -> supersampled canvas coordinate."""
    return round(v * AVATAR / SRC * SS)


def avatar_layer(eyes_closed):
    src = Image.open(HERE / "avatar_src.png").convert("RGB")
    big = src.resize((AVATAR * SS, AVATAR * SS), Image.LANCZOS)
    if eyes_closed:
        d = ImageDraw.Draw(big)
        for px, py in PUPILS:
            r = a(6.5)
            d.ellipse((a(px) - r, a(py) - r, a(px) + r, a(py) + r), fill=SKIN)
            w = a(7.5)
            d.arc((a(px) - w, a(py) - w * 0.9, a(px) + w, a(py) + w * 0.5), 20, 160, fill=EYELID, width=a(2.4))
    return big


def draw_keyboard(d, pressed):
    for side, x0 in (("L", KB_LEFT_X), ("R", KB_RIGHT_X)):
        x1 = x0 + KB_COLS * PITCH + 5
        y1 = KB_Y + KB_ROWS * PITCH + 5
        d.rounded_rectangle((s(x0), s(KB_Y), s(x1), s(y1)), radius=s(3), fill=CASE, outline=CASE_EDGE, width=s(1))
        for r in range(KB_ROWS):
            for c in range(KB_COLS):
                kx = x0 + 3 + c * PITCH
                ky = KB_Y + 3 + r * PITCH
                down = (side, c, r) in pressed
                d.rounded_rectangle((s(kx), s(ky), s(kx + KEY), s(ky + KEY)), radius=s(1.5), fill=KEYCAP_DOWN if down else KEYCAP)


def draw_arm(d, shoulder, wrist, mirror):
    def m(p):
        return (W - p[0], p[1]) if mirror else p

    sx, sy = m(shoulder)
    wx, wy = m(wrist)
    dx, dy = wx - sx, wy - sy
    n = (dx * dx + dy * dy) ** 0.5
    ux, uy = dx / n, dy / n

    pts = [(s(sx), s(sy)), (s(wx), s(wy))]
    d.line(pts, fill=SUIT_DARK, width=s(17))
    d.line(pts, fill=SUIT, width=s(14))
    cuff = [(s(wx - ux * 3.5), s(wy - uy * 3.5)), (s(wx + ux * 0.5), s(wy + uy * 0.5))]
    d.line(cuff, fill=CUFF, width=s(13))

    # Hand: an oval past the wrist with a few finger creases.
    hx, hy = wx + ux * 7, wy + uy * 7
    d.ellipse((s(hx - 9), s(hy - 6.5), s(hx + 9), s(hy + 6.5)), fill=SKIN, outline=SKIN_SHADE, width=s(1))
    for off in (-4, 0, 4):
        d.line([(s(hx + off), s(hy + 2)), (s(hx + off), s(hy + 6))], fill=SKIN_SHADE, width=s(1))


# Arm poses: (shoulder, wrist) for the left arm; the right arm is mirrored.
ARM_UP = ((24, 136), (32, 162))
ARM_DOWN = ((24, 136), (35, 174))
# Keys under each hand when it presses (side, col, row).
PRESS_L = {("L", 3, 1), ("L", 4, 1)}
PRESS_R = {("R", 1, 1), ("R", 2, 1)}


def draw_sweat(d):
    for cx, cy, size in ((161, 56, 1.0), (183, 42, 0.6)):
        r = a(4.5 * size)
        x, y = a(cx), a(cy)
        d.polygon([(x, y - r * 2.4), (x - r * 0.95, y - r * 0.3), (x + r * 0.95, y - r * 0.3)], fill=SWEAT)
        d.ellipse((x - r, y - r, x + r, y + r), fill=SWEAT)
        h = r * 0.35
        d.ellipse((x - r * 0.5 - h, y - r * 0.3 - h, x - r * 0.5 + h, y - r * 0.3 + h), fill=SWEAT_HI)


def draw_z(d, cx, cy, size):
    h = size / 2
    pts = [(s(cx - h), s(cy - h)), (s(cx + h), s(cy - h)), (s(cx - h), s(cy + h)), (s(cx + h), s(cy + h))]
    d.line(pts, fill=ZZZ, width=s(1.6), joint="curve")


def draw_zzz(d, frame):
    start, end = (26, 50), (9, 9)
    for i in range(3):
        t = ((i + frame / 3) / 3) % 1.0
        cx = start[0] + (end[0] - start[0]) * t
        cy = start[1] + (end[1] - start[1]) * t
        draw_z(d, cx, cy, 5 + 8 * t)


def render(left_down=False, right_down=False, eyes_closed=False, sweat=False, zzz=None):
    img = Image.new("RGB", (W * SS, H * SS), BG)
    img.paste(avatar_layer(eyes_closed), (0, 0))

    # Extend the torso down to the desk by repeating the avatar's bottom row.
    row = img.crop((0, AVATAR * SS - 1, W * SS, AVATAR * SS))
    for y in range(AVATAR * SS, DESK_Y * SS):
        img.paste(row, (0, y))

    d = ImageDraw.Draw(img)
    if sweat:
        draw_sweat(d)
    if zzz is not None:
        draw_zzz(d, zzz)

    d.rectangle((0, s(DESK_Y), s(W), s(FRONT_Y)), fill=DESK)
    d.rectangle((0, s(DESK_Y), s(W), s(DESK_Y + 2)), fill=DESK_EDGE)
    d.rectangle((0, s(FRONT_Y), s(W), s(H)), fill=DESK_FRONT)

    pressed = (PRESS_L if left_down else set()) | (PRESS_R if right_down else set())
    draw_keyboard(d, pressed)
    draw_arm(d, *(ARM_DOWN if left_down else ARM_UP), mirror=False)
    draw_arm(d, *(ARM_DOWN if right_down else ARM_UP), mirror=True)

    return img.resize((W, H), Image.LANCZOS)


def crop(img, name):
    return img.crop(PATCHES[name])


def check_patches():
    rects = list(PATCHES.items())
    for i, (na, ra) in enumerate(rects):
        for nb, rb in rects[i + 1 :]:
            if ra[0] < rb[2] and rb[0] < ra[2] and ra[1] < rb[3] and rb[1] < ra[3]:
                sys.exit(f"patches {na} and {nb} overlap")


def qp_hsv(rgb):
    h, sat, v = colorsys.rgb_to_hsv(*(c / 255 for c in rgb))
    return round(h * 255), round(sat * 255), round(v * 255)


def write_layout():
    lines = [
        "// Generated by gen_scene.py - do not edit.",
        "#pragma once",
        "",
    ]
    for name, (x0, y0, x1, y1) in PATCHES.items():
        lines.append(f"#define SCENE_{name}_X {x0}")
        lines.append(f"#define SCENE_{name}_Y {y0}")
    fh, fs, fv = qp_hsv(DESK_FRONT)
    lines += [
        f"#define SCENE_FRONT_Y {FRONT_Y}",
        f"#define SCENE_FRONT_HSV {fh}, {fs}, {fv}",
        "",
    ]
    (HERE / "scene_layout.h").write_text("\n".join(lines))


def main():
    check_patches()

    base = render()
    images = {
        "scene_base": base,
        "hand_l_up": crop(base, "HAND_L"),
        "hand_l_down": crop(render(left_down=True), "HAND_L"),
        "hand_r_up": crop(base, "HAND_R"),
        "hand_r_down": crop(render(right_down=True), "HAND_R"),
        "eyes_open": crop(base, "EYES"),
        "eyes_closed": crop(render(eyes_closed=True), "EYES"),
        "sweat_off": crop(base, "SWEAT"),
        "sweat_on": crop(render(sweat=True), "SWEAT"),
        "zzz_off": crop(base, "ZZZ"),
    }
    for f in range(3):
        images[f"zzz_{f}"] = crop(render(zzz=f), "ZZZ")

    for name, img in images.items():
        path = HERE / f"{name}.png"
        img.save(path)
        subprocess.run(["qmk", "painter-convert-graphics", "-f", "pal256", "-i", str(path), "-o", str(HERE)], check=True)
    write_layout()

    if len(sys.argv) > 1:
        out = Path(sys.argv[1])
        poses = [
            render(),
            render(left_down=True),
            render(right_down=True, sweat=True),
            render(eyes_closed=True, zzz=0),
        ]
        sheet = Image.new("RGB", (W * len(poses) + 8 * (len(poses) - 1), H), (255, 255, 255))
        for i, p in enumerate(poses):
            sheet.paste(p, (i * (W + 8), 0))
        sheet.resize((sheet.width * 2, sheet.height * 2), Image.NEAREST).save(out / "scene_preview.png")


if __name__ == "__main__":
    main()
