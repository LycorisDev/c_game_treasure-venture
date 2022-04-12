#include "../headers/events.h"

/* Declared as extern in ../headers/events.h */
int list_events[NBR_EVENTS];

void populate_list_events(void)
{
    memset(list_events, FLAG_OFF, sizeof(list_events));
    list_events[0] = FLAG_ON;
    list_events[1] = FLAG_ON;
    return;
}

