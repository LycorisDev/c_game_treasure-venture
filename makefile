SOURCE_FILES=\
source/character.c \
source/characters.c \
source/commands.c \
source/drop.c \
source/events.c \
source/go.c \
source/hold.c \
source/initialize.c \
source/input.c \
source/inventory.c \
source/items.c \
source/lexicon.c \
source/locations.c \
source/look.c \
source/main.c \
source/play.c \
source/rng.c \
source/save.c \
source/take.c \
source/use.c

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
twenty_squares/source/twenty_squares_ability.c \
twenty_squares/source/twenty_squares_board.c \
twenty_squares/source/twenty_squares_cells.c \
twenty_squares/source/twenty_squares_main.c \
twenty_squares/source/twenty_squares_movement.c \
twenty_squares/source/twenty_squares_players.c \
twenty_squares/source/twenty_squares_selection.c \
twenty_squares/source/twenty_squares_turn.c

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

