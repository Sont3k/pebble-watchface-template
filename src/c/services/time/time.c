#include "time.h"

TextLayer *s_time_layer;
static GFont s_time_font;

TextLayer *s_date_layer;
static GFont s_date_font;

void time_init() {
    // Register with TickTimerService
    tick_timer_service_subscribe(MINUTE_UNIT, time_tick_handler);
}

void time_on_window_load(Window *window, Layer *window_layer, GRect bounds) {
    // Load custom fonts
    s_time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXELIFY_SANS_REGULAR_24));
    s_date_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXELIFY_SANS_REGULAR_24));

    // Center the time + date block vertically
    int date_height = 30;
    int block_height = 56 + date_height;
    int time_y = (bounds.size.h / 2) - (block_height / 2) - 10;
    int date_y = time_y + 56;

    // Create the time TextLayer
    s_time_layer = text_layer_create(GRect(0, time_y, bounds.size.w, 60));
    text_layer_set_background_color(s_time_layer, GColorClear);
    text_layer_set_text_color(s_time_layer, GColorWhite);
    text_layer_set_font(s_time_layer, s_time_font);
    text_layer_set_text_alignment(s_time_layer, GTextAlignmentCenter);

    // Add it as a child layer to the Window's root layer
    layer_add_child(window_layer, text_layer_get_layer(s_time_layer));

    // Create the date TextLayer
    s_date_layer = text_layer_create(
        GRect(0, date_y, bounds.size.w, 30));
    text_layer_set_background_color(s_date_layer, GColorClear);
    text_layer_set_text_color(s_date_layer, GColorWhite);
    text_layer_set_font(s_date_layer, s_date_font);
    text_layer_set_text_alignment(s_date_layer, GTextAlignmentCenter);

    // Add to Window
    layer_add_child(window_layer, text_layer_get_layer(s_date_layer));
}

void time_on_window_unload(Window *window) {
    text_layer_destroy(s_time_layer);
    text_layer_destroy(s_date_layer);

    // Unload custom fonts
    fonts_unload_custom_font(s_time_font);
    fonts_unload_custom_font(s_date_font);
}

void update_time() {
    // Get a tm structure
    time_t temp = time(NULL);
    struct tm *tick_time = localtime(&temp);

    // Write the current hours and minutes into a buffer
    static char s_time_buffer[8];
    strftime(s_time_buffer, sizeof(s_time_buffer), clock_is_24h_style() ? "%H:%M" : "%I:%M", tick_time);

    // Display this time on the TextLayer
    text_layer_set_text(s_time_layer, s_time_buffer);

    // Write the current date into a buffer
    static char s_date_buffer[16];
    strftime(s_date_buffer, sizeof(s_date_buffer), "%a %b %d", tick_time);

    // Display the date
    text_layer_set_text(s_date_layer, s_date_buffer);
}

void time_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    update_time();
}
