#ifndef WATCHFACE_BATTERY_H
#define WATCHFACE_BATTERY_H
#include <pebble.h>

extern Layer *s_battery_layer;

void battery_init();

void battery_on_window_load(Window *window, Layer *window_layer, GRect bounds);
void battery_on_window_unload(Window *window);

void battery_update_proc(Layer *layer, GContext *ctx);
void battery_callback(BatteryChargeState state);

#endif //WATCHFACE_BATTERY_H