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
#define _WORKMAN 2
#define _LOWER 10
#define _RAISE 11
#define _EMACS 12
#define _MOUSE 13
#define _ADJUST 29
#define _NUMPAD 30

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  COLEMAK,
  WORKMAN,
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
  NUMPAD_ADJUST,
  SUPER_CTRL,
  SUPER_ALT,
};


//**************** Definitions needed for quad function to work *********************//
//Enums used to clearly convey the state of the tap dance
enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD,
  DOUBLE_TAP,
  DOUBLE_HOLD,
  TRIPLE_TAP,
  TRIPLE_HOLD,
  DOUBLE_SINGLE_TAP //send SINGLE_TAP twice - NOT DOUBLE_TAP
  // Add more enums here if you want for triple, quadruple, etc.
};

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
  alt_tap_state.state = cur_dance(state);
  switch (alt_tap_state.state) {
  case SINGLE_TAP: 
  case SINGLE_HOLD: layer_on(_NUMPAD); break;
  case DOUBLE_TAP:
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD: layer_on(_ADJUST); break;
  }
}

void numpad_reset (qk_tap_dance_state_t *state, void *user_data) {
  pre_numpad_disable();
  switch (alt_tap_state.state) {
  case SINGLE_TAP: break;
  case SINGLE_HOLD: layer_off(_NUMPAD); break;
  case DOUBLE_TAP:
  case DOUBLE_SINGLE_TAP:
  case DOUBLE_HOLD: 
  case TRIPLE_TAP: 
  case TRIPLE_HOLD: layer_off(_NUMPAD); layer_off(_ADJUST); break;
  }
  alt_tap_state.state = 0;
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
  [MOD_BUILDER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mod_builder_finished, dance_mod_builder_reset),
  [NUMPAD_ADJUST] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, numpad_finished, numpad_reset),
  [SUPER_CTRL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_finished, ctrl_reset),
  [SUPER_ALT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
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
 * |      |      | Alt  | GUI  |Lower |Sp/Ctl|  |Sp/Alt|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_QWERTY] = LAYOUT( \
  KC_ESC            , KC_Q       , KC_W    , KC_E                   , KC_R  , KC_T           , KC_Y           , KC_U  , KC_I    , KC_O    , KC_P    , KC_BSPC         , \
  LCTL_T(KC_TAB)    , KC_A       , KC_S    , KC_D                   , KC_F  , KC_G           , KC_H           , KC_J  , KC_K    , KC_L    , KC_SCLN , RCTL_T(KC_QUOT) , \
  KC_LSFT           , KC_Z       , KC_X    , KC_C                   , KC_V  , KC_B           , KC_N           , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT)  , \
  TD(NUMPAD_ADJUST) , MO(_MOUSE) , KC_LALT , TD(SUPER_LAYER_CHANGE) , LOWER , TD(SUPER_CTRL) , TD(SUPER_ALT)  , RAISE , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT \
),

