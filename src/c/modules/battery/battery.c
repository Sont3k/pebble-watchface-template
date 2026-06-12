#include "battery.h"
#include "../../settings/clay_settings.h"

Layer *s_battery_layer;
static int s_battery_level;

void battery_init() {
    // Register for battery level updates
    battery_state_service_subscribe(battery_callback);

    // Ensure battery level is displayed from the start
    battery_callback(battery_state_service_peek());
}

void battery_on_window_load(Window *window, Layer *window_layer, GRect bounds) {
    // Create battery meter layer - visible bar near the top
    int bar_width = bounds.size.w / 2;
    int bar_x = (bounds.size.w - bar_width) / 2;
    int bar_y = PBL_IF_ROUND_ELSE(bounds.size.h / 8, bounds.size.h / 28);
    s_battery_layer = layer_create(GRect(bar_x, bar_y, bar_width, 8));
    layer_set_update_proc(s_battery_layer, battery_update_proc);

    // Add to Window
    layer_add_child(window_layer, s_battery_layer);
}

void battery_on_window_unload(Window *window) {
    layer_destroy(s_battery_layer);
}

void battery_update_proc(Layer *layer, GContext *ctx) {
    GRect bounds = layer_get_bounds(layer);

    // Find the width of the bar (inside the border)
    int bar_width = s_battery_level * (bounds.size.w - 4) / 100;

    // Draw the border
    graphics_context_set_stroke_color(ctx, settings.TextColor);
    graphics_draw_round_rect(ctx, bounds, 2);

    // Choose color based on battery level
    GColor bar_color;
    if (s_battery_level <= 20) {
        bar_color = PBL_IF_COLOR_ELSE(GColorRed, settings.TextColor);
    } else if (s_battery_level <= 40) {
        bar_color = PBL_IF_COLOR_ELSE(GColorChromeYellow, settings.TextColor);
    } else {
        bar_color = PBL_IF_COLOR_ELSE(GColorGreen, settings.TextColor);
    }

    // Draw the filled bar inside the border
    graphics_context_set_fill_color(ctx, bar_color);
    graphics_fill_rect(ctx, GRect(2, 2, bar_width, bounds.size.h - 4), 1, GCornerNone);
}

void battery_callback(BatteryChargeState state) {
    // Record the new battery level
    s_battery_level = state.charge_percent;

    // Update the meter
    layer_mark_dirty(s_battery_layer);
}
