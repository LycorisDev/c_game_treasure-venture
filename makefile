SOURCE_FILES=\
character.c \
characters.c \
commands.c \
drop.c \
go.c \
hold.c \
initialize.c \
input.c \
inventory.c \
items.c \
lexicon.c \
locations.c \
look.c \
main.c \
play.c \
rng.c \
save.c \
take.c \
use.c

HEADER_FILES=\
headers/character.h \
headers/characters.h \
headers/commands.h \
headers/drop.h \
headers/events.h \
headers/game.h \
headers/go.h \
headers/hold.h \
headers/initialize.h \
headers/input.h \
headers/inventory.h \
headers/items.h \
headers/lexicon.h \
headers/locations.h \
headers/look.h \
headers/main.h \
headers/play.h \
headers/rng.h \
headers/save.h \
headers/take.h \
headers/use.h

TWENTY_SQUARES_SOURCE_FILES=\
twenty_squares/twenty_squares_ability.c \
twenty_squares/twenty_squares_board.c \
twenty_squares/twenty_squares_cells.c \
twenty_squares/twenty_squares_main.c \
twenty_squares/twenty_squares_movement.c \
twenty_squares/twenty_squares_players.c \
twenty_squares/twenty_squares_selection.c \
twenty_squares/twenty_squares_turn.c

TWENTY_SQUARES_HEADER_FILES=\
twenty_squares/headers/twenty_squares.h \
twenty_squares/headers/twenty_squares_ability.h \
twenty_squares/headers/twenty_squares_board.h \
twenty_squares/headers/twenty_squares_cells.h \
twenty_squares/headers/twenty_squares_main.h \
twenty_squares/headers/twenty_squares_movement.h \
twenty_squares/headers/twenty_squares_players.h \
twenty_squares/headers/twenty_squares_selection.h \
twenty_squares/headers/twenty_squares_turn.h

rpg: $(SOURCE_FILES) $(HEADER_FILES) $(TWENTY_SQUARES_SOURCE_FILES) $(TWENTY_SQUARES_HEADER_FILES)
	@gcc -ansi -pedantic -Wall -Wextra -o rpg $(SOURCE_FILES) $(HEADER_FILES) $(TWENTY_SQUARES_SOURCE_FILES) $(TWENTY_SQUARES_HEADER_FILES)

