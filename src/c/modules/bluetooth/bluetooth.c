#include "bluetooth.h"

BitmapLayer *s_bt_icon_layer;
static GBitmap *s_bt_icon_bitmap;

void bluetooth_init() {
    // Register for Bluetooth connection updates
    connection_service_subscribe((ConnectionHandlers) {
      .pebble_app_connection_handler = bluetooth_callback
    });
}

void bluetooth_on_window_load(Window *window, Layer *window_layer, GRect bounds) {
    // Create the Bluetooth icon GBitmap
    s_bt_icon_bitmap = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_BT_ICON);

    // Create the BitmapLayer to display the GBitmap - below the battery bar, centered
    int battery_bar_y = PBL_IF_ROUND_ELSE(bounds.size.h / 8, bounds.size.h / 28);
    int bt_y = battery_bar_y + 12;
    s_bt_icon_layer = bitmap_layer_create(GRect((bounds.size.w -30) / 2, bt_y, 30, 30));
    bitmap_layer_set_bitmap(s_bt_icon_layer, s_bt_icon_bitmap);
    bitmap_layer_set_compositing_mode(s_bt_icon_layer, GCompOpSet);

    // Add to Window
    layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_bt_icon_layer));

    // Show the correct state of the BT connection from the start
    bluetooth_callback(connection_service_peek_pebble_app_connection());
}

void bluetooth_on_window_unload(Window *window) {
    gbitmap_destroy(s_bt_icon_bitmap);
    bitmap_layer_destroy(s_bt_icon_layer);
}

void bluetooth_callback(bool connected) {
    // Show icon if disconnected
    layer_set_hidden(bitmap_layer_get_layer(s_bt_icon_layer), connected);

    if (!connected) {
        // Issue a vibrating alert
        vibes_double_pulse();
    }
}
