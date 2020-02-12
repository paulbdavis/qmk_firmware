#ifndef VELOCIKEY_H
#define VELOCIKEY_H

#include <stdint.h>
#include <stdbool.h>

bool    velocikey_enabled(void);
void    velocikey_toggle(void);
void    velocikey_accelerate(void);
void    velocikey_decelerate(void);
uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue);
void    velocikey_set_typing_speed(uint8_t new_speed);
uint8_t velocikey_get_typing_speed(void);
bool    velocikey_typing_speed_changed(void);

#endif
