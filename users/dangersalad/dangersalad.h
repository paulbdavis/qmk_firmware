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
  E_WIN_1,
  E_WIN_2, 
  E_WIN_3,
  E_WIN_4,
  E_WIN_0,
  E_PROJ_SWITCH,
  E_PROJ_FILE,
  E_PROJ_SEARCH,
  E_PROJ_COMPILE,
  E_PROJ_SHELL,
  E_PROJ_GIT,
  E_FLYC_CHECK,
  E_FLYC_NEXT,
  E_FLYC_PREV,
  E_FLYC_LIST,
  E_FIND_FILE,
  E_SWITCH_BUFFER,
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
