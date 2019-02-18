#include "dangersalad.h"

// rgblight
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

// music 
#ifdef AUDIO_ENABLE
float tone_qwerty[][2]      = SONG(COIN_SOUND);
float tone_workman[][2]     = SONG(ZELDA_TREASURE);
float tone_numpad[][2]      = SONG(AUDIO_ON_SOUND);
float tone_numpad_exit[][2] = SONG(AUDIO_OFF_SOUND);
float tone_emacs[][2]       = SONG(BEEP);
float tone_adjust[][2]      = SONG(ZELDA_PUZZLE);
#endif

__attribute__ ((weak)) void matrix_init_keymap(void) { }
__attribute__ ((weak)) void matrix_scan_keymap(void) { }
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
__attribute__ ((weak)) uint32_t layer_state_set_keymap (uint32_t state) {
    return state;
}
__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) { }

// typically the LOWER and RAISE keycodes just layer_on() and update_tri_layer(),
// which causes two layer state changes in quick succession.
// since there is some issue with updating the rgblight underglow LEDs so rapidly,
// implement a more complicated function to compute the final state and set once.
void layer_on_update_tri_layer(uint8_t layer_on, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  uint32_t mask12 = (1UL << layer1) | (1UL << layer2);
  uint32_t mask3 = 1UL << layer3;
  uint32_t new_state = layer_state | (1UL << layer_on);
  layer_state_set((new_state & mask12) == mask12 ? (new_state | mask3) : (new_state));
}

void layer_off_update_tri_layer(uint8_t layer_off, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  uint32_t mask12 = (1UL << layer1) | (1UL << layer2);
  uint32_t mask3 = 1UL << layer3;
  uint32_t new_state = layer_state & ~(1UL << layer_off);
  layer_state_set((new_state & mask12) != mask12 ? (new_state & ~mask3) : (new_state));
}

// tap dance stuff
typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //If count = 1, and it has been interrupted - it doesn't matter if it is pressed or not: Send SINGLE_TAP
    if (state->pressed==0) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  //If count = 2, and it has been interrupted - assume that user is trying to type the letter associated
  //with single tap. In example below, that means to send `xx` instead of `Escape`.
  else if (state->count == 2) {
    /* if (state->interrupted) return DOUBLE_SINGLE_TAP; */
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count >= 3) {
    if (state->pressed) return TRIPLE_HOLD;
    else return TRIPLE_TAP;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

//**************** Definitions needed for quad function to work *********************//

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap ctrl_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap alt_tap_state = {
  .is_press_action = true,
  .state = 0
};

static tap numpad_tap_state = {
  .is_press_action = true,
  .state = 0
};

void pre_numpad_disable (void) {
  // always deactivate these to prevent them getting stuck on since
  // the numpad overrides them
  layer_off(_RAISE);
  unregister_code(KC_LALT);
  unregister_code(KC_LGUI);
  alt_tap_state.is_press_action = true;
  alt_tap_state.state = 0;
}

void ctrl_finished (qk_tap_dance_state_t *state, void *user_data) {
  ctrl_tap_state.state = cur_dance(state);
  switch (ctrl_tap_state.state) {
  case SINGLE_TAP: register_code(KC_SPC); break;
  case SINGLE_HOLD: register_code(KC_LCTRL); break;
  case DOUBLE_TAP:
  case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC); break;
  case DOUBLE_HOLD:
    layer_on(_RAISE);
    register_code (KC_LGUI);
    break;
  case TRIPLE_TAP: register_code(KC_ENTER); break;
  case TRIPLE_HOLD:
    layer_on(_RAISE);
    register_code(KC_LCTRL);
    register_code (KC_LGUI);
    break;
  }
}

