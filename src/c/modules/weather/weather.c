#include "weather.h"

TextLayer *s_weather_layer;

void weather_init() {

}

static GFont s_weather_font;

void weather_on_window_load(Window *window, Layer *window_layer, GRect bounds) {
    // Create weather TextLayer - aligned to the bottom fo the screen
    int weather_y = bounds.size.h - PBL_IF_ROUND_ELSE(40, 30);

    s_weather_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_PIXELIFY_SANS_REGULAR_18));

    s_weather_layer = text_layer_create(GRect(0, weather_y, bounds.size.w, 25));
    text_layer_set_background_color(s_weather_layer, GColorClear);
    text_layer_set_text_color(s_weather_layer, GColorWhite);
    text_layer_set_font(s_weather_layer, s_weather_font);
    text_layer_set_text_alignment(s_weather_layer, GTextAlignmentCenter);
    text_layer_set_text(s_weather_layer, "Loading...");

    layer_add_child(window_layer, text_layer_get_layer(s_weather_layer));
}

void weather_on_window_unload(Window *window) {
    text_layer_destroy(s_weather_layer);
}
