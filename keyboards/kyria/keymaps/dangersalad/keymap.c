#include QMK_KEYBOARD_H
#include "dangersalad.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* 
 * Base Layer: QWERTY
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |RAIS/ESC|   Q  |   W  |   E  |   R  |   T  |                              |   Y  |   U  |   I  |   O  |   P  |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |Ctrl/BS |   A  |   S  |  D   |   F  |   G  |                              |   H  |   J  |   K  |   L  | ;  : |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * | LShift |   Z  |   X  |   C  |   V  |   B  |LShift|LShift|  |LShift|LShift|   N  |   M  | ,  < | . >  | /  ? |  - _   |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        | GUI  | Del  | Enter| Space| Esc  |  | Enter| Space| Tab  | Bksp | AltGr|
 *                        |      |      | Alt  | Lower| Raise|  | Lower| Raise|      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_WORKMAN] = LAYOUT(
        KC_ESC,  KC_Q,    KC_D,    KC_R,           KC_W,    KC_B,                                      KC_J,  KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC ,
        KC_TAB,  KC_A,    KC_S,    KC_H,           KC_T,    KC_G,                                      KC_Y,  KC_N,    KC_E,    KC_O,    KC_I,    KC_QUOT    ,
        KC_LSFT, KC_Z,    KC_X,    KC_M,           KC_C,    KC_V,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_K,  KC_L,    KC_COMM, KC_DOT,  KC_SLSH, RSFT_T(KC_ENT) \
        ,                          TD(TD_NUM_ADJ), KC_LGUI, LOWER, KC_SPC,  KC_LCTL, KC_LALT, KC_SPC,  RAISE, KC_RCTL, KC_RALT
    ),
/*
 * Lower Layer: Symbols
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |  !   |  @   |  {   |  }   |  |   |                              |      |      |      |      |      |  | \   |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |  #   |  $   |  (   |  )   |  `   |                              |   +  |  -   |  /   |  *   |  %   |  ' "   |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |  %   |  ^   |  [   |  ]   |  ~   |      |      |  |      |      |   &  |  =   |  ,   |  .   |  / ? | - _    |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |  ;   |  =   |  |  =   |  ;   |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_LOWER] = LAYOUT(
      KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                       KC_COLN, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE,
      KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______ \
      ,                          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Raise Layer: Number keys, media, navigation
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        |   1  |  2   |  3   |  4   |  5   |                              |  6   |  7   |  8   |  9   |  0   |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        |      | Prev | Play | Next | VolUp|                              | Left | Down | Up   | Right|      |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      |      |      | Mute | VolDn|      |      |  |      |      | MLeft| Mdown| MUp  |MRight|      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_RAISE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                                        KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                       KC_SCLN, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______ \
        ,                          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
 * Adjust Layer: Function keys, RGB
 *
 * ,-------------------------------------------.                              ,-------------------------------------------.
 * |        | F1   |  F2  | F3   | F4   | F5   |                              | F6   | F7   |  F8  | F9   | F10  |        |
 * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
 * |        | TOG  | SAI  | HUI  | VAI  | MOD  |                              |      |      |      | F11  | F12  |        |
 * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
 * |        |      | SAD  | HUD  | VAD  | RMOD |      |      |  |      |      |      |      |      |      |      |        |
 * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        |      |      |      |      |      |  |      |      |      |      |      |
 *                        `----------------------------------'  `----------------------------------'
 */
    [_EMACS] = LAYOUT(
        RESET,          EMACS_WIN_1,       EMACS_WIN_2,     EMACS_WIN_3,       EMACS_WIN_4,        XXXXXXX,                                              XXXXXXX,          XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX, XXXXXXX,
        EMACS_PROJ_GIT, EMACS_PROJ_SWITCH, EMACS_PROJ_FILE, EMACS_PROJ_SEARCH, EMACS_PROJ_COMPILE, EMACS_PROJ_SHELL,                                     EMACS_FLYC_CHECK, EMACS_FLYC_NEXT, EMACS_FLYC_PREV, EMACS_FLYC_LIST, XXXXXXX, XXXXXXX,
        XXXXXXX,        XXXXXXX,           XXXXXXX,         XXXXXXX,           XXXXXXX,            XXXXXXX,          _______, _______, _______, _______, XXXXXXX,          XXXXXXX,         XXXXXXX,         XXXXXXX,         XXXXXXX, XXXXXXX \
        ,                                                   _______,           _______,            _______,          _______, _______, _______, _______, _______,          _______,         _______
    ),
    
    [_ADJUST] = LAYOUT(
        RESET,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        AG_SWAP, RGB_TOG, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,                                     XXXXXXX, KC_INSERT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        AG_NORM, XXXXXXX, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, _______, _______, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
        ,                          _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______
    ),
    
    [_NUMPAD] = LAYOUT(
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_PSLS, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS,   KC_BSPC,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                     KC_PAST, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS,   KC_NLCK,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, _______, _______, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_KP_DOT, KC_PENT \
        ,                          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
/*
//  * Layer template
//  *
//  * ,-------------------------------------------.                              ,-------------------------------------------.
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------|                              |------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |                              |      |      |      |      |      |        |
//  * |--------+------+------+------+------+------+-------------.  ,-------------+------+------+------+------+------+--------|
//  * |        |      |      |      |      |      |      |      |  |      |      |      |      |      |      |      |        |
//  * `----------------------+------+------+------+------+------|  |------+------+------+------+------+----------------------'
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        |      |      |      |      |      |  |      |      |      |      |      |
//  *                        `----------------------------------'  `----------------------------------'
//  */
    
    /* [_LAYERINDEX] = LAYOUT( */
    /*     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, */
    /*     _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______, */
    /*     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \ */
    /*     ,                          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ */
    /* ), */
    
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
	return OLED_ROTATION_180;
}

static void render_qmk_logo(void) {
  static const char PROGMEM qmk_logo[] = {
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0};

  oled_write_P(qmk_logo, false);
}

static void render_status(void) {
    // QMK Logo and version information
    render_qmk_logo();
    oled_write_P(PSTR("Kyria rev1.0\n\n"), false);

    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _WORKMAN:
            oled_write_P(PSTR("default\n"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("lower\n"), false);
            break;
        case _RAISE:
            oled_write_P(PSTR("raise\n"), false);
            break;
        case _EMACS:
            oled_write_P(PSTR("emacs\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("numpad\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("adjust\n"), false);
            break;
        default:
            oled_write_P(PSTR("undefined\n"), false);
    }

    // Host Keyboard LED Status
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_NUM_LOCK) ? PSTR("NUMLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK) ? PSTR("CAPLCK ") : PSTR("       "), false);
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_SCROLL_LOCK) ? PSTR("SCRLCK ") : PSTR("       "), false);
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status(); // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_qmk_logo();
    }
}
#endif

#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}
#endif
