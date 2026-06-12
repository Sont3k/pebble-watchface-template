#include "app_message.h"
#include "../weather/weather.h"
#include "../../settings/clay_settings.h"

void app_message_init(void) {
    // Register AppMessage callbacks
    app_message_register_inbox_received(inbox_received_callback);
    app_message_register_inbox_dropped(inbox_dropped_callback);
    app_message_register_outbox_failed(outbox_failed_callback);
    app_message_register_outbox_sent(outbox_sent_callback);

    // Open AppMessage
    const int inbox_size = 256;
    const int outbox_size = 256;
    app_message_open(inbox_size, outbox_size);
}

void inbox_received_callback(DictionaryIterator *iterator, void *context) {
    // Check for weather data
    Tuple *temp_tuple = dict_find(iterator, MESSAGE_KEY_TEMPERATURE);
    Tuple *conditions_tuple = dict_find(iterator, MESSAGE_KEY_CONDITIONS);

    if (temp_tuple && conditions_tuple) {
        static char temperature_buffer[8];
        static char conditions_buffer[32];
        static char weather_layer_buffer[42];

        int temp_value = (int)temp_tuple->value->int32;

        // Convert to Fahrenheit if setting is enabled
        if (settings.TemperatureUnit) {
            temp_value = (temp_value * 9 / 5) + 32;
            snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°F", temp_value);
        } else {
            snprintf(temperature_buffer, sizeof(temperature_buffer), "%d°C", temp_value);
        }

        snprintf(conditions_buffer, sizeof(conditions_buffer), "%s", conditions_tuple->value->cstring);
        snprintf(weather_layer_buffer, sizeof(weather_layer_buffer), "%s %s", temperature_buffer, conditions_buffer);
        text_layer_set_text(s_weather_layer, weather_layer_buffer);
    }

    // Check for Clay settings
    Tuple *bg_color_t = dict_find(iterator, MESSAGE_KEY_BackgroundColor);
    if (bg_color_t) {
        settings.BackgroundColor = GColorFromHEX(bg_color_t->value->int32);
    }

    Tuple *text_color_t = dict_find(iterator, MESSAGE_KEY_TextColor);
    if (text_color_t) {
        settings.TextColor = GColorFromHEX(text_color_t->value->int32);
    }

    Tuple *temp_unit_t = dict_find(iterator, MESSAGE_KEY_TemperatureUnit);
    if (temp_unit_t) {
        settings.TemperatureUnit = temp_unit_t->value->int32 == 1;
    }

    Tuple *show_date_t = dict_find(iterator, MESSAGE_KEY_ShowDate);
    if (show_date_t) {
        settings.ShowDate = show_date_t->value->int32 == 1;
    }

    // Save and apply if any settings were changed
    if (bg_color_t || text_color_t || temp_unit_t || show_date_t) {
        prv_save_settings();
        prv_update_display();

        // Refetch weather if the temperature unit changed so the display updates
        if (temp_unit_t) {
            DictionaryIterator *iter;
            app_message_outbox_begin(&iter);
            dict_write_uint8(iter, MESSAGE_KEY_REQUEST_WEATHER, 1);
            app_message_outbox_send();
        }
    }
}

void inbox_dropped_callback(AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Message dropped!");
}

void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Outbox send failed!");
}

void outbox_sent_callback(DictionaryIterator *iterator, void *context) {
    APP_LOG(APP_LOG_LEVEL_INFO, "Outbox send success!");
}

void app_message_tick_handler(struct tm *tick_time, TimeUnits units_changed) {
    // Get weather update every 30 minutes
    if (tick_time->tm_min % 30 == 0) {
        DictionaryIterator *iter;
        app_message_outbox_begin(&iter);
        dict_write_uint8(iter, MESSAGE_KEY_REQUEST_WEATHER, 1);
        app_message_outbox_send();
    }
}
