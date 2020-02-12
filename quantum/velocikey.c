#include "velocikey.h"
#include "timer.h"
#include "eeconfig.h"
#include "eeprom.h"
#include "rgblight.h"

#ifndef MIN
#    define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef MAX
#    define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef VELOCIKEY_MAX_VALUE
#    define VELOCIKEY_MAX_VALUE 200
#endif

#ifndef VELOCIKEY_STEP
#    define VELOCIKEY_STEP 1
#endif

uint8_t typing_speed = 0;
uint8_t last_query = 0;
uint8_t step_cache = 0;

bool velocikey_enabled(void) { return eeprom_read_byte(EECONFIG_VELOCIKEY) == 1; }

void velocikey_toggle(void) {
    if (velocikey_enabled())
        eeprom_update_byte(EECONFIG_VELOCIKEY, 0);
    else
        eeprom_update_byte(EECONFIG_VELOCIKEY, 1);
}

void velocikey_accelerate(void) {
    step_cache++;
    if (step_cache >= VELOCIKEY_STEP) {
        if (typing_speed < VELOCIKEY_MAX_VALUE) {
            typing_speed += (VELOCIKEY_MAX_VALUE / 100) * VELOCIKEY_STEP;
        }
        step_cache = 0;
        rgblight_alter_change_flags(RGBLIGHT_STATUS_CHANGE_VELOCIKEY);
    }
}

void velocikey_set_typing_speed(uint8_t new_speed) {
    typing_speed = new_speed;
}

uint8_t velocikey_get_typing_speed(void) {
    return typing_speed;
}

bool velocikey_typing_speed_changed(void) {
    bool changed = last_query != typing_speed;
    last_query = typing_speed;
    return changed;
}

void velocikey_decelerate(void) {
    static uint16_t decay_timer = 0;

    if (timer_elapsed(decay_timer) > 500 || decay_timer == 0) {
        if (typing_speed > 0) typing_speed -= 1;
        // Decay a little faster at half of max speed
        if (typing_speed > VELOCIKEY_MAX_VALUE / 2) typing_speed -= 1;
        // Decay even faster at 3/4 of max speed
        if (typing_speed > VELOCIKEY_MAX_VALUE / 4 * 3) typing_speed -= 2;
        decay_timer = timer_read();
        rgblight_alter_change_flags(RGBLIGHT_STATUS_CHANGE_VELOCIKEY);
    }
}

uint8_t velocikey_match_speed(uint8_t minValue, uint8_t maxValue) { return MAX(minValue, maxValue - (maxValue - minValue) * ((float)typing_speed / VELOCIKEY_MAX_VALUE)); }
