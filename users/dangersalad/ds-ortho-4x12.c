#include QMK_KEYBOARD_H
#include "dangersalad.h"

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
        KC_ESC         , KC_Q    , KC_D           , KC_R    , KC_W  , KC_B    , KC_J           , KC_F  , KC_U    , KC_P    , KC_SCLN , KC_BSPC        , \
        KC_TAB         , KC_A    , KC_S           , KC_H    , KC_T  , KC_G    , KC_Y           , KC_N  , KC_E    , KC_O    , KC_I    , KC_QUOT        , \
        KC_LSFT        , KC_Z    , KC_X           , KC_M    , KC_C  , KC_V    , KC_K           , KC_L  , KC_COMM , KC_DOT  , KC_SLSH , RSFT_T(KC_ENT) , \
        TD(TD_NUM_ADJ) , XXXXXXX , TD(TD_NUM_ADJ) , KC_LGUI , LOWER , KC_LCTL , LALT_T(KC_SPC) , RAISE , KC_RCTL , KC_RALT , XXXXXXX , XXXXXXX \
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
        KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , KC_DEL  , \
        KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_COLN , KC_UNDS , KC_PLUS , KC_LCBR , KC_RCBR , KC_PIPE , \
        KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_HOME , KC_PGDN , KC_PGUP , KC_END  , _______ , \
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
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
        KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , \
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
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
        RESET   , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_HOME , KC_PGUP   , KC_PSCREEN , KC_SCROLLLOCK , KC_PAUSE , \
        AG_SWAP , XXXXXXX , RGB_RMOD , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_END  , KC_PGDOWN , KC_INSERT  , XXXXXXX       , XXXXXXX  , \
        AG_NORM , RGB_TOG , RGB_MOD  , RGB_HUI , RGB_SAI , RGB_VAI , XXXXXXX , RGB_M_P , RGB_M_B   , RGB_M_SW   , RGB_M_G       , XXXXXXX  , \
        _______ , AU_ON   , AU_OFF   , RGB_HUD , RGB_SAD , RGB_VAD , XXXXXXX , XXXXXXX , XXXXXXX   , XXXXXXX    , XXXXXXX       , XXXXXXX \
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
        RESET   , E_WIN_1 , E_WIN_2  , E_WIN_3  , E_WIN_4         , XXXXXXX   , XXXXXXX      , XXXXXXX     , XXXXXXX     , XXXXXXX     , E_WIN_0 , XXXXXXX , \
        E_P_GIT , E_P_SW  , E_P_FILE , E_P_SRCH , E_P_COMP        , E_P_SHELL , E_FLYC_CHECK , E_FLYC_NEXT , E_FLYC_PREV , E_FLYC_LIST , XXXXXXX , XXXXXXX , \
        XXXXXXX , XXXXXXX , XXXXXXX  , XXXXXXX  , E_SWITCH_BUFFER , XXXXXXX   , XXXXXXX      , E_FIND_FILE , XXXXXXX     , XXXXXXX     , XXXXXXX , XXXXXXX , \
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ \
        ),

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
