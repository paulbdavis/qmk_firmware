#include "lets_split.h"
#include "dangersalad.h"
#include "action_layer.h"
#include "eeconfig.h"

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]       = SONG(BEEP);
float tone_workman[][2]       = SONG(BEEP_BEEP);
float tone_numpad[][2]       = SONG(BEEP_BEEP);
float tone_numpad_exit[][2]  = SONG(BEEP);
#endif

extern keymap_config_t keymap_config;

void play_qwerty_sound(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_qwerty);
#endif
}

void play_workman_sound(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_workman);
#endif
}

void play_numpad_sound(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_numpad);
#endif
}

void play_numpad_exit_sound(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_numpad_exit);
#endif
}


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
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_ESC             , KC_Q     , KC_W     , KC_E                    , KC_R   , KC_T            , KC_Y           , KC_U   , KC_I     , KC_O     , KC_P     , KC_BSPC          , \
  LCTL_T(KC_TAB)     , KC_A     , KC_S     , KC_D                    , KC_F   , KC_G            , KC_H           , KC_J   , KC_K     , KC_L     , KC_SCLN  , RCTL_T(KC_QUOT)  , \
  KC_LSFT            , KC_Z     , KC_X     , KC_C                    , KC_V   , KC_B            , KC_N           , KC_M   , KC_COMM  , KC_DOT   , KC_SLSH  , RSFT_T(KC_ENT)   , \
  TD(NUMPAD_ADJUST)  , XXXXXXX  , KC_LALT  , TD(SUPER_LAYER_CHANGE)  , LOWER  , TD(SUPER_CTRL)  , TD(SUPER_ALT)  , RAISE  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT \
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
[_WORKMAN]  = LAYOUT_ortho_4x12(                                                   \
  KC_ESC             , KC_Q     , KC_D     , KC_R                    , KC_W   , KC_B            , KC_J           , KC_F   , KC_U     , KC_P     , KC_SCLN  , KC_BSPC          , \
  LCTL_T(KC_TAB)     , KC_A     , KC_S     , KC_H                    , KC_T   , KC_G            , KC_Y           , KC_N   , KC_E     , KC_O     , KC_I     , RCTL_T(KC_QUOT)  , \
  KC_LSFT            , KC_Z     , KC_X     , KC_M                    , KC_C   , KC_V            , KC_K           , KC_L   , KC_COMM  , KC_DOT   , KC_SLSH  , RSFT_T(KC_ENT)   , \
  TD(NUMPAD_ADJUST)  , XXXXXXX  , KC_LALT  , TD(SUPER_LAYER_CHANGE)  , LOWER  , TD(SUPER_CTRL)  , TD(SUPER_ALT)  , RAISE  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT \
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
  RESET   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_HOME , KC_PGUP   , KC_PSCREEN , KC_SCROLLLOCK , KC_PAUSE , \
  AG_SWAP , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , WORKMAN , KC_END  , KC_PGDOWN , KC_INSERT  , XXXXXXX       , XXXXXXX  , \
  AG_NORM , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX  , \
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
[_EMACS] =  LAYOUT_ortho_4x12( \
  RESET          , EMACS_WIN_1       , EMACS_WIN_2     , EMACS_WIN_3       , EMACS_WIN_4        , XXXXXXX          , XXXXXXX          , XXXXXXX         , XXXXXXX         , XXXXXXX         , EMACS_WIN_0 , SSH_PUB , \
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
[_NUMPAD] =  LAYOUT_ortho_4x12( \
  RESET   , _______ , _______ , _______ , _______ , _______ , KC_KP_7 , KC_KP_8 , KC_KP_9 , KC_PSLS , KC_NLCK , KC_BSPC , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_4 , KC_KP_5 , KC_KP_6 , KC_PAST , XXXXXXX , XXXXXXX , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_1 , KC_KP_2 , KC_KP_3 , KC_PMNS , KC_PENT , KC_PENT , \
  _______ , _______ , _______ , _______ , _______ , _______ , KC_KP_0 , KC_KP_0 , KC_PDOT , KC_PPLS , KC_PENT , KC_PENT \
 ),

};

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  return true;
}
