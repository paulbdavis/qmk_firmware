#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H


// #define PREVENT_STUCK_MODIFIERS

#define PERMISSIVE_HOLD
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 220
#define TAPPING_TERM_PER_KEY

#ifdef OLED_DRIVER_ENABLE
#define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE
#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif


// songs
#ifdef AUDIO_ENABLE

#undef PUZZLE
#define PUZZLE \
    Q__NOTE(_G5),     \
    Q__NOTE(_FS5),    \
    Q__NOTE(_DS5),     \
    Q__NOTE(_A4),    \
    Q__NOTE(_GS4),     \
    Q__NOTE(_E5),     \
    Q__NOTE(_GS5),     \
    HD_NOTE(_C6),

#undef TREASURE
#define TREASURE \
    Q__NOTE(_A4 ), \
    Q__NOTE(_AS4), \
    Q__NOTE(_B4 ), \
    HD_NOTE(_C5 ), \

#define MUSHROOM                                \
  S__NOTE(_C5 ),                                \
    S__NOTE(_G4 ),                              \
    S__NOTE(_C5 ),                              \
    S__NOTE(_E5 ),                              \
    S__NOTE(_G5 ),                              \
    S__NOTE(_C6 ),                              \
    S__NOTE(_G5 ),                              \
    S__NOTE(_GS4 ),                             \
    S__NOTE(_C5 ),                              \
    S__NOTE(_DS5 ),                             \
    S__NOTE(_GS5 ),                             \
    S__NOTE(_DS5 ),                             \
    S__NOTE(_GS5 ),                             \
    S__NOTE(_C6 ),                              \
    S__NOTE(_DS6 ),                             \
    S__NOTE(_GS6 ),                             \
    S__NOTE(_DS6 ),                             \
    S__NOTE(_AS4 ),                             \
    S__NOTE(_D5 ),                              \
    S__NOTE(_F5 ),                              \
    S__NOTE(_AS5 ),                             \
    S__NOTE(_D6 ),                              \
    S__NOTE(_F6 ),                              \
    S__NOTE(_AS6 ),                             \
    S__NOTE(_F6 )

#define BEEP                                    \
  S__NOTE(_A4 )

#define BEEP_BEEP                               \
  S__NOTE(_A4 ),                                \
    S__NOTE(_REST ),                            \
    S__NOTE(_A4 )

#define STARTUP_SONG SONG(MUSHROOM)

#endif

#endif // !USERSPACE_CONFIG_H

