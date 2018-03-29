#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _COLEMAK 1
#define _NUMPAD 5
#define _LOWER 10
#define _RAISE 11
#define _EMACS 12
#define _MOUSE 13
#define _ADJUST 30

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  LOWER,
  RAISE,
  ADJUST,
  EMACS_WIN_1,
  EMACS_WIN_2,
  EMACS_WIN_3,
  EMACS_WIN_4,
  EMACS_WIN_0,
  EMACS_PROJ_SWITCH,
  EMACS_PROJ_FILE,
  EMACS_PROJ_SEARCH,
  EMACS_PROJ_COMPILE,
  EMACS_PROJ_SHELL,
  EMACS_PROJ_GIT,
  EMACS_FLYC_CHECK,
  EMACS_FLYC_NEXT,
  EMACS_FLYC_PREV,
  EMACS_FLYC_LIST,
};

enum  {
  SUPER_LAYER_CHANGE = 0,
  MOD_BUILDER,
  NUMPAD_ADJUST
};

void dance_super_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_LGUI);
  } else {
    layer_on(_RAISE);
    register_code (KC_LGUI);
  }
}

void dance_super_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    unregister_code (KC_LGUI);
  } else {
    layer_off(_RAISE);
    unregister_code (KC_LGUI);
  }
}

void dance_mod_builder_finished (qk_tap_dance_state_t *state, void *user_data) {
  // 5 taps goes to adjustment layer
  if (state->count == 5) {
    layer_on(_ADJUST);
    return;
  }
  register_code (KC_LCTRL);
  if (state->count >= 2) {
    register_code (KC_LALT);
  }
  if (state->count >= 3) {
    register_code (KC_LGUI);
  }
  if (state->count >= 4) {
    register_code (KC_LSHIFT);
  }
}

void dance_mod_builder_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 5) {
    layer_off(_ADJUST);
    return;
  }
  unregister_code (KC_LCTRL);
  if (state->count >= 2) {
    unregister_code (KC_LALT);
  }
  if (state->count >= 3) {
    unregister_code (KC_LGUI);
  }
  if (state->count >= 4) {
    unregister_code (KC_LSHIFT);
  }
}

void dance_numpad_adjust (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_LOWER);
    layer_off(_RAISE);
    layer_on(_NUMPAD);
    return;
  }
  if (state->count == 2) {
    layer_on(_ADJUST);
    return;
  }
}

void dance_numpad_adjust_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_NUMPAD);
    return;
  }
  if (state->count == 2) {
    layer_off(_ADJUST);
    return;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [SUPER_LAYER_CHANGE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_super_finished, dance_super_reset),
  [MOD_BUILDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mod_builder_finished, dance_mod_builder_reset),
  [NUMPAD_ADJUST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_numpad_adjust, dance_numpad_adjust_reset),
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Hyper| Meh  |  GUI | Alt  |Lower | Ctrl |  |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_QWERTY] = KEYMAP( \
  KC_ESC            , KC_Q       , KC_W    , KC_E                   , KC_R  , KC_T           , KC_Y           , KC_U  , KC_I    , KC_O    , KC_P    , KC_BSPC         , \
  LCTL_T(KC_TAB)    , KC_A       , KC_S    , KC_D                   , KC_F  , KC_G           , KC_H           , KC_J  , KC_K    , KC_L    , KC_SCLN , RCTL_T(KC_QUOT) , \
  KC_LSFT           , KC_Z       , KC_X    , KC_C                   , KC_V  , KC_B           , KC_N           , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT)  , \
  TD(NUMPAD_ADJUST) , MO(_MOUSE) , KC_LALT , TD(SUPER_LAYER_CHANGE) , LOWER , LCTL_T(KC_SPC) , LALT_T(KC_SPC) , RAISE , KC_LEFT , KC_DOWN , KC_UP   , RCTL_T(KC_RGHT) \
),

