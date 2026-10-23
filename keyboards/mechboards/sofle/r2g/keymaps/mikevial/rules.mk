ENCODER_MAP_ENABLE = yes
VIA_ENABLE = yes
VIAL_ENABLE = yes
VIALRGB_ENABLE = yes

SRC += display.c
GRAPHICS = scene_base hand_l_up hand_l_down hand_r_up hand_r_down \
           eyes_open eyes_closed sweat_off sweat_on zzz_off zzz_0 zzz_1 zzz_2
SRC += $(addprefix graphics/,$(addsuffix .qgf.c,$(GRAPHICS)))
