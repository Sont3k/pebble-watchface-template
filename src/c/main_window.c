#include "main_window.h"

#include "services/app_message/app_message.h"
#include "services/time/time.h"
#include "services/battery/battery.h"
#include "services/bluetooth/bluetooth.h"
#include "services/timeline_peek/timeline_peek.h"
#include "services/weather/weather.h"
#include "settings/clay_settings.h"

Window *s_main_window;

void main_window_load(Window *window) {
    // Get information about the Window
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    time_on_window_load(window, window_layer, bounds);
    battery_on_window_load(window, window_layer, bounds);
    bluetooth_on_window_load(window, window_layer, bounds);
    weather_on_window_load(window, window_layer, bounds);
    timeline_peek_on_window_load(window, window_layer, bounds);

    prv_update_display();
}

void main_window_unload(Window *window) {
    time_on_window_unload(window);
    battery_on_window_unload(window);
    bluetooth_on_window_unload(window);
    weather_on_window_unload(window);
    timeline_peek_on_window_unload(window);
}

void main_window_init() {
    prv_load_settings();

    // Create main Window element and assign to pointer
    s_main_window = window_create();

    // Set the background color
    window_set_background_color(s_main_window, GColorBlack);

    // Set handlers to manage the elements inside the Window
    window_set_window_handlers(s_main_window, (WindowHandlers) {
      .load = main_window_load,
      .unload = main_window_unload
    });

    // Show the Window on the watch, with animated=true
    window_stack_push(s_main_window, true);

    // Make sure the time is displayed from the start
    update_time();

    time_init();
    battery_init();
    bluetooth_init();
    app_message_init();
    timeline_peek_init();
}

void main_window_deinit() {
    // Destroy Window
    window_destroy(s_main_window);
}