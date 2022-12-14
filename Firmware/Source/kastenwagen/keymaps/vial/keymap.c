/* Copyright 2021 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H

#define L2_SPC      LT(2,KC_SPC)
#define L3_SPC      LT(3,KC_SPC)
#define L3_PENT     LT(3,KC_PENT)
#define RWINALT     RALT_T(KC_RGUI)
#define ISO_LT      KC_NUBS
#define ISO_GT      LSFT(KC_NUBS)

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =  { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] =  { ENCODER_CCW_CW(RGB_HUD, RGB_HUI)},
    [2] =  { ENCODER_CCW_CW(RGB_VAD, RGB_VAI)  },
    [3] = { ENCODER_CCW_CW(RGB_RMOD, RGB_MOD) },
};
#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT_1840(

    KC_ESC ,KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,KC_LBRC,KC_BSPC      , KC_P7  ,KC_P8  ,KC_P9  ,KC_PMNS,
    KC_TAB   ,KC_A   ,KC_S   ,KC_D   ,KC_F   ,KC_G   ,KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_SCLN,KC_QUOT,KC_ENT     , KC_P4  ,KC_P5  ,KC_P6  ,KC_PPLS,
    KC_LSPO      ,KC_Z   ,KC_X   ,KC_C   ,KC_V   ,KC_B   ,KC_N   ,KC_M   ,KC_COMM,KC_DOT ,KC_SLSH,KC_RSPC ,KC_UP , KC_P1  ,KC_P2  ,KC_P3  ,KC_PAST,
    KC_LCTL  ,KC_LALT  ,MO(2)  ,L2_SPC               ,L3_SPC           ,MO(3)  ,RWINALT  ,MO(1)   ,KC_LEFT,KC_DOWN,KC_RGHT,KC_P0  ,KC_PDOT,L3_PENT  
    ),
[1] = LAYOUT_1840(
    RESET  ,KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,KC_RBRC,KC_DEL       , KC_HOME,XXXXXXX,KC_PGUP,XXXXXXX,
    KC_CAPS  ,KC_F11 ,KC_F12 ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX    , XXXXXXX,XXXXXXX,XXXXXXX,KC_PAST,
    _______      ,XXXXXXX,XXXXXXX,KC_PSCR,KC_SLCK,KC_PAUS,KC_INS ,KC_APP ,KC_LGUI,KC_RGUI,XXXXXXX,_______ ,KC_PGUP,KC_END ,XXXXXXX,KC_PGDN,KC_PSLS,
    KC_RCTL  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,KC_HOME,KC_PGDN,KC_END ,KC_INS ,KC_DEL ,KC_EQL   
    ),
[2] = LAYOUT_1840(
    KC_GRV ,KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,KC_MINS,KC_EQL       , XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    KC_TILD  ,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_UNDS,KC_LBRC,KC_RBRC,KC_BSLS    , XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    _______      ,ISO_LT ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______ ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    _______  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX  
    ),
[3] = LAYOUT_1840(
    KC_TILD,KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_UNDS,KC_PLUS      , KC_NLCK,KC_PSLS,KC_PAST,XXXXXXX,
    _______  ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_LCBR,KC_RCBR,KC_PIPE    , KC_PSCR,KC_SLCK,KC_PAUS,XXXXXXX,
    _______      ,ISO_GT ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______ ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
    _______  ,_______  ,_______,XXXXXXX              ,XXXXXXX          ,_______,_______  ,_______ ,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,_______  
    )
};

void matrix_scan_user(void) {
    
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1250) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}



