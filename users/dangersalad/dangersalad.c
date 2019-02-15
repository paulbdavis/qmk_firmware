#include QMK_KEYBOARD_H
#include "dangersalad.h"
#include "quantum.h"
#include "action.h"
#include "version.h"
#include "split_flags.h"

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

__attribute__ ((weak))
void play_emacs_sound(void) {
}

__attribute__ ((weak))
void play_adjust_sound(void) {
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
  case _LOWER_TTS:
    rgblight_sethsv_azure();
    break;
  case _ADJUST:
    rgblight_sethsv_white();
    break;
  case _RAISE_TTS:
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
#ifdef SPLIT_KEYBOARD
  RGB_DIRTY = true;
#endif
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
    play_numpad_sound();
#endif
    break;
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD:
    if (biton32(layer_state) != _NUMPAD) {
#ifdef AUDIO_ENABLE
    play_adjust_sound();
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
    play_numpad_exit_sound();
#endif
    break;
  case DOUBLE_TAP: break;
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


qk_tap_dance_action_t tap_dance_actions[] = {
  [SUPER_LAYER_CHANGE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_super_finished, dance_super_reset),
  [NUMPAD_ADJUST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_finished, numpad_reset),
  [SUPER_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_finished, ctrl_reset),
  [SUPER_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
  [CTRL_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LALT|KC_LCTL),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Workman
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   H  |   T  |   G  |  |   Y  |   N  |   E  |   O  |   I  |  '   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |  |   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      | Alt  | GUI  |Lower |Sp/Ctl|  |Sp/Alt|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_WORKMAN]  = LAYOUT_ortho_4x12(                                                   \
  KC_ESC             , KC_Q   , KC_D          , KC_R                    , KC_W   , KC_B            , KC_J           , KC_F   , KC_U     , KC_P     , KC_SCLN  , KC_BSPC          , \
  LCTL_T(KC_TAB)     , KC_A   , KC_S          , KC_H                    , KC_T   , KC_G            , KC_Y           , KC_N   , KC_E     , KC_O     , KC_I     , RCTL_T(KC_QUOT)  , \
  KC_LSFT            , KC_Z   , KC_X          , KC_M                    , KC_C   , KC_V            , KC_K           , KC_L   , KC_COMM  , KC_DOT   , KC_SLSH  , RSFT_T(KC_ENT)   , \
  TD(NUMPAD_ADJUST)  , EMACS  , TD(CTRL_ALT)  , TD(SUPER_LAYER_CHANGE)  , LOWER  , TD(SUPER_CTRL)  , TD(SUPER_ALT)  , RAISE  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT \
),

/* Qwerty
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Ctrl |   A  |   S  |   D  |   F  |   G  |  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      | Alt  | GUI  |Lower |Sp/Ctl|  |Sp/Alt|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC             , KC_Q     , KC_W     , KC_E                    , KC_R   , KC_T            , KC_Y           , KC_U   , KC_I     , KC_O     , KC_P     , KC_BSPC          , \
  LCTL_T(KC_TAB)     , KC_A     , KC_S     , KC_D                    , KC_F   , KC_G            , KC_H           , KC_J   , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_QUOT)  , \
  KC_LSFT            , KC_Z     , KC_X     , KC_C                    , KC_V   , KC_B            , KC_N           , KC_M   , KC_COMM  , KC_DOT   , KC_SLSH  , RSFT_T(KC_ENT)   , \
  TD(NUMPAD_ADJUST)  , XXXXXXX  , KC_LALT  , TD(SUPER_LAYER_CHANGE)  , LOWER  , TD(SUPER_CTRL)  , TD(SUPER_ALT)  , RAISE  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT \
),

[_TTS] = LAYOUT_ortho_4x12(
   KC_ESC   , KC_Q     , KC_W  , KC_E                , KC_R       , KC_T       , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
   KC_TAB   , KC_A     , KC_S  , KC_D                , KC_F       , KC_G       , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
   KC_LSFT  , KC_L     , KC_H  , KC_C                , KC_V       , KC_B       , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
   KC_LCTL  , KC_LALT  , KC_M  , LCTL(LSFT(KC_GRV))  , LOWER_TTS  , RAISE_TTS  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX \
),
[_LOWER_TTS] = LAYOUT_ortho_4x12( \
  KC_DEL   , KC_MINUS  , KC_UP    , KC_EQL    , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
  _______  , KC_LEFT   , KC_DOWN  , KC_RIGHT  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
  _______  , XXXXXXX   , XXXXXXX  , XXXXXXX   , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
  RESET    , WORKMAN   , QWERTY   , _______   , _______  , _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX \
),
[_RAISE_TTS] = LAYOUT_ortho_4x12( \
  KC_DEL   , XXXXXXX  , KC_1  , KC_2  , KC_3    ,  XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
  KC_DEL   , XXXXXXX  , KC_4  , KC_5  , KC_6    ,  XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
  _______  , XXXXXXX  , KC_7  , KC_8  , KC_9    ,  XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , \
  _______  , _______  , KC_0  , KC_0  , KC_DOT  ,  _______  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX \
),
/* Lower
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  |   :  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |  |      |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |      |      | Home | PgDn | PgUp | End  |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR    , KC_ASTR    , KC_LPRN , KC_RPRN , KC_DEL  , \
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_COLN , KC_UNDS    , KC_PLUS    , KC_LCBR , KC_RCBR , KC_PIPE , \
  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , S(KC_NUHS) , S(KC_NUBS) , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______    , KC_HOME    , KC_PGDN , KC_PGUP , KC_END  \
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
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL  , \
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_SCLN , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS , \
  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_NUHS , KC_NUBS , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MPLY , KC_VOLD , KC_VOLU , KC_MUTE \
),

/* Adjust
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Reset|      |      |      |      |      |  |      | Home | PgUp |Prtscr|Scrllk|Pause |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |AGSwap|      |      |      |      |      |  |WrkMan| End  | PgDn |Insert|      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |AGNorm|      |      |      |      |      |  |      |      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |Qwerty|      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  RESET   , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , TTS     , KC_HOME , KC_PGUP   , KC_PSCREEN , KC_SCROLLLOCK , KC_PAUSE , \
  AG_SWAP , XXXXXXX , RGB_RMOD , XXXXXXX , XXXXXXX , XXXXXXX , WORKMAN , KC_END  , KC_PGDOWN , KC_INSERT  , XXXXXXX       , XXXXXXX  , \
  AG_NORM , RGB_TOG , RGB_MOD  , RGB_HUI , RGB_SAI , RGB_VAI , XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX  , \
  _______ , AU_ON   , AU_OFF   , RGB_HUD , RGB_SAD , RGB_VAD , QWERTY  , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX \
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
[_EMACS] =  LAYOUT_ortho_4x12( \
  RESET          , EMACS_WIN_1       , EMACS_WIN_2     , EMACS_WIN_3       , EMACS_WIN_4         , XXXXXXX          , XXXXXXX          , XXXXXXX         , XXXXXXX         , XXXXXXX         , EMACS_WIN_0 , SSH_PUB , \
  EMACS_PROJ_GIT , EMACS_PROJ_SWITCH , EMACS_PROJ_FILE , EMACS_PROJ_SEARCH , EMACS_PROJ_COMPILE  , EMACS_PROJ_SHELL , EMACS_FLYC_CHECK , EMACS_FLYC_NEXT , EMACS_FLYC_PREV , EMACS_FLYC_LIST , XXXXXXX     , XXXXXXX , \
  XXXXXXX        , XXXXXXX           , XXXXXXX         , XXXXXXX           , EMACS_SWITCH_BUFFER , XXXXXXX          , XXXXXXX          , EMACS_FIND_FILE , XXXXXXX         , XXXXXXX         , XXXXXXX     , XXXXXXX , \
  _______        , _______           , XXXXXXX         , XXXXXXX           , _______             , XXXXXXX          , XXXXXXX          , _______         , XXXXXXX         , XXXXXXX         , XXXXXXX     , XXXXXXX \
 )               ,

/* Number Pad
 * ,-----------------------------------------.  ,-----------------------------------------.
 * |      |      |      |      |      |      |  |  7   |  8   |  9   |  /   |NmLck | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |  4   |  5   |  6   |  *   |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |  |  1   |  2   |  3   |  -   |Enter |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |  0   |  0   |  .   |  +   |Enter |Enter |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_NUMPAD] =  LAYOUT_ortho_4x12( \
  RESET   , _______ , _______ , _______ , _______ , _______ , KC_PSLS , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_PMNS , KC_BSPC , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_PAST , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_PPLS , KC_NLCK , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_0 , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_PDOT , KC_PENT , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
 ),

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
  case TTS:
    if (record->event.pressed) {
#ifdef AUDIO_ENABLE
      play_dvorak_sound();
#endif
      set_single_persistent_default_layer(_TTS);
    }
    return false;
    break;
  case LOWER_TTS:
    if (record->event.pressed) {
      layer_on(_LOWER_TTS);
    } else {
      layer_off(_LOWER_TTS);
    }
    return false;
    break;
  case RAISE_TTS:
    if (record->event.pressed) {
      layer_on(_RAISE_TTS);
    } else {
      layer_off(_RAISE_TTS);
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
      play_emacs_sound();
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
