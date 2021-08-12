#include "../headers/events.h"

/* Declared as extern in ../headers/events.h */
int list_events[NBR_EVENTS];

void populate_list_events(void)
{
    memset(list_events, 0, sizeof(list_events));
    return;
}

