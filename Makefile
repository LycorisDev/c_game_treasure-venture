CC = gcc
CFLAGS = -Iinclude -Wall -Wextra -pedantic -g
LDFLAGS = -O2
DIR_20SQ = plugin/20SQ
DIR_BUILD = build
DIR_OBJ = $(DIR_BUILD)/unix/objects
BIN = $(DIR_BUILD)/unix/treasure_venture
SRC_FILES = $(shell find src -name '*.c')
OBJ_FILES = $(patsubst src/%.c, $(DIR_OBJ)/%.o, $(SRC_FILES))

all: $(BIN)

$(BIN): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(DIR_OBJ)/%.o: src/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@
-include $(DIR_OBJ)/%.d

.PHONY: all 20SQ win64 win32 clean clean-unix clean-win64 clean-win32 fclean 
.PHONY: fclean-unix fclean-win64 fclean-win32 re re-win64 re-win32

20SQ:
	@mkdir -p $(DIR_20SQ)
	@git clone --quiet https://github.com/LycorisDev/c_game_twenty-squares.git
	@$(MAKE) -s -C c_game_twenty-squares
	@cp c_game_twenty-squares/build/unix/lib20SQ.so $(DIR_20SQ)/.
	@$(MAKE) -s win64 -C c_game_twenty-squares
	@cp c_game_twenty-squares/build/win64/lib20SQ64.dll $(DIR_20SQ)/.
	@$(MAKE) -s win32 -C c_game_twenty-squares
	@cp c_game_twenty-squares/build/win32/lib20SQ32.dll $(DIR_20SQ)/.
	@rm -rf c_game_twenty-squares
	@echo "Twenty Squares plugin downloaded in $(DIR_20SQ)!"

# Package: gcc-mingw-w64
win64:
	$(MAKE) all \
	CC=x86_64-w64-mingw32-gcc \
	DIR_OBJ=$(DIR_BUILD)/win64/objects \
	BIN=$(DIR_BUILD)/win64/TreasureVenture-64bit.exe
win32:
	$(MAKE) all \
	CC=i686-w64-mingw32-gcc \
	DIR_OBJ=$(DIR_BUILD)/win32/objects \
	BIN=$(DIR_BUILD)/win32/TreasureVenture-32bit.exe

clean:
	$(MAKE) clean-unix
	$(MAKE) clean-win64
	$(MAKE) clean-win32
clean-unix:
	rm -rf $(DIR_BUILD)/unix/objects
clean-win64:
	rm -rf $(DIR_BUILD)/win64/objects
clean-win32:
	rm -rf $(DIR_BUILD)/win32/objects

fclean:
	$(MAKE) fclean-unix
	$(MAKE) fclean-win64
	$(MAKE) fclean-win32
fclean-unix:
	rm -rf $(DIR_BUILD)/unix
fclean-win64:
	rm -rf $(DIR_BUILD)/win64
fclean-win32:
	rm -rf $(DIR_BUILD)/win32

re: fclean-unix all

re-win64: fclean-win64 win64

re-win32: fclean-win32 win32