void ctrl_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ctrl_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: unregister_code(KC_LCTRL); break;
    case DOUBLE_TAP: unregister_code(KC_SPC); break;
    case DOUBLE_HOLD:
      layer_off(_RAISE);
      unregister_code (KC_LGUI);
      break;
    case TRIPLE_TAP: unregister_code(KC_ENTER); break;
    case TRIPLE_HOLD:
      layer_off(_RAISE);
      unregister_code(KC_LCTRL);
      unregister_code (KC_LGUI);
      break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC);
  }
  ctrl_tap_state.state = 0;
}

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
  alt_tap_state.state = cur_dance(state);
  switch (alt_tap_state.state) {
  case SINGLE_TAP: register_code(KC_SPC); break;
  case SINGLE_HOLD: register_code(KC_LALT); break;
  case DOUBLE_TAP:
  case DOUBLE_SINGLE_TAP: register_code(KC_SPC); unregister_code(KC_SPC); register_code(KC_SPC); break;
  case DOUBLE_HOLD: register_code(KC_LGUI); break;
  case TRIPLE_TAP: register_code(KC_ENTER); break;
  case TRIPLE_HOLD:
    register_code (KC_LGUI);
    break;
  }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (alt_tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_SPC); break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_TAP: unregister_code(KC_SPC); break;
    case DOUBLE_HOLD: unregister_code(KC_LGUI); break;
    case TRIPLE_TAP: unregister_code(KC_ENTER); break;
    case TRIPLE_HOLD:
      unregister_code (KC_LGUI);
      break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_SPC);
  }
  alt_tap_state.state = 0;
}

void numpad_finished (qk_tap_dance_state_t *state, void *user_data) {
  pre_numpad_disable();
  numpad_tap_state.state = cur_dance(state);
  switch (numpad_tap_state.state) {
  case SINGLE_TAP: 
  case SINGLE_HOLD:
  case DOUBLE_TAP:
    layer_on(_NUMPAD);
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_numpad);
#endif
    break;
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD:
    if (biton32(layer_state) != _NUMPAD) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_adjust);
#endif
    }
    layer_on(_ADJUST);
    break;
  }
}

void numpad_reset (qk_tap_dance_state_t *state, void *user_data) {
  pre_numpad_disable();
  switch (numpad_tap_state.state) {
  case SINGLE_TAP:
  case SINGLE_HOLD:
    layer_off(_NUMPAD);
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_numpad_exit);
#endif
    break;
  case DOUBLE_TAP: break;
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD:
    if (biton32(layer_state) == _NUMPAD) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_numpad_exit);
#endif
    }
    layer_off(_NUMPAD);
    layer_off(_ADJUST);
    break;
  }
  numpad_tap_state.state = 0;
}

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


qk_tap_dance_action_t tap_dance_actions[] = {
  [SUPER_LAYER_CHANGE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_super_finished, dance_super_reset),
  [NUMPAD_ADJUST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_finished, numpad_reset),
  [SUPER_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_finished, ctrl_reset),
  [SUPER_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
  [CTRL_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LALT|KC_LCTL),
};

// rgb light functions
#ifdef RGBLIGHT_ENABLE
// Storage variables
extern  rgblight_config_t rgblight_config;
bool    base_sta;   // Keeps track if in saveable state
bool    base_tog;   // Whether base state is active or not
int     base_hue;   // Hue value of base state
int     base_sat;   // Saturation value of base state
int     base_val;   // Brightness value of base state
uint8_t base_mod;   // Animation mode of the base state

// Save the current state of the rgb mode
void rgblight_saveBase(void) {
    base_hue = rgblight_config.hue;
    base_sat = rgblight_config.sat;
    base_val = rgblight_config.val;
    base_mod = rgblight_config.mode;
    base_tog = rgblight_config.enable;
    base_sta = false;   // If saving, that means base layer is being left
}

// Load the base state back 
void rgblight_loadBase(void) {
    // Don't do anything if not enabled
    if ( !base_sta ) {
        if ( base_tog ) {
            rgblight_enable();
            rgblight_mode( base_mod );
            rgblight_sethsv( base_hue, base_sat, base_val );
        } else {
            rgblight_disable();
        }
    }
    // Mark that base is loaded, and to be saved before leaving
    base_sta = true;
}

// Set to plain HSV color
void rgblight_colorStatic( int hu, int sa, int va ) {
    // First, it must be enabled or color change is not written
    rgblight_enable();
    rgblight_mode(1);
    rgblight_sethsv(hu,sa,va);
}

/* HSV values
 * white        (  0,   0, 255)
 * red          (  0, 255, 255)
 * coral        ( 16, 176, 255)
 * orange       ( 39, 255, 255)
 * goldenrod    ( 43, 218, 218)
 * gold         ( 51, 255, 255)
 * yellow       ( 60, 255, 255)
 * chartreuse   ( 90, 255, 255)
 * green        (120, 255, 255)
 * springgreen  (150, 255, 255)
 * turquoise    (174,  90, 112)
 * teal         (180, 255, 128)
 * cyan         (180, 255, 255)
 * azure        (186, 102, 255)
 * blue         (240, 255, 255)
 * purple       (270, 255, 255)
 * magenta      (300, 255, 255)
 * pink         (330, 128, 255)
 */

// Set RGBLIGHT state depending on layer
void rgblight_change( uint8_t this_layer ) {
    // Save state, if saving is requested
    if ( base_sta ) {
        rgblight_saveBase();
    }
    // Change RGB light
    switch ( this_layer ) {
        case _WORKMAN:
            // Load base layer
            rgblight_loadBase();
            break;
        case _RAISE:
            // Do orange for raise
            rgblight_colorStatic( 39,255,255);
            break;
        case _LOWER:
            // Do azure for lower
            rgblight_colorStatic(186,102,255);
            break;
        case _ADJUST:
            // Do white for adjust
            rgblight_colorStatic(  0,  0,255);
            break;
        case _NUMPAD:
            // Do red for numpad
            rgblight_colorStatic(  0,255,255);
            break;
        case _EMACS:
            // Do purple for emacs
            rgblight_colorStatic(270,255,255);
            break;
        default:
            // Something went wrong
            rgblight_colorStatic(120,255,255);
            break;
    }
}

#endif

// matrix init
void matrix_init_user (void) {

    // Keymap specific things, do it first thing to allow for delays etc
    matrix_init_keymap();

    // Correct unicode
#ifdef UNICODE_ENABLE
    set_unicode_input_mode(UC_LNX);
#endif

    // Make beginning layer WORKMAN
    set_single_persistent_default_layer(_WORKMAN);

//--RGB light initialize base layer
#ifdef RGBLIGHT_ENABLE
    // Base hue is white, and RGB disabled
    base_hue = 120;
    base_sat = 255;
    base_val = 255;
    base_mod = 2;
    base_tog = false;
    rgblight_enable();
    rgblight_mode(base_mod);
    rgblight_sethsv(base_hue,base_sat,base_val);
    rgblight_disable();
    rgblight_loadBase();
#endif

}

// matrix scan
void matrix_scan_user (void) {
    // Keymap specific, do it first
    matrix_scan_keymap();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case QWERTY:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_qwerty);
#endif
      set_single_persistent_default_layer(_QWERTY);
    }
    return false;
    break;
  case WORKMAN:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_workman);
#endif
      set_single_persistent_default_layer(_WORKMAN);
    }
    return false;
    break;
  case LOWER:
    if (record->event.pressed) {
      /* layer_on(_LOWER); */
      layer_on_update_tri_layer(_LOWER, _LOWER, _RAISE, _EMACS);
    } else {
      /* layer_off(_LOWER); */
      layer_off_update_tri_layer(_LOWER, _LOWER, _RAISE, _EMACS);
    }
    return false;
    break;
  case RAISE:
    if (record->event.pressed) {
      /* layer_on(_RAISE); */
      layer_on_update_tri_layer(_RAISE, _LOWER, _RAISE, _EMACS);
    } else {
      /* layer_off(_RAISE); */
      layer_off_update_tri_layer(_RAISE, _LOWER, _RAISE, _EMACS);
    }
    return false;
    break;
  case EMACS:
    if (record->event.pressed) {
      layer_on(_EMACS);
#ifdef AUDIO_ENABLE
      PLAY_SONG(tone_emacs);
#endif
    } else {
      layer_off(_EMACS);
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
  return process_record_keymap(keycode, record);
}

// layer change
uint32_t layer_state_set_user(uint32_t state) {

    state = layer_state_set_keymap (state);
#ifdef RGBLIGHT_ENABLE
    // Change RGB lighting depending on the last layer activated
    rgblight_change( biton32(state) );
#endif
    return state;
}
