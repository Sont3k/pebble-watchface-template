#ifndef WATCHFACE_TIMELINE_PEEK_H
#define WATCHFACE_TIMELINE_PEEK_H

#include <pebble.h>

void timeline_peek_init();

void timeline_peek_on_window_load(Window *window, Layer *window_layer, GRect bounds);
void timeline_peek_on_window_unload(Window *window);

void prv_unobstructed_will_change(GRect final_unobstructed_screen_area, void * context);
void prv_unobstructed_change(AnimationProgress progress, void * context);
void prv_unobstructed_did_change(void * context);

#endif //WATCHFACE_TIMELINE_PEEK_H
