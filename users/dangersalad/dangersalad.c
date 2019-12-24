#include QMK_KEYBOARD_H
#include "dangersalad.h"
#include "quantum.h"
#include "action.h"
#include "version.h"

__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

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

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
    switch (biton32(state)) {
    case _RAISE:
        rgblight_sethsv_orange();
        break;
    case _LOWER:
        rgblight_sethsv_azure();
        break;
    case _ADJUST:
        rgblight_sethsv_white();
        break;
    case _NUMPAD:
        rgblight_sethsv_red();
        break;
    case _EMACS:
        rgblight_sethsv_magenta();
        break;
    default:
        rgblight_sethsv_green();
        break;
    }
#endif
    return state;
}

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
static tap numpad_tap_state = {
    .is_press_action = true,
    .state = 0
};

static tap raise_tap_state = {
    .is_press_action = true,
    .state = 0
};

static tap lower_tap_state = {
    .is_press_action = true,
    .state = 0
};

void pre_numpad_disable (void) {
    // always deactivate these to prevent them getting stuck on since
    // the numpad overrides them
    layer_off(_RAISE);
    unregister_code(KC_LALT);
    unregister_code(KC_LGUI);
}

void lower_finished (qk_tap_dance_state_t *state, void *user_data) {
    lower_tap_state.state = cur_dance(state);
    switch (lower_tap_state.state) {
    case SINGLE_HOLD:
        layer_on_update_tri_layer(_LOWER, _LOWER, _RAISE, _EMACS);
        break;
    case DOUBLE_HOLD:
        layer_on(_RAISE);
        register_code (KC_LGUI);
        break;
    case TRIPLE_HOLD:
        layer_on(_RAISE);
        register_code(KC_LCTRL);
        register_code (KC_LGUI);
        break;
    }
}

void lower_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (lower_tap_state.state) {
    case SINGLE_HOLD:
        layer_off_update_tri_layer(_LOWER, _LOWER, _RAISE, _EMACS);
        break;
    case DOUBLE_HOLD:
        layer_off(_RAISE);
        unregister_code (KC_LGUI);
        break;
    case TRIPLE_HOLD:
        layer_off(_RAISE);
        unregister_code(KC_LCTRL);
        unregister_code (KC_LGUI);
        break;
    }
    lower_tap_state.state = 0;
}


void raise_finished (qk_tap_dance_state_t *state, void *user_data) {
    raise_tap_state.state = cur_dance(state);
    switch (raise_tap_state.state) {
    case SINGLE_TAP:
        register_code(KC_ENTER);
        break;
    case SINGLE_HOLD:
        layer_on_update_tri_layer(_RAISE, _LOWER, _RAISE, _EMACS);
        break;
    case DOUBLE_HOLD:
        register_code (KC_LGUI);
        break;
    case TRIPLE_HOLD:
        register_code(KC_LCTRL);
        register_code (KC_LGUI);
        break;
    }
}

void raise_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (raise_tap_state.state) {
    case SINGLE_TAP:
        unregister_code(KC_ENTER);
        break;
    case SINGLE_HOLD:
        layer_off_update_tri_layer(_RAISE, _LOWER, _RAISE, _EMACS);
        break;
    case DOUBLE_HOLD:
        unregister_code (KC_LGUI);
        break;
    case TRIPLE_HOLD:
        unregister_code(KC_LCTRL);
        unregister_code (KC_LGUI);
        break;
    }
    raise_tap_state.state = 0;
}

void numpad_finished (qk_tap_dance_state_t *state, void *user_data) {
    pre_numpad_disable();
    numpad_tap_state.state = cur_dance(state);
    switch (numpad_tap_state.state) {
    case SINGLE_TAP: 
    case SINGLE_HOLD:
    case DOUBLE_TAP:
        layer_on(_NUMPAD);
        break;
    case DOUBLE_SINGLE_TAP:
    case DOUBLE_HOLD: 
    case TRIPLE_TAP: 
    case TRIPLE_HOLD:
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
        break;
    case DOUBLE_TAP: break;
    case DOUBLE_SINGLE_TAP:
    case DOUBLE_HOLD: 
    case TRIPLE_TAP: 
    case TRIPLE_HOLD:
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
    [TD_SUPER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_super_finished, dance_super_reset),
    [TD_NUM_ADJ] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_finished, numpad_reset),
    [TD_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, lower_finished, lower_reset),
    [TD_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, raise_finished, raise_reset)
};

uint16_t get_tapping_term(uint16_t keycode) {
    switch (keycode) {
    case LCTL_T(KC_SPC):
    case LALT_T(KC_SPC):
        return 130;
    default:
        return TAPPING_TERM;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case WORKMAN:
        if (record->event.pressed) {
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
    case EMACS_FIND_FILE:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("x")SS_LCTRL("f"));
        }
        return true;
        break;
    case EMACS_SWITCH_BUFFER:
        if (record->event.pressed) {
            SEND_STRING(SS_LCTRL("x")"b");
        }
        return true;
        break;
    }
    return process_record_keymap(keycode, record);
}
