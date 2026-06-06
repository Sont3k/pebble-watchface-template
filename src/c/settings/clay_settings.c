#include "clay_settings.h"

#include "../main_window.h"
#include "../services/battery/battery.h"
#include "../services/time/time.h"
#include "../services/weather/weather.h"

ClaySettings settings;

void prv_default_settings() {
    settings.BackgroundColor = GColorBlack;
    settings.TextColor = GColorWhite;
    settings.TemperatureUnit = false;
    settings.ShowDate = true;
}

void prv_save_settings() {
    persist_write_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void prv_load_settings() {
    prv_default_settings();
    persist_read_data(SETTINGS_KEY, &settings, sizeof(settings));
}

void prv_update_display() {
    window_set_background_color(s_main_window, settings.BackgroundColor);

    text_layer_set_text_color(s_time_layer, settings.TextColor);
    text_layer_set_text_color(s_date_layer, settings.TextColor);
    text_layer_set_text_color(s_weather_layer, settings.TextColor);

    // Show/hide date based on setting
    layer_set_hidden(text_layer_get_layer(s_date_layer), !settings.ShowDate);

    layer_mark_dirty(s_battery_layer);
}