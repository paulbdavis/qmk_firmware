#include QMK_KEYBOARD_H
#include "version.h"
#include "dangersalad.h"

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
    [_WORKMAN] = LAYOUT_ergodox_pretty(  // layer 0 : default (workman)
        
        XXXXXXX,        XXXXXXX, XXXXXXX,       XXXXXXX,      XXXXXXX,     XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_ESC,         KC_Q,    KC_D,          KC_R,         KC_W,        KC_B,    XXXXXXX, /**/ XXXXXXX, KC_J,    KC_F,         KC_U,    KC_P,    KC_SCLN, KC_BSPC,
        KC_TAB,         KC_A,    KC_S,          KC_H,         KC_T,        KC_G,             /**/          KC_Y,    KC_N,         KC_E,    KC_O,    KC_I,    KC_QUOT,
        KC_LSFT,        KC_Z,    KC_X,          KC_M,         KC_C,        KC_V,    XXXXXXX, /**/ XXXXXXX, KC_K,    KC_L,         KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT),
        TD(TD_NUM_ADJ), EMACS,   LALT(KC_LCTL), TD(TD_SUPER), LOWER,                         /**/                   RAISE,        KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
        
        
        ,                                                                  XXXXXXX, XXXXXXX, /**/ XXXXXXX, XXXXXXX \
        ,                                                                           XXXXXXX, /**/ XXXXXXX \
        ,                                                          KC_SPC, KC_LCTL, XXXXXXX, /**/ XXXXXXX, KC_LALT, KC_SPC
        
        ),
    
    [_LOWER] = LAYOUT_ergodox_pretty(  // layer 1 
        
        _______,     _______, _______,       _______,   _______,   _______, _______, /**/ _______, _______, _______,   _______, _______, _______, _______,
        KC_TILD,     KC_EXLM, KC_AT,         KC_HASH,   KC_DLR,    KC_PERC, _______, /**/ _______, KC_CIRC, KC_AMPR,   KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
        KC_F1,       KC_F2,   KC_F3,         KC_F4,     KC_F5,     KC_F6,            /**/          KC_COLN, KC_UNDS,   KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
        KC_F7,       KC_F8,   KC_F9,         KC_F10,    KC_F11,    KC_F12,  _______, /**/ _______, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______,     _______, _______,       _______,   _______,                     /**/                   _______,   KC_HOME, KC_PGDN, KC_PGUP, KC_END \
        
        
        ,                                                          _______, _______, /**/ _______, _______ \
        ,                                                                   _______, /**/ _______ \
        ,                                                 _______, _______, _______, /**/ _______, _______, _______
        
        ),
    
    [_RAISE] = LAYOUT_ergodox_pretty(  // layer 2 
        
        _______,     _______, _______,       _______,   _______,   _______, _______, /**/ _______, _______, _______,   _______, _______, _______, _______,
        KC_GRV,      KC_1,    KC_2,          KC_3,      KC_4,      KC_5,    _______, /**/ _______, KC_6,    KC_7,      KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_F1,       KC_F2,   KC_F3,         KC_F4,     KC_F5,     KC_F6,            /**/          KC_SCLN, KC_MINS,   KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_F7,       KC_F8,   KC_F9,         KC_F10,    KC_F11,    KC_F12,  _______, /**/ _______, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______,     _______, _______,       _______,   _______,                     /**/                   _______,   _______, _______, _______, _______ \
        
        
        ,                                                          _______, _______, /**/ _______, _______ \
        ,                                                                   _______, /**/ _______ \
        ,                                                 _______, _______, _______, /**/ _______, _______, _______
        
        ),
    [_EMACS] = LAYOUT_ergodox_pretty(  // layer 2 
        
        _______,    _______, _______,       _______,   _______,   _______, _______, /**/ _______, _______, _______,   _______, _______, _______, _______,
        RESET,      E_WIN_1, E_WIN_2, E_WIN_3, E_WIN_4, XXXXXXX, _______, /**/ _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, E_WIN_0, XXXXXXX,
        E_PROJ_GIT, E_PROJ_SWITCH, E_PROJ_FILE, E_PROJ_SEARCH, E_PROJ_COMPILE, E_PROJ_SHELL, /**/          E_FLYC_CHECK, E_FLYC_NEXT,   E_FLYC_PREV,  E_FLYC_LIST, XXXXXXX, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /**/ _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______,                   /**/                   _______, _______, _______, _______, _______ \
        
        
        ,                                                          _______, _______, /**/ _______, _______ \
        ,                                                                   _______, /**/ _______ \
        ,                                                 _______, _______, _______, /**/ _______, _______, _______
        
        ),
    
    [_ADJUST] = LAYOUT_ergodox_pretty(  // layer 2
        
        _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______, _______,
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /**/ _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        AG_SWAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          /**/          XXXXXXX, XXXXXXX, KC_INSERT, XXXXXXX, XXXXXXX, XXXXXXX,
        AG_NORM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /**/ _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
        _______, _______, _______, _______, _______,                   /**/                   _______, _______, _______, _______, _______ \
        
        
        ,                                            _______, _______, /**/ _______, _______ \
        ,                                                     _______, /**/ _______ \
        ,                                   _______, _______, _______, /**/ _______, _______, _______
        
        ),
    
    
    [_NUMPAD] = LAYOUT_ergodox_pretty(  // layer 2
        
        _______, _______, _______, _______, _______, _______, _______, /**/ _______, _______, _______, _______, _______, _______,   _______,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /**/ _______, KC_PSLS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS,   KC_BSPC,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          /**/          KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,   KC_NLCK,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /**/ _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT, KC_PENT,
        _______, _______, _______, _______, _______,                   /**/                   _______, _______, _______, _______,   _______ \
        
        
        ,                                            _______, _______, /**/ _______, _______ \
        ,                                                     _______, /**/ _______ \
        ,                                   _______, _______, _______, /**/ _______, _______, _______
        
        ),
    
    
    /* [_BLANK] = LAYOUT_ergodox_pretty(  // layer 2 */
        
    /*     _______, _______, _______, _______, _______, _______, _______, /\**\/ _______, _______, _______, _______, _______, _______, _______,  */
    /*     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /\**\/ _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  */
    /*     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          /\**\/          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  */
    /*     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, /\**\/ _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,  */
    /*     _______, _______, _______, _______, _______,                   /\**\/                   _______, _______, _______, _______, _______, \ */
        
        
    /*     ,                                            _______, _______, /\**\/ _______, _______ \ */
    /*     ,                                                     _______, /\**\/ _______ \ */
    /*     ,                                   _______, _______, _______, /\**\/ _______, _______, _______ */
        
    /*     ), */
};

extern keymap_config_t keymap_config;

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};


// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

};
