#ifndef WATCHFACE_TIME_H
#define WATCHFACE_TIME_H

#include <pebble.h>

extern TextLayer *s_time_layer;
extern TextLayer *s_date_layer;

void time_init();

void time_on_window_load(Window *window, Layer *window_layer, GRect bounds);
void time_on_window_unload(Window *window);

void update_time();
void time_tick_handler(struct tm *tick_time, TimeUnits units_changed);

#endif //WATCHFACE_TIME_H