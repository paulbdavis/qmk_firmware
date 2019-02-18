#include "lets_split.h"
#include "dangersalad.h"

void matrix_init_keymap (void) {
}

uint32_t layer_state_set_keymap(uint32_t state) {
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_WORKMAN] = LAYOUT_letssplit_wrapper(KEYMAP_WORKMAN),
    [_QWERTY] = LAYOUT_letssplit_wrapper(KEYMAP_QWERTY),
    [_LOWER] = LAYOUT_letssplit_wrapper(KEYMAP_LOWER),
    [_RAISE] = LAYOUT_letssplit_wrapper(KEYMAP_RAISE),
    [_ADJUST] = LAYOUT_letssplit_wrapper(KEYMAP_ADJUST),
    [_EMACS] = LAYOUT_letssplit_wrapper(KEYMAP_EMACS),
    [_NUMPAD] = LAYOUT_letssplit_wrapper(KEYMAP_NUMPAD),
};
