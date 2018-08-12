#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"
#include "split_flags.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
// Use an enum instead of #defines so that it's not necessary to manually assign numbers.
enum layers {
  _QWERTY,
  _SDV1,
  _SDV2,
  _LOWER,
  _RAISE,
  _FUNCTION,
  _ADJUST
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

// macOS screenshot shortcuts
#define C_SS LGUI(LSFT(KC_3))
#define C_SSA LGUI(LSFT(KC_4))
#define C_SSC LGUI(LCTL(LSFT(KC_3)))
#define C_SSAC LGUI(LCTL(LSFT(KC_4)))

// Mod Tap
#define ENT_SFT MT(MOD_LSFT, KC_ENT)

// Layer changes
#define SDV_T TG(_SDV1)
#define SDV_M MO(_SDV2)

// We need to use this LAYOUT() macro from lets_split_eh/eh/eh.h because it needs
// to be split into 8 rows of 6 (all the left hand rows followed by right hand rows).
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc/`|   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Func | Ctrl | Alt  | Cmd  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 *
 * Esc is "Grave Escape", where it's usually Esc, except when:
 *   GUI is pressed, so that it's Cmd-` (macOS next window)
 *   Shift is pressed, so that it's Shift-`, aka ~
 *   Typically this means that it's impossible to press Cmd-Opt-Esc as this sends Cmd-Opt-`
 *     but see config.h for the workaround.
 */
[_QWERTY] = LAYOUT( \
  KC_TAB,        KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_GESC,       KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, ENT_SFT, \
  MO(_FUNCTION), KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  ~   |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Mute |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Bksp | Bksp |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT( \
  KC_TILD, KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,  \
  KC_DEL,  KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_MUTE, _______, _______, \
  _______, _______,  _______, _______, _______, KC_BSPC, KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   4  |   5  |   6  |   +  |  F5  |  F6  |   -  |   =  |   [  |   ]  |   \  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |Enter |   7  |   8  |   9  |   -  |  F11 |  F12 |      | Home | PgDn | PgUp | End  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   ,  |   0  |  .   |      | Bksp | Bksp |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT( \
  KC_GRV,  KC_1,    KC_2,  KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL,  \
  _______, KC_4,    KC_5,  KC_6,   KC_PLUS, KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  KC_ENT,  KC_7,    KC_8,  KC_9,   KC_MINS, KC_F11,  KC_F12,  _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  \
  _______, KC_COMM, KC_0,  KC_DOT, _______, KC_BSPC, KC_BSPC, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      | SDV_T|RGBVAI|RGBSAI|RGBHUI| Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |    SS|   SSA| SS Cp|SSA Cp|      |      |      |RGBVAD|RGBSAD|RGBHUD|RGBTOG|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |BLSTEP|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | RESET|
 * `-----------------------------------------------------------------------------------'
 *
 * Retain the bottom right reset for compatibility with default lets_split_eh keymap.
 */
[_ADJUST] = LAYOUT( \
  _______, RESET,   _______, _______, _______, _______, _______,   SDV_T, RGB_VAI, RGB_SAI, RGB_HUI, KC_DEL, \
  _______, C_SS,    C_SSA,   C_SSC,   C_SSAC,  _______, _______, _______,  RGB_VAD, RGB_SAD, RGB_HUD, RGB_TOG, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, BL_STEP, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET    \
),

/* Function
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |  Up  |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      | Left | Down |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Caps |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT( \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_UP,   _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
  KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
),

/* Stardew Valley 1
 * ,-----------------------------------------------------------------------------------.
 * |      |      |   W  |   E  |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   A  |   S  |   D  |   F  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |   X  |   C  |   M  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Items|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 * Most of the keys are actually the same as Qwerty, except M, but let's just specify to be clear.
 */
[_SDV1] = LAYOUT( \
  _______, _______,    KC_W,    KC_E, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______,    KC_A,    KC_S,    KC_D,    KC_F, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______,    KC_X,    KC_C,    KC_M, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,   SDV_M, _______, _______, _______, _______, _______, _______  \
),

/* Stardew Valley 2
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |   5  |   6  |   7  |   8  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   9  |   0  |   -  |   =  |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      | Items|      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 *
 * The Toggle button must remain transparent so that releasing it will be detected by the momentary
 * layer switch keycode on the layer below.
 */
[_SDV2] = LAYOUT( \
  _______,    KC_1,    KC_2,    KC_3,    KC_4, _______, _______, _______, _______, _______, _______, _______, \
  _______,    KC_5,    KC_6,    KC_7,    KC_8, _______, _______, _______, _______, _______, _______, _______, \
  _______,    KC_9,    KC_0, KC_MINS,  KC_EQL, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  \
)

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}

// This is run every time layers are changed.
uint32_t layer_state_set_user(uint32_t state) {
  // get existing value to avoid changing the EEPROM-configured brightness
  // hue and saturation need to be controlled here to fully control colour
  uint8_t cur_val = rgblight_get_val();

  // state is bitmask of active layers, of the max 32 layers
  switch (biton32(state)) {
    case _SDV1:
    case _SDV2:
      rgblight_sethsv_noeeprom(120, 255, cur_val);
      RGB_DIRTY = true;
      break;
    default:
      rgblight_sethsv_noeeprom(240, 255, cur_val);
      RGB_DIRTY = true;
      break;
  }
  return state;
}
