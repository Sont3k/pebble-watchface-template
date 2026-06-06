#ifndef WATCHFACE_BLUETOOTH_H
#define WATCHFACE_BLUETOOTH_H

#include <pebble.h>

extern BitmapLayer *s_bt_icon_layer;

void bluetooth_init();

void bluetooth_on_window_load(Window *window, Layer *window_layer, GRect bounds);
void bluetooth_on_window_unload(Window *window);

void bluetooth_callback(bool connected);

#endif //WATCHFACE_BLUETOOTH_H