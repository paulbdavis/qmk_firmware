#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define _WORKMAN 0
#define _QWERTY 1
#define _LOWER 2
#define _RAISE 3
#define _EMACS 4
#define _ADJUST 5
#define _NUMPAD 6


#define _______ KC_TRNS
#define XXXXXXX KC_NO

// Define all of
enum custom_keycodes {
  WORKMAN = SAFE_RANGE,
  QWERTY,
  LOWER,
  RAISE,
  ADJUST,
  SSH_PUB,
  EMACS,
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
  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};

enum  {
  SUPER_LAYER_CHANGE = 0,
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

enum {
      COLOR_DEFAULT = 0,
      COLOR_RAISE,
      COLOR_LOWER,
      COLOR_EMACS,
      COLOR_ADJUST,
      COLOR_NUMPAD
};
  
#endif