/* Colemak
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Ctrl |   A  |   R  |   S  |   T  |   D  |  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Hyper| Meh  | GUI  | Alt  |Lower | Ctrl |  |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_COLEMAK] = KEYMAP( \
  KC_ESC            , KC_Q       , KC_W    , KC_F                   , KC_P  , KC_G           , KC_J           , KC_L  , KC_U    , KC_Y    , KC_SCLN , KC_BSPC         , \
  LCTL_T(KC_TAB)    , KC_A       , KC_R    , KC_S                   , KC_T  , KC_D           , KC_H           , KC_N  , KC_E    , KC_I    , KC_O    , RCTL_T(KC_QUOT) , \
  KC_LSFT           , KC_Z       , KC_X    , KC_C                   , KC_V  , KC_B           , KC_K           , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT)  , \
  TD(NUMPAD_ADJUST) , MO(_MOUSE) , KC_LALT , TD(SUPER_LAYER_CHANGE) , LOWER , LCTL_T(KC_SPC) , LALT_T(KC_SPC) , RAISE , KC_LEFT , KC_DOWN , KC_UP   , RCTL_T(KC_RGHT) \
),

/* Lower
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |   :  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |      |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      | Next | Vol- | Vol+ | Mute |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_LOWER] = KEYMAP( \
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR    , KC_ASTR    , KC_LPRN , KC_RPRN , KC_DEL  , \
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_COLN , KC_UNDS    , KC_PLUS    , KC_LCBR , KC_RCBR , KC_PIPE , \
  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , S(KC_NUHS) , S(KC_NUBS) , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______    , KC_MNXT    , KC_VOLD , KC_VOLU , KC_MUTE \
), 

/* Raise
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |   ;  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |      |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      | Next | Vol- | Vol+ | Mute |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_RAISE] = KEYMAP( \
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL  , \
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_SCLN , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS , \
  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_NUHS , KC_NUBS , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MNXT , KC_VOLD , KC_VOLU , KC_MUTE \
),

/* Adjust (mod builder 5 times)
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      | Reset|      |      |      |      |  |      |      |      |      |      |  Del |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|  |AGswap|Qwerty|Colemk|      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |      |      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_ADJUST] =  KEYMAP( \
  _______ , RESET   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_DEL  , \
  _______ , _______ , _______ , AU_ON   , AU_OFF  , AG_NORM , AG_SWAP , QWERTY  , COLEMAK , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
),

/* Emacs (Lower + Raise)
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |      |      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_EMACS] =  KEYMAP( \
  RESET          , EMACS_WIN_1       , EMACS_WIN_2     , EMACS_WIN_3       , EMACS_WIN_4        , XXXXXXX          , XXXXXXX          , XXXXXXX         , XXXXXXX         , XXXXXXX         , EMACS_WIN_0 , XXXXXXX , \
  EMACS_PROJ_GIT , EMACS_PROJ_SWITCH , EMACS_PROJ_FILE , EMACS_PROJ_SEARCH , EMACS_PROJ_COMPILE , EMACS_PROJ_SHELL , EMACS_FLYC_CHECK , EMACS_FLYC_NEXT , EMACS_FLYC_PREV , EMACS_FLYC_LIST , XXXXXXX     , XXXXXXX , \
  XXXXXXX        , XXXXXXX           , XXXXXXX         , XXXXXXX           , XXXXXXX            , XXXXXXX          , XXXXXXX          , XXXXXXX         , XXXXXXX         , XXXXXXX         , XXXXXXX     , XXXXXXX , \
  _______        , _______           , XXXXXXX         , XXXXXXX           , _______            , XXXXXXX          , XXXXXXX          , _______         , XXXXXXX         , XXXXXXX         , XXXXXXX     , XXXXXXX \
 )               ,

/* Number Pad
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |  7   |  8   |  9   |      |      |NmLck |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |  4   |  5   |  6   |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |  1   |  2   |  3   |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |      |  0   |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_NUMPAD] =  KEYMAP( \
  RESET   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_PSLS , XXXXXXX , KC_NLCK , \
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_PAST , XXXXXXX , XXXXXXX , \
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_PMNS , KC_PENT , KC_PENT , \
  _______ , _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_KP_0 , KC_KP_0 , KC_PDOT , KC_PPLS , KC_PENT , KC_PENT \
 ),

/* Number Pad
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |  7   |  8   |  9   |      |      |NmLck |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |  4   |  5   |  6   |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |  1   |  2   |  3   |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |      |  0   |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_MOUSE] =  KEYMAP( \
  RESET   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN2 , KC_BTN3 , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
 )


};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_colemak);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _EMACS);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _EMACS);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _EMACS);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _EMACS);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case EMACS_WIN_1:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("x")"1");
      }
      return true;
      break;
    case EMACS_WIN_2:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("x")"2");
      }
      return true;
      break;
    case EMACS_WIN_3:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("x")"3");
      }
      return true;
      break;
    case EMACS_WIN_4:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("x")"4");
      }
      return true;
      break;
    case EMACS_WIN_0:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("x")"0");
      }
      return true;
      break;
    case EMACS_PROJ_SWITCH:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"pp");
      }
      return true;
      break;
    case EMACS_PROJ_SHELL:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"pxe");
      }
      return true;
      break;
    case EMACS_PROJ_FILE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"pf");
      }
      return true;
      break;
    case EMACS_PROJ_SEARCH:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"pss");
      }
      return true;
      break;
    case EMACS_PROJ_COMPILE:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"pc");
      }
      return true;
      break;
    case EMACS_PROJ_GIT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"pv");
      }
      return true;
      break;
    case EMACS_FLYC_CHECK:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"!c");
      }
      return true;
      break;
    case EMACS_FLYC_NEXT:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"!n");
      }
      return true;
      break;
    case EMACS_FLYC_PREV:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"!p");
      }
      return true;
      break;
    case EMACS_FLYC_LIST:
      if (record->event.pressed) {
        SEND_STRING(SS_LCTRL("c")"!l");
      }
      return true;
      break;
  }
  return true;
}
