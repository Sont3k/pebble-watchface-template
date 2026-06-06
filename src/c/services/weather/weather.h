#ifndef WATCHFACE_WEATHER_H
#define WATCHFACE_WEATHER_H

#include <pebble.h>

extern TextLayer *s_weather_layer;

void weather_on_window_load(Window *window, Layer *window_layer, GRect bounds);
void weather_on_window_unload(Window *window);

#endif //WATCHFACE_WEATHER_H