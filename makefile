SOURCE_FILES=\
sources/character.c \
sources/characters.c \
sources/commands.c \
sources/drop.c \
sources/events.c \
sources/go.c \
sources/hold.c \
sources/initialize.c \
sources/input.c \
sources/inventory.c \
sources/items.c \
sources/lexicon.c \
sources/locations.c \
sources/look.c \
sources/main.c \
sources/play.c \
sources/rng.c \
sources/save.c \
sources/take.c \
sources/use.c

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
twenty_squares/sources/twenty_squares_ability.c \
twenty_squares/sources/twenty_squares_board.c \
twenty_squares/sources/twenty_squares_cells.c \
twenty_squares/sources/twenty_squares_main.c \
twenty_squares/sources/twenty_squares_movement.c \
twenty_squares/sources/twenty_squares_players.c \
twenty_squares/sources/twenty_squares_selection.c \
twenty_squares/sources/twenty_squares_turn.c

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

# Package: mingw-w64
# 32-bit Windows executable: i686-w64-mingw32-gcc -o persistence.exe $(SOURCE_FILES) $(HEADER_FILES) $(TWENTY_SQUARES_SOURCE_FILES) $(TWENTY_SQUARES_HEADER_FILES)
# 64-bit Windows executable: x86_64-w64-mingw32-gcc -o persistence.exe $(SOURCE_FILES) $(HEADER_FILES) $(TWENTY_SQUARES_SOURCE_FILES) $(TWENTY_SQUARES_HEADER_FILES)

