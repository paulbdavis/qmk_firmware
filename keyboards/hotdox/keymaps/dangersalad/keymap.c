#include QMK_KEYBOARD_H
#include "version.h"

#define _BASE 0 // default layer
#define _LOWER = 1
#define _RAISE = 2

enum custom_keycodes {
    START_HERE = SAFE_RANGE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |   `    |   1  |   2  |   3  |   4  |   5  | LEFT |           | RIGHT|   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Esc    |   Q  |   D  |   R  |   W  |   B  |  L1  |           |  L1  |   J  |   F  |   U  |   P  |   ;  |  Bksp  |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Tab    |   A  |   S  |   H  |   T  |   G  |------|           |------|   Y  |   N  |   E  |   O  |   I  |   '    |
 * |--------+------+------+------+------+------|  C-t |           | C-t  |------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   M  |   C  |   V  |      |           |      |   K  |   L  |   ,  |   .  |   /  | RS/Ent |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |  L1  |      |CtlAlt| Left | Right|                                       |  Up  | Down |   [  |   ]  |  L1  |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,---------------.
 *                                        |      |      |       |      |        |
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |      |       |      |        |      |
 *                                 | Space|LCtrl |------|       |------| LAlt   |Space |
 *                                 |      |      |Super |       |Super |        |      |
 *                                 `--------------------'       `----------------------'
 */
    [_BASE] = LAYOUT_ergodox_pretty(  // layer 0 : default (workman)
        
        XXXXXXX,     XXXXXXX, XXXXXXX,       XXXXXXX,   XXXXXXX,   XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_ESC,      KC_Q,    KC_D,          KC_R,      KC_W,      KC_B,    XXXXXXX, /**/ XXXXXXX, KC_J,    KC_F,      KC_U,    KC_P,    KC_SCLN, KC_BSPC,
        KC_TAB,      KC_A,    KC_S,          KC_H,      KC_T,      KC_G,             /**/          KC_Y,    KC_N,      KC_E,    KC_O,    KC_I,    KC_QUOT,
        KC_LSFT,     KC_Z,    KC_X,          KC_M,      KC_C,      KC_V,    XXXXXXX, /**/ XXXXXXX, KC_K,    KC_L,      KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
        TD(NUM_ADJ), EMACS,   LALT(KC_LCTL), TD(SUPER), TD(LOWER),                   /**/                   TD(RAISE), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
        
        
        ,                                                          XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX \
        ,                                                                   XXXXXXX, /**/ XXXXXXX \
        ,                                          LCTL_T(KC_SPC), XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX, LALT_T(KC_SPC)
        
        ),
    [_LOWER] = LAYOUT_ergodox_pretty(  // layer 1 
        
        _______,     _______, _______,       _______,   _______,   _______, _______, /**/ _______, _______, _______,   _______, _______, _______, _______,
        KC_TILD,     KC_EXLM, KC_AT,         KC_HASH,   KC_DLR,    KC_PERC, _______, /**/ _______, KC_CIRC, KC_AMPR,   KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_F1,       KC_F2,   KC_F3,         KC_F4,     KC_F5,     KC_F6,            /**/          KC_COLN, KC_UNDS,   KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        KC_F7,       KC_F8,   KC_F9,         KC_F10,    KC_F11,    KC_F12,  _______, /**/ _______, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______,     _______, _______,       _______,   _______,                     /**/                   _______,   KC_HOME, KC_PGDN, KC_PGUP, KC_END, \
        
        
        ,                                                          _______, _______, /**/ _______, _______ \
        ,                                                                   _______, /**/ _______ \
        ,                                                 _______, _______, _______, /**/ _______, _______, _______
        
        ),
    [_RAISE] = LAYOUT_ergodox_pretty(  // layer 2 
        
        _______,     _______, _______,       _______,   _______,   _______, _______, /**/ _______, _______, _______,   _______, _______, _______, _______,
        KC_GRV,      KC_1,    KC_2,          KC_3,      KC_4,      KC_5,    _______, /**/ _______, KC_6,    KC_7,      KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_F1,       KC_F2,   KC_F3,         KC_F4,     KC_F5,     KC_F6,            /**/          KC_SCLN, KC_MINS,   KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_F7,       KC_F8,   KC_F9,         KC_F10,    KC_F11,    KC_F12,  _______, /**/ _______, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______,     _______, _______,       _______,   _______,                     /**/                   _______,   _______, _______, _______, _______, \
        
        
        ,                                                          _______, _______, /**/ _______, _______ \
        ,                                                                   _______, /**/ _______ \
        ,                                                 _______, _______, _______, /**/ _______, _______, _______
        
        ),
/* Keymap 1: Symbol Layer
 *
 * ,---------------------------------------------------.           ,--------------------------------------------------.
 * |  Reset  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
 * |---------+------+------+------+------+------+------|           |------+------+------+------+------+------+--------|
 * |  NumLk  |   !  |   @  |   {  |   }  |   |  |      |           |      |   _  |   7  |   8  |   9  |   *  |   F12  |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |         |   #  |   $  |   (  |   )  |   &  |------|           |------|   -  |   4  |   5  |   6  |   +  |        |
 * |---------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | Insert  |   %  |   ^  |   [  |   ]  |   *  |      |           |      |   &  |   1  |   2  |   3  |   \  |        |
 * `---------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 * | EPP_RST |      |      |      |      |                                        |   0  |   0  |   .  |   =  |        |
 * `------------------------------------'                                        `------------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
    [SYMB] = LAYOUT_ergodox_pretty(
        
        RESET,     KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   _______, /**/ _______, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        KC_NLCK,   KC_EXLM, KC_AT,   KC_LCBR, KC_RCBR, KC_PIPE, _______, /**/ _______, KC_UNDS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PAST, KC_F12,
        _______,   KC_HASH, KC_DLR,  KC_LPRN, KC_RPRN, KC_AMPR,          /**/          KC_PMNS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, _______,
        KC_INSERT, KC_PERC, KC_CIRC, KC_LBRC, KC_RBRC, KC_ASTR, _______, /**/ _______, KC_AMPR, KC_KP_1, KC_KP_2, KC_KP_3, KC_PSLS, _______,
        EEP_RST,   _______, _______, _______, _______,                   /**/                   KC_KP_0, KC_KP_0, KC_PDOT, KC_EQL,  _______\
    
        
        ,                                     _______, _______,          /**/          _______, _______\
        ,                                     _______,                   /**/                   _______\
        ,                                     _______, _______, _______, /**/ _______, _______, _______
        
        ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};
