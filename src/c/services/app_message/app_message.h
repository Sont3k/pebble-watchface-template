#ifndef WATCHFACE_APP_MESSAGE_H
#define WATCHFACE_APP_MESSAGE_H

#include <pebble.h>

void app_message_init(void);

void inbox_received_callback(DictionaryIterator *iterator, void *context);
void inbox_dropped_callback(AppMessageResult reason, void *context);
void outbox_failed_callback(DictionaryIterator *iterator, AppMessageResult reason, void *context);
void outbox_sent_callback(DictionaryIterator *iterator, void *context);

void app_message_tick_handler(struct tm *tick_time, TimeUnits units_changed);

#endif //WATCHFACE_APP_MESSAGE_H
