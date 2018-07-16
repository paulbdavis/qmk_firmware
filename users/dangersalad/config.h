#ifndef USERSPACE_CONFIG_H
#define USERSPACE_CONFIG_H


#define PREVENT_STUCK_MODIFIERS

#define TAPPING_TERM 200


// songs
#ifdef AUDIO_ENABLE

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
