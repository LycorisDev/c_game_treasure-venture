#ifndef EVENTS_H
#define EVENTS_H

#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif

void populate_list_events(void);

#define NBR_EVENTS 	10
#define FLAG_ON 	1
#define FLAG_OFF 	0

extern int list_events[NBR_EVENTS];

/* Used in go.c and use.c --------------------------------------------------------- */

#define EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME  \
    if (PLAYER->current_location == LOCATION_MAIN_HALLWAY && list_events[0] == FLAG_ON)\
    {\
        ITEM_ENTRY_DOORS->access = ACCESS_LOCKED;\
        printf("A distinct noise lets you know the entry doors have locked, seemingly all by themselves. You hope this is no haunting place. ");\
        list_events[0] = FLAG_OFF;\
    }

/* Used in go.c and look.c -------------------------------------------------------- */

#define EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY(item_id)  \
    if (item_id == ID_ITEM_ENTRY_DOORS_KEY && list_events[1] == FLAG_ON)\
    {\
        memcpy(ITEM_ENTRY_DOORS_KEY->description_obvious, "A key is left unattended on the ground.", LENGTH_DESCRIPTION);\
        memcpy(ITEM_ENTRY_DOORS_KEY->description_detailed, "The key shines in a golden color, and a small note attached to it with a string reads \"Entry\".", LENGTH_DESCRIPTION);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[0], "key / entry doors key / double doors key / main doors key / main entry doors key / main double doors key", LENGTH_NAME);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[1], "key", LENGTH_NAME);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[2], "entry doors key", LENGTH_NAME);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[3], "double doors key", LENGTH_NAME);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[4], "main doors key", LENGTH_NAME);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[5], "main entry doors key", LENGTH_NAME);\
        memcpy(ITEM_ENTRY_DOORS_KEY->tags[6], "main double doors key", LENGTH_NAME);\
        list_events[1] = FLAG_OFF;\
    }

#endif

