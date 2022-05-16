#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H


// #define PREVENT_STUCK_MODIFIERS

/* #define PERMISSIVE_HOLD */
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define IGNORE_MOD_TAP_INTERRUPT
#define TAPPING_TERM 220
#define TAPPING_TERM_PER_KEY

#ifdef OLED_DRIVER_ENABLE
#define OLED_DISPLAY_128X64
#endif

#ifdef RGBLIGHT_ENABLE

#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE

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


#ifdef RGB_MATRIX_ENABLE
#define ENABLE_RGB_MATRIX_FRAMEBUFFER_EFFECTS

#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define SPLIT_TRANSPORT_MIRROR
#endif



// songs
#ifdef AUDIO_ENABLE

// defineine default songs
#undef ODE_TO_JOY
#undef ROCK_A_BYE_BABY
#undef CLUEBOARD_SOUND
#undef STARTUP_SOUND
/* #undef GOODBYE_SOUND */
#undef PLANCK_SOUND
#undef PREONIC_SOUND
#undef QWERTY_SOUND
#undef COLEMAK_SOUND
#undef DVORAK_SOUND
#undef WORKMAN_SOUND
#undef PLOVER_SOUND
#undef PLOVER_GOODBYE_SOUND
/* #undef MUSIC_ON_SOUND */
/* #undef AUDIO_ON_SOUND */
/* #undef AUDIO_OFF_SOUND */
#undef MUSIC_SCALE_SOUND
/* #undef MUSIC_OFF_SOUND */
/* #undef VOICE_CHANGE_SOUND */
/* #undef CHROMATIC_SOUND */
/* #undef MAJOR_SOUND */
/* #undef MINOR_SOUND */
/* #undef GUITAR_SOUND */
/* #undef VIOLIN_SOUND */
#undef CAPS_LOCK_ON_SOUND
#undef CAPS_LOCK_OFF_SOUND
#undef SCROLL_LOCK_ON_SOUND
#undef SCROLL_LOCK_OFF_SOUND
#undef NUM_LOCK_ON_SOUND
#undef NUM_LOCK_OFF_SOUND
/* #undef AG_NORM_SOUND */
/* #undef AG_SWAP_SOUND */
#undef UNICODE_WINDOWS
#undef UNICODE_LINUX
#undef TERMINAL_SOUND
#undef CAMPANELLA
   
#undef NOCTURNE_OP_9_NO_1
    

#undef PUZZLE
#define PUZZLE                                  \
    Q__NOTE(_G5),                               \
        Q__NOTE(_FS5),                          \
        Q__NOTE(_DS5),                          \
        Q__NOTE(_A4),                           \
        Q__NOTE(_GS4),                          \
        Q__NOTE(_E5),                           \
        Q__NOTE(_GS5),                          \
        HD_NOTE(_C6),

#undef TREASURE
#define TREASURE                                \
    Q__NOTE(_A4 ),                              \
        Q__NOTE(_AS4),                          \
        Q__NOTE(_B4 ),                          \
        HD_NOTE(_C5 ),                          \

#define MUSHROOM                                \
    S__NOTE(_C5 ),                              \
        S__NOTE(_G4 ),                          \
        S__NOTE(_C5 ),                          \
        S__NOTE(_E5 ),                          \
        S__NOTE(_G5 ),                          \
        S__NOTE(_C6 ),                          \
        S__NOTE(_G5 ),                          \
        S__NOTE(_GS4 ),                         \
        S__NOTE(_C5 ),                          \
        S__NOTE(_DS5 ),                         \
        S__NOTE(_GS5 ),                         \
        S__NOTE(_DS5 ),                         \
        S__NOTE(_GS5 ),                         \
        S__NOTE(_C6 ),                          \
        S__NOTE(_DS6 ),                         \
        S__NOTE(_GS6 ),                         \
        S__NOTE(_DS6 ),                         \
        S__NOTE(_AS4 ),                         \
        S__NOTE(_D5 ),                          \
        S__NOTE(_F5 ),                          \
        S__NOTE(_AS5 ),                         \
        S__NOTE(_D6 ),                          \
        S__NOTE(_F6 ),                          \
        S__NOTE(_AS6 ),                         \
        S__NOTE(_F6 )

#define BEEP                                    \
    S__NOTE(_A4 )

#define BEEP_BEEP                               \
    S__NOTE(_A4 ),                              \
        S__NOTE(_REST ),                        \
        S__NOTE(_A4 )

#define STARTUP_SONG SONG(MUSHROOM)

#endif

#endif // !USERSPACE_CONFIG_H

