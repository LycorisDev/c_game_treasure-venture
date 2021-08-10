#ifndef EVENTS_H
#define EVENTS_H

#define NBR_EVENTS 	100
#define FLAG_ON 	0
#define FLAG_OFF 	1

extern int list_events[NBR_EVENTS];

/* Used in go.c and use.c --------------------------------------------------------- */

#define EVENT_PLAYER_ENTERS_MANSION_FOR_THE_FIRST_TIME    if (list_events[0] == FLAG_ON && PLAYER->current_location == LOCATION_MAIN_HALLWAY)\
                                                          {\
                                                              ITEM_ENTRY_DOORS->access = ACCESS_LOCKED;\
                                                              list_events[0] = FLAG_OFF;\
                                                          }

/* -------------------------------------------------------------------------------- */

/* Used in items.c --------------------------- Flag turned off in look.c and take.c */

#define EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY_1_ON_3         if (list_events[1] == FLAG_ON)\
                                                          {\
                                                              return "shiny thing";\
                                                          }\
                                                          else\
                                                          {\
                                                              return "key";\
                                                          }

                                                          /* It requires an "if" or "else if" in front of it */
#define EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY_2_ON_3         (list_events[1] == FLAG_ON && strcmp(parser, "shiny thing") == 0)\
                                                          {\
                                                              return ID_ITEM_ENTRY_DOORS_KEY;\
                                                          }\
                                                          else if (list_events[1] == FLAG_OFF && (strcmp(parser, "entry doors key") == 0 || strcmp(parser, "key") == 0))\
                                                          {\
                                                              return ID_ITEM_ENTRY_DOORS_KEY;\
                                                          }



#define EVENT_PLAYER_FINDS_ENTRY_DOORS_KEY_3_ON_3         if (list_events[1] == FLAG_ON && strcmp(parser, "shiny thing") == 0)\
                                                          {\
                                                              return 1;\
                                                          }\
                                                          else if (list_events[1] == FLAG_OFF && (strcmp(parser, "entry doors key") == 0 || strcmp(parser, "key") == 0))\
                                                          {\
                                                              return 1;\
                                                          }\
                                                          else\
                                                          {\
                                                              return 0;\
                                                          }

/* -------------------------------------------------------------------------------- */
#endif

