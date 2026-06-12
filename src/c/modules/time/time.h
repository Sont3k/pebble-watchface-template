#ifndef WATCHFACE_TIME_H
#define WATCHFACE_TIME_H

#include <pebble.h>

typedef struct {
    int time_height;
    int date_height;
    int time_date_gap;
    int y_offset;
} TimeLayoutStyle;

extern TextLayer *s_time_layer;
extern TextLayer *s_date_layer;

void time_init();
void time_on_window_load(Window *window, Layer *window_layer, GRect bounds);
void time_on_window_unload(Window *window);

void time_tick_handler(struct tm *tick_time, TimeUnits units_changed);
void update_time();

void time_relayout(GRect bounds);
int time_get_bottom_y(void);

#endif //WATCHFACE_TIME_H