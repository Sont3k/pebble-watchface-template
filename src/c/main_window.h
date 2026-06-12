#ifndef WATCHFACE_MAIN_WINDOW_H
#define WATCHFACE_MAIN_WINDOW_H

#include <pebble.h>

extern Window *s_main_window;

void main_window_init();
void main_window_load(Window *window);
void main_window_tick_handler(struct tm * tick_time, TimeUnits units_changed);
void main_window_unload(Window *window);
void main_window_destroy();

#endif //WATCHFACE_MAIN_WINDOW_H
