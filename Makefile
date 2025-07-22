CC = gcc
CFLAGS = -fPIC -MMD -Iinclude -Wall -Wextra -pedantic -g
TS_LIB = -lts
DIR_BUILD = build
DIR_OBJ = $(DIR_BUILD)/unix/objects
EXE = $(DIR_BUILD)/unix/treasure-venture
SRC_FILES = $(shell find src -name '*.c')
OBJ_FILES = $(patsubst src/%.c, $(DIR_OBJ)/%.o, $(SRC_FILES))

all: $(EXE)

$(EXE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ -O2 -Lplugin/20SQ $(TS_LIB)

$(DIR_OBJ)/%.o: src/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
-include $(DIR_OBJ)/%.d

.PHONY: fclean re win64 win32

fclean:
	rm -rf $(DIR_BUILD)

re: fclean
	make -s all

# Package: gcc-mingw-w64
win64:
	$(MAKE) CC=x86_64-w64-mingw32-gcc TS_LIB=-lts64 \
	DIR_OBJ=$(DIR_BUILD)/win64/objects \
	EXE=$(DIR_BUILD)/win64/TreasureVenture-64bit.exe
win32:
	$(MAKE) CC=i686-w64-mingw32-gcc TS_LIB=-lts32 \
	DIR_OBJ=$(DIR_BUILD)/win32/objects \
	EXE=$(DIR_BUILD)/win32/TreasureVenture-32bit.exe
