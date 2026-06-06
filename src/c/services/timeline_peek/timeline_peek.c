#include "timeline_peek.h"
#include "../bluetooth/bluetooth.h"
#include "../time/time.h"
#include "../weather/weather.h"

static Layer *s_window_layer;

void timeline_peek_init() {
    // Apply correct layout in case Quick View is already active
    prv_unobstructed_change(0, NULL);
    prv_unobstructed_did_change(NULL);
}

void timeline_peek_on_window_load(Window *window, Layer *window_layer, GRect bounds) {
    s_window_layer = window_layer;

    UnobstructedAreaHandlers handlers = {
        .will_change = prv_unobstructed_will_change,
        .change = prv_unobstructed_change,
        .did_change = prv_unobstructed_did_change
    };
    unobstructed_area_service_subscribe(handlers, NULL);
}

void timeline_peek_on_window_unload(Window *window) {
}

void prv_unobstructed_will_change(GRect final_unobstructed_screen_area, void * context) {
    // Hide BT icon during the transition to reduce clutter
    layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), true);
}

void prv_unobstructed_change(AnimationProgress progress, void * context) {
    GRect bounds = layer_get_unobstructed_bounds(s_window_layer);

    // Reposition time, date, and weather to fit in the available space
    int date_height = 30;
    int block_height = 56 + date_height;
    int time_y = (bounds.size.h / 2) - (block_height / 2) - 10;
    int date_y = time_y + 56;
    int weather_y = bounds.size.h - PBL_IF_ROUND_ELSE(40, 30);

    GRect time_frame = layer_get_frame(text_layer_get_layer(s_time_layer));
    time_frame.origin.y = time_y;
    layer_set_frame(text_layer_get_layer(s_time_layer), time_frame);

    GRect date_frame = layer_get_frame(text_layer_get_layer(s_date_layer));
    date_frame.origin.y = date_y;
    layer_set_frame(text_layer_get_layer(s_date_layer), date_frame);

    GRect weather_frame = layer_get_frame(text_layer_get_layer(s_weather_layer));
    weather_frame.origin.y = weather_y;
    layer_set_frame(text_layer_get_layer(s_weather_layer), weather_frame);
}

void prv_unobstructed_did_change(void * context) {
    GRect full_bounds = layer_get_bounds(s_window_layer);
    GRect bounds = layer_get_unobstructed_bounds(s_window_layer);
    bool obstructed = !grect_equal(&full_bounds, &bounds);

    // Keep BT icon hidden when obstructed, otherwise restore based on connection
    if (obstructed) {
        layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), true);
    } else {
        layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer),
            connection_service_peek_pebble_app_connection());
    }
}
