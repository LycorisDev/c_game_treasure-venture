CC = gcc
CFLAGS = -O2 -Iinclude -Wall -Wextra -pedantic -g
DIR_20SQ = plugin/20SQ
DIR_BUILD = build
DIR_OBJ = $(DIR_BUILD)/linux/objects
BIN_NAME = treasure_venture
BIN_NAME_WIN = TreasureVenture.exe
BIN = $(DIR_BUILD)/linux/$(BIN_NAME)
SRC = $(shell find src -name '*.c')
OBJ = $(patsubst %.c, $(DIR_OBJ)/%.o, $(SRC))

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@

$(DIR_OBJ)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all 20SQ win64 win32 clean clean-linux clean-win64 clean-win32 fclean 
.PHONY: fclean-linux fclean-win64 fclean-win32 re re-win64 re-win32

20SQ:
	@mkdir -p $(DIR_20SQ)
	@git clone --quiet https://github.com/LycorisDev/c_game_twenty-squares.git
	@$(MAKE) -s -C c_game_twenty-squares
	@cp c_game_twenty-squares/build/linux/lib20SQ.so $(DIR_20SQ)/.
	@$(MAKE) -s win64 -C c_game_twenty-squares
	@cp c_game_twenty-squares/build/win64/lib20SQ64.dll $(DIR_20SQ)/.
	@$(MAKE) -s win32 -C c_game_twenty-squares
	@cp c_game_twenty-squares/build/win32/lib20SQ32.dll $(DIR_20SQ)/.
	@rm -rf c_game_twenty-squares
	@echo "Twenty Squares plugin downloaded in $(DIR_20SQ)!"

# Package: gcc-mingw-w64
win64:
	@$(MAKE) --no-print-directory all \
	CC=x86_64-w64-mingw32-gcc \
	DIR_OBJ=$(DIR_BUILD)/win64/objects \
	BIN=$(DIR_BUILD)/win64/$(BIN_NAME_WIN)
win32:
	@$(MAKE) --no-print-directory all \
	CC=i686-w64-mingw32-gcc \
	DIR_OBJ=$(DIR_BUILD)/win32/objects \
	BIN=$(DIR_BUILD)/win32/$(BIN_NAME_WIN)

clean:
	@$(MAKE) --no-print-directory clean-linux
	@$(MAKE) --no-print-directory clean-win64
	@$(MAKE) --no-print-directory clean-win32
clean-linux:
	rm -rf $(DIR_BUILD)/linux/objects
clean-win64:
	rm -rf $(DIR_BUILD)/win64/objects
clean-win32:
	rm -rf $(DIR_BUILD)/win32/objects

fclean:
	@$(MAKE) --no-print-directory fclean-linux
	@$(MAKE) --no-print-directory fclean-win64
	@$(MAKE) --no-print-directory fclean-win32
fclean-linux: clean-linux
	rm -rf $(DIR_BUILD)/linux/$(BIN_NAME)
fclean-win64: clean-win64
	rm -rf $(DIR_BUILD)/win64/$(BIN_NAME_WIN)
fclean-win32: clean-win32
	rm -rf $(DIR_BUILD)/win32/$(BIN_NAME_WIN)

re: fclean-linux all

re-win64: fclean-win64 win64

re-win32: fclean-win32 win32
