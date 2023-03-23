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

app: $(SOURCE_FILES) $(HEADER_FILES)
	@gcc -ansi -pedantic -Wall -Wextra -o builds/app $(SOURCE_FILES) $(HEADER_FILES)

# Package: mingw-w64
# 32-bit Windows executable: i686-w64-mingw32-gcc -o builds/TreasureVenture.exe $(SOURCE_FILES) $(HEADER_FILES)
# 64-bit Windows executable: x86_64-w64-mingw32-gcc -o builds/TreasureVenture.exe $(SOURCE_FILES) $(HEADER_FILES)

