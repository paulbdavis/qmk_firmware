#include "lets_split_eh.h"
#include "dangersalad.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

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
