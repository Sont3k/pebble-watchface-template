#ifndef WATCHFACE_CLAY_SETTINGS_H
#define WATCHFACE_CLAY_SETTINGS_H

#include <pebble.h>

#define SETTINGS_KEY 1

typedef struct ClaySettings {
    GColor BackgroundColor;
    GColor TextColor;
    bool TemperatureUnit; // false = Celsius, true = Fahrenheit
    bool ShowDate;
} ClaySettings;
extern ClaySettings settings;

void prv_default_settings();
void prv_save_settings();
void prv_load_settings();
void prv_update_display();

#endif //WATCHFACE_CLAY_SETTINGS_H