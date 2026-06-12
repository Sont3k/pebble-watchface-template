#include "main_window.h"

#include "modules/app_message/app_message.h"
#include "modules/time/time.h"
#include "settings/clay_settings.h"
#include "watchface_modules.h"

Window *s_main_window;

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

    // Subscribe for app tick
    tick_timer_service_subscribe(MINUTE_UNIT, main_window_tick_handler);

    // Init Modules
    for (int i = 0; i < s_module_count; i++) {
        if (s_modules[i].init) {
            s_modules[i].init();
        }
    }
}

void main_window_load(Window *window) {
    // Get information about the Window
    Layer *window_layer = window_get_root_layer(window);
    GRect bounds = layer_get_bounds(window_layer);

    // Load Modules
    for (int i = 0; i < s_module_count; i++) {
        if (s_modules[i].load) {
            s_modules[i].load(window, window_layer, bounds);
        }
    }

    prv_update_display();
}

void main_window_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    // Handle Tick For Modules
    for (int i = 0; i < s_module_count; i++) {
        if (s_modules[i].tick) {
            s_modules[i].tick(tick_time, units_changed);
        }
    }
}

void main_window_unload(Window *window) {
    // Unload Modules
    for (int i = 0; i < s_module_count; i++) {
        if (s_modules[i].unload) {
            s_modules[i].unload(window);
        }
    }
}

void main_window_destroy() {
    window_destroy(s_main_window);
}