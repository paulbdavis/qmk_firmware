#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

#define _WORKMAN 0
#define _LOWER 1
#define _RAISE 2
#define _EMACS 3
#define _ADJUST 4
#define _NUMPAD 5

// Define all of
enum custom_keycodes {
  WORKMAN = SAFE_RANGE,
  LOWER,
  RAISE,
  EMACS,
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
  EMACS_FIND_FILE,
  EMACS_SWITCH_BUFFER,
  NEW_SAFE_RANGE  //use "NEW_SAFE_RANGE" for keymap specific codes
};

enum  {
  TD_SUPER = 0,
  TD_NUM_ADJ,
  TD_LOWER,
  TD_RAISE
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

#endif
