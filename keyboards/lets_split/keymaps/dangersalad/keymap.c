#include "lets_split.h"
#include "dangersalad.h"
#include "action_layer.h"
#include "eeconfig.h"

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]      = SONG(COIN_SOUND);
float tone_workman[][2]     = SONG(ZELDA_TREASURE);
float tone_numpad[][2]      = SONG(AUDIO_ON_SOUND);
float tone_numpad_exit[][2] = SONG(AUDIO_OFF_SOUND);
float tone_emacs[][2]       = SONG(BEEP);
float tone_adjust[][2]      = SONG(ZELDA_PUZZLE);
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

void play_emacs_sound(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_emacs);
#endif
}

void play_adjust_sound(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(tone_adjust);
#endif
}

bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case SSH_PUB:
    if (record->event.pressed) {
      SEND_STRING("ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQC8RjYOMQzmVfqACviToDhEcaGfzA+chsL0Ut+7ni18EFreduIVOfPX6iceRC9yaACNjbZxz0i5+ABhgDFXLEqOoLJczW1zlinRfeMaQEyGgTAuSyhYYBy8iZnHG5Y1yR2vUQW2PQjxmBP5KH9ctmFJG/Nahppag/WMcwto/VGcp0FhQUiwIumFt5g3rONXWhuF9iAK3a0mvVQbbCdHsAjK+K5jl6jDUAAxkY98WoPaHWkrt3rhYYKXWWja1I/d7r+wn3aRArN/9H7ciQohELykQbEGT/TTZK2Ahx6uS5oUhE+BW4ckGj4gY/+faOZqeRG3KMtbyEpU7K9IdHQ8Z+Ej");
    }
    return true;
    break;
  }
  return true;
}
