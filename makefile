CC = gcc
CFLAGS = -fPIC -MMD -Wall -Wextra
CFLAGS_C89 = -ansi -pedantic
INTERFACE_FLAG = -DGUI
GTK_FLAG_START = `pkg-config --cflags gtk4`
GTK_FLAG_END = `pkg-config --libs gtk4`
TS_LIB = -lts

DIR_BUILD = builds
DIR_OBJ = $(DIR_BUILD)/unix/objects

EXECUTABLE = $(DIR_BUILD)/unix/treasure-venture

SOURCE_FILES = $(wildcard sources/*.c)
OBJ_FILES = $(patsubst sources/%.c, $(DIR_OBJ)/%.o, $(SOURCE_FILES))

all: $(EXECUTABLE)

# Package: libgtk-4-dev
$(EXECUTABLE): $(OBJ_FILES)
	@$(CC) $(GTK_FLAG_START) $^ -o $@ -O2 -Lplugins/twenty-squares/static $(TS_LIB) $(GTK_FLAG_END)

# File with GTK code
$(DIR_OBJ)/main.o: sources/main.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INTERFACE_FLAG) $(GTK_FLAG_START) -c $< -o $@ $(GTK_FLAG_END)
-include $(DIR_OBJ)/main.d

$(DIR_OBJ)/%.o: sources/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(CFLAGS_C89) $(INTERFACE_FLAG) -c $< -o $@
-include $(DIR_OBJ)/%.d

.PHONY: cli
cli:
	@$(MAKE) -s all INTERFACE_FLAG=-DCLI GTK_FLAG_START="" GTK_FLAG_END=""

# Package: gcc-mingw-w64
.PHONY: win64
.PHONY: win32
win64:
	@$(MAKE) -s cli \
	CC=x86_64-w64-mingw32-gcc \
	TS_LIB=-lts64 \
	DIR_OBJ=$(DIR_BUILD)/win64/objects \
	EXECUTABLE=$(DIR_BUILD)/win64/TreasureVenture-64bit.exe
win32:
	@$(MAKE) -s cli \
	CC=i686-w64-mingw32-gcc \
	TS_LIB=-lts32 \
	DIR_OBJ=$(DIR_BUILD)/win32/objects \
	EXECUTABLE=$(DIR_BUILD)/win32/TreasureVenture-32bit.exe

.PHONY: clean
.PHONY: clean-unix
.PHONY: clean-win64
.PHONY: clean-win32
clean:
	@make -s clean-unix
	@make -s clean-win64
	@make -s clean-win32
clean-unix:
	@rm -rf builds/unix/
clean-win64:
	@rm -rf builds/win64/
clean-win32:
	@rm -rf builds/win32/

