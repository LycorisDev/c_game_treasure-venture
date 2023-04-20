#ifndef EVENTS_H
#define EVENTS_H

#ifndef STANDARD_LIBRARY_STRING
#define STANDARD_LIBRARY_STRING
#include <string.h>
#endif

#include "main.h"
#include "game.h"

#define NBR_EVENTS 	10
#define FLAG_ON 	1
#define FLAG_OFF 	0

extern int list_events[NBR_EVENTS];

void populate_list_events(void);
void execute_event_first_time_player_enters_mansion(void);
void event_first_time_player_enters_mansion(void);
void execute_event_player_finds_entry_doors_key(void);
void event_player_finds_entry_doors_key(const int id_item);

#endif