/* Colemak
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Esc  |   Q  |   W  |   F  |   P  |   G  |  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Ctrl |   A  |   R  |   S  |   T  |   D  |  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      | Alt  | GUI  |Lower |Sp/Ctl|  |Sp/Alt|Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_COLEMAK] = LAYOUT( \
  KC_ESC            , KC_Q       , KC_W    , KC_F                   , KC_P  , KC_G           , KC_J           , KC_L  , KC_U    , KC_Y    , KC_SCLN , KC_BSPC         , \
  LCTL_T(KC_TAB)    , KC_A       , KC_R    , KC_S                   , KC_T  , KC_D           , KC_H           , KC_N  , KC_E    , KC_I    , KC_O    , RCTL_T(KC_QUOT) , \
  KC_LSFT           , KC_Z       , KC_X    , KC_C                   , KC_V  , KC_B           , KC_K           , KC_M  , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT)  , \
  TD(NUMPAD_ADJUST) , MO(_MOUSE) , KC_LALT , TD(SUPER_LAYER_CHANGE) , LOWER , TD(SUPER_CTRL) , TD(SUPER_ALT)  , RAISE , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT \
),

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
[_WORKMAN]  = LAYOUT(                                                   \
  KC_ESC            , KC_Q       , KC_D    , KC_R                   , KC_W  , KC_B           , KC_J           , KC_F  , KC_U    , KC_P    , KC_SCLN , KC_BSPC         , \
  LCTL_T(KC_TAB)    , KC_A       , KC_S    , KC_H                   , KC_T  , KC_G           , KC_Y           , KC_N  , KC_E    , KC_O    , KC_I    , RCTL_T(KC_QUOT) , \
  KC_LSFT           , KC_Z       , KC_X    , KC_M                   , KC_C  , KC_V           , KC_K           , KC_L  , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT)  , \
  TD(NUMPAD_ADJUST) , MO(_MOUSE) , KC_LALT , TD(SUPER_LAYER_CHANGE) , LOWER , TD(SUPER_CTRL) , TD(SUPER_ALT)  , RAISE , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT \
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
[_LOWER] = LAYOUT( \
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
[_RAISE] = LAYOUT( \
  KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL  , \
  KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_SCLN , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS , \
  KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_NUHS , KC_NUBS , _______ , _______ , _______ , \
  _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MNXT , KC_VOLD , KC_VOLU , KC_MUTE \
),

/* Adjust
 * ,-----------------------------------------.  ,-----------------------------------------.
 * | Reset|      |      |      |      |      |  |      | Home | PgUp |Prtscr|Scrllk|Pause |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |AGSwap|      |      |      |      |      |  |WrkMan| End  | PgDn |Insert|      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |AGNorm|      |      |      |      |      |  |Colemk|      |      |      |      |      |
 * |------+------+------+------+------+------|  |------+------+------+------+------+------|
 * |      |      |      |      |      |         |Qwerty|      |      |      |      |      |
 * `-----------------------------------------'  `-----------------------------------------'
 */
[_ADJUST] =  LAYOUT( \
  RESET   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_HOME , KC_PGUP   , KC_PSCREEN , KC_SCROLLLOCK , KC_PAUSE , \
  AG_SWAP , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , WORKMAN , KC_END  , KC_PGDOWN , KC_INSERT  , XXXXXXX       , XXXXXXX  , \
  AG_NORM , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , COLEMAK , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX  , \
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , QWERTY  , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX \
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
[_EMACS] =  LAYOUT( \
  RESET          , EMACS_WIN_1       , EMACS_WIN_2     , EMACS_WIN_3       , EMACS_WIN_4        , XXXXXXX          , XXXXXXX          , XXXXXXX         , XXXXXXX         , XXXXXXX         , EMACS_WIN_0 , XXXXXXX , \
  EMACS_PROJ_GIT , EMACS_PROJ_SWITCH , EMACS_PROJ_FILE , EMACS_PROJ_SEARCH , EMACS_PROJ_COMPILE , EMACS_PROJ_SHELL , EMACS_FLYC_CHECK , EMACS_FLYC_NEXT , EMACS_FLYC_PREV , EMACS_FLYC_LIST , XXXXXXX     , XXXXXXX , \
  XXXXXXX        , XXXXXXX           , XXXXXXX         , XXXXXXX           , XXXXXXX            , XXXXXXX          , XXXXXXX          , XXXXXXX         , XXXXXXX         , XXXXXXX         , XXXXXXX     , XXXXXXX , \
  _______        , _______           , XXXXXXX         , XXXXXXX           , _______            , XXXXXXX          , XXXXXXX          , _______         , XXXXXXX         , XXXXXXX         , XXXXXXX     , XXXXXXX \
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
[_NUMPAD] =  LAYOUT( \
  RESET   , _______ , _______ , _______ , _______ , _______ , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_PSLS , KC_NLCK , KC_BSPC , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_PAST , XXXXXXX , XXXXXXX , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_PMNS , KC_PENT , KC_PENT , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_0 , KC_KP_0 , KC_PDOT , KC_PPLS , KC_PENT , KC_PENT \
 ),

/* Mouse
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
[_MOUSE] =  LAYOUT( \
  RESET   , _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , _______ , \
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
    case WORKMAN:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_WORKMAN);
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
