#ifndef PIXY_WATCHFACE_WATCHFACE_MODULES
#define PIXY_WATCHFACE_WATCHFACE_MODULES

#include <pebble.h>

#include "modules/battery/battery.h"
#include "modules/bluetooth/bluetooth.h"
#include "modules/time/time.h"
#include "modules/timeline_peek/timeline_peek.h"
#include "modules/weather/weather.h"

typedef struct {
    void (*init)(void);
    void (*load)(Window *window, Layer *window_layer, GRect bounds);
    void (*tick)(struct tm *tick_time, TimeUnits units_changed);
    void (*unload)(Window *window);
} WatchfaceModule;

static WatchfaceModule s_modules[] = {
    {app_message_init, NULL, app_message_tick_handler, NULL},
    {time_init, time_on_window_load, time_tick_handler, time_on_window_unload},
    {battery_init, battery_on_window_load, NULL, battery_on_window_unload},
    {bluetooth_init, bluetooth_on_window_load, NULL, bluetooth_on_window_unload},
    {weather_init, weather_on_window_load, NULL, weather_on_window_unload},
    {timeline_peek_init, timeline_peek_on_window_load, NULL, timeline_peek_on_window_unload},
};

static const int s_module_count = ARRAY_LENGTH(s_modules);

#endif //PIXY_WATCHFACE_WATCHFACE_MODULES
