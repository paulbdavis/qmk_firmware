#include "dangersalad.h"
#include "quantum.h"
#include "action.h"
#include "version.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}

__attribute__ ((weak))
void play_qwerty_sound(void) {
}

__attribute__ ((weak))
void play_workman_sound(void) {
}

__attribute__ ((weak))
void play_numpad_sound(void) {
}

__attribute__ ((weak))
void play_numpad_exit_sound(void) {
}


typedef struct {
  bool is_press_action;
  int state;
} tap;

void pre_numpad_disable (void) {
  // always deactivate these to prevent them getting stuck on since
  // the numpad overrides them
  layer_off(_RAISE);
  unregister_code(KC_LALT);
  unregister_code(KC_LGUI);
}

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
    layer_on(_NUMPAD);
#ifdef AUDIO_ENABLE
    play_numpad_sound();
#endif
    break;
  case DOUBLE_TAP:
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD: layer_on(_ADJUST); break;
  }
}

void numpad_reset (qk_tap_dance_state_t *state, void *user_data) {
  pre_numpad_disable();
  switch (numpad_tap_state.state) {
  case SINGLE_TAP: break;
  case SINGLE_HOLD:
    layer_off(_NUMPAD);
#ifdef AUDIO_ENABLE
    play_numpad_exit_sound();
#endif
    break;
  case DOUBLE_TAP:
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD:
    if (biton32(layer_state) == _NUMPAD) {
#ifdef AUDIO_ENABLE
    play_numpad_exit_sound();
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


void dance_numpad_adjust (qk_tap_dance_state_t *state, void *user_data) {
  // one or two taps activates the numpad, two tap start is sticky
  if (state->count < 3) {
    pre_numpad_disable();
    layer_on(_NUMPAD);
    return;
  }
  if (state->count == 3) {
    layer_on(_ADJUST);
    return;
  }
}

void dance_numpad_adjust_reset (qk_tap_dance_state_t *state, void *user_data) {
  // one tap reset turns off the numpad
  if (state->count == 1) {
    pre_numpad_disable();
    layer_off(_NUMPAD);
    return;
  }
  if (state->count == 3) {
    layer_off(_ADJUST);
    return;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [SUPER_LAYER_CHANGE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_super_finished, dance_super_reset),
  [NUMPAD_ADJUST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_finished, numpad_reset),
  [SUPER_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_finished, ctrl_reset),
  [SUPER_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        play_qwerty_sound();
        #endif
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
        play_workman_sound();
        #endif
        set_single_persistent_default_layer(_WORKMAN);
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
    case SSH_PUB:
      if (record->event.pressed) {
        SEND_STRING("ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC8RjYOMQzmVfqACviToDhEcaGfzA+chsL0Ut+7ni18EFreduIVOfPX6iceRC9yaACNjbZxz0i5+ABhgDFXLEqOoLJczW1zlinRfeMaQEyGgTAuSyhYYBy8iZnHG5Y1yR2vUQW2PQjxmBP5KH9ctmFJG/Nahppag/WMcwto/VGcp0FhQUiwIumFt5g3rONXWhuF9iAK3a0mvVQbbCdHsAjK+K5jl6jDUAAxkY98WoPaHWkrt3rhYYKXWWja1I/d7r+wn3aRArN/9H7ciQohELykQbEGT/TTZK2Ahx6uS5oUhE+BW4ckGj4gY/+faOZqeRG3KMtbyEpU7K9IdHQ8Z+Ej");
      }
      return true;
      break;
  }
  return process_record_keymap(keycode, record);
}
