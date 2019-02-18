#ifndef USERSPACE
#define USERSPACE

#include "quantum.h"

// define layers
#define _WORKMAN 0
#define _QWERTY 1
#define _TTS 2
#define _LOWER_TTS 3
#define _RAISE_TTS 4
#define _LOWER 5
#define _RAISE 6
#define _EMACS 7
#define _ADJUST 8
#define _NUMPAD 9


#define _______ KC_TRNS
#define XXXXXXX KC_NO

// custom keycodes
enum custom_keycodes {
                      WORKMAN = SAFE_RANGE,
                      QWERTY,
                      LOWER,
                      RAISE,
                      ADJUST,
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

// define tap dance codes and keys
enum  {
       SUPER_LAYER_CHANGE = 0,
       NUMPAD_ADJUST,
       SUPER_CTRL,
       SUPER_ALT,
       CTRL_ALT
};

#define TD_NUMPAD TD(NUMPAD_ADJUST)
#define TD_CA TD(CTRL_ALT)
#define TD_SUPER TD(SUPER_LAYER_CHANGE)
#define TD_SCTRL TD(SUPER_CTRL)
#define TD_SALT TD(SUPER_ALT)
#define TD_LCTRL LCTL_T(KC_TAB)
#define TD_RCTRL RCTL_T(KC_QUOT)
#define TD_ENT RSFT_T(KC_ENT)


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

// Shared keymaps
#define LAYOUT_planck_wrapper(...) LAYOUT_planck_grid(__VA_ARGS__)
#define LAYOUT_letssplit_wrapper(...) LAYOUT_ortho_4x12(__VA_ARGS__)

#define KEYMAP_WORKMAN                                                         \
    KC_ESC     , KC_Q   , KC_D   , KC_R      , KC_W   , KC_B      , KC_J     , KC_F   , KC_U     , KC_P     , KC_SCLN  , KC_BSPC   , \
    TD_LCTRL   , KC_A   , KC_S   , KC_H      , KC_T   , KC_G      , KC_Y     , KC_N   , KC_E     , KC_O     , KC_I     , TD_RCTRL  , \
    KC_LSFT    , KC_Z   , KC_X   , KC_M      , KC_C   , KC_V      , KC_K     , KC_L   , KC_COMM  , KC_DOT   , KC_SLSH  , TD_ENT    , \
    TD_NUMPAD  , EMACS  , TD_CA  , TD_SUPER  , LOWER  , TD_SCTRL  , TD_SALT  , RAISE  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT

#define KEYMAP_QWERTY                                                          \
    KC_ESC     , KC_Q   , KC_W   , KC_E      , KC_R   , KC_T      , KC_Y     , KC_U   , KC_I     , KC_O     , KC_P     , KC_BSPC   , \
    TD_LCTRL   , KC_A   , KC_S   , KC_D      , KC_F   , KC_G      , KC_H     , KC_J   , KC_K     , KC_L     , KC_SCLN  , TD_RCTRL  , \
    KC_LSFT    , KC_Z   , KC_X   , KC_C      , KC_V   , KC_B      , KC_N     , KC_M   , KC_COMM  , KC_DOT   , KC_SLSH  , TD_ENT    , \
    TD_NUMPAD  , EMACS  , TD_CA  , TD_SUPER  , LOWER  , TD_SCTRL  , TD_SALT  , RAISE  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT

#define KEYMAP_LOWER                                                           \
    KC_TILD  , KC_EXLM  , KC_AT    , KC_HASH  , KC_DLR   , KC_PERC  , KC_CIRC  , KC_AMPR     , KC_ASTR     , KC_LPRN  , KC_RPRN  , KC_DEL   , \
    KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    , KC_F6    , KC_COLN  , KC_UNDS     , KC_PLUS     , KC_LCBR  , KC_RCBR  , KC_PIPE  , \
    KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   , KC_F12   , XXXXXXX  , S(KC_NUHS)  , S(KC_NUBS)  , _______  , _______  , _______  , \
    _______  , _______  , _______  , _______  , _______  , _______  , _______  , _______     , KC_HOME     , KC_PGDN  , KC_PGUP  , KC_END

#define KEYMAP_RAISE                                                           \
    KC_GRV  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL  , \
    KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_SCLN , KC_MINS , KC_EQL  , KC_LBRC , KC_RBRC , KC_BSLS , \
    KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_NUHS , KC_NUBS , _______ , _______ , _______ , \
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_MPLY , KC_VOLD , KC_VOLU , KC_MUTE

#define KEYMAP_ADJUST                                                          \
    RESET   , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_HOME , KC_PGUP   , KC_PSCREEN , KC_SCROLLLOCK , KC_PAUSE , \
    AG_SWAP , XXXXXXX , RGB_RMOD , XXXXXXX , XXXXXXX , XXXXXXX , WORKMAN , KC_END  , KC_PGDOWN , KC_INSERT  , XXXXXXX       , XXXXXXX  , \
    AG_NORM , RGB_TOG , RGB_MOD  , RGB_HUI , RGB_SAI , RGB_VAI , XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX  , \
    _______ , AU_ON   , AU_OFF   , RGB_HUD , RGB_SAD , RGB_VAD , QWERTY  , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX

#define KEYMAP_EMACS                                                           \
    RESET           , EMACS_WIN_1        , EMACS_WIN_2      , EMACS_WIN_3        , EMACS_WIN_4         , XXXXXXX           , XXXXXXX           , XXXXXXX          , XXXXXXX          , XXXXXXX          , EMACS_WIN_0  , XXXXXXX  , \
    EMACS_PROJ_GIT  , EMACS_PROJ_SWITCH  , EMACS_PROJ_FILE  , EMACS_PROJ_SEARCH  , EMACS_PROJ_COMPILE  , EMACS_PROJ_SHELL  , EMACS_FLYC_CHECK  , EMACS_FLYC_NEXT  , EMACS_FLYC_PREV  , EMACS_FLYC_LIST  , XXXXXXX      , XXXXXXX  , \
      XXXXXXX       , XXXXXXX            , XXXXXXX          , XXXXXXX            , XXXXXXX             , XXXXXXX           , XXXXXXX           , XXXXXXX          , XXXXXXX          , XXXXXXX          , XXXXXXX      , XXXXXXX  , \
    _______         , _______            , XXXXXXX          , XXXXXXX            , _______             , XXXXXXX           , XXXXXXX           , _______          , XXXXXXX          , XXXXXXX          , XXXXXXX      , XXXXXXX
    

#define KEYMAP_NUMPAD                                                          \
    RESET   , _______ , _______ , _______ , _______ , _______ , KC_PSLS , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_PMNS , KC_BSPC , \
    _______ , _______ , _______ , _______ , _______ , _______ , KC_PAST , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_PPLS , KC_NLCK , \
    _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_0 , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_PDOT , KC_PENT , \
    _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
  
#endif

