#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H


#define PREVENT_STUCK_MODIFIERS

#define TAPPING_TERM 150


// songs
#ifdef AUDIO_ENABLE

#define BEEP                                    \
  S__NOTE(_A4 )

#define BEEP_BEEP                               \
  S__NOTE(_A4 ),                                \
    S__NOTE(_REST ),                            \
    S__NOTE(_A4 )

#define STARTUP_SONG SONG(MARIO_MUSHROOM)

#endif

#ifdef RGBLIGHT_ENABLE
/* #define RGBLIGHT_ANIMATIONS */
#endif

#endif // !USERSPACE_CONFIG_H
