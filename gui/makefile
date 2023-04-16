CC = gcc
CFLAGS = -fPIC -MMD -ansi -pedantic -Wall -Wextra 
TS_LIB = -lts

DIR_BUILD = builds
DIR_OBJ = $(DIR_BUILD)/unix/objects

EXECUTABLE = $(DIR_BUILD)/unix/treasure-venture

SOURCE_FILES = $(wildcard sources/*.c)
OBJ_FILES = $(patsubst sources/%.c, $(DIR_OBJ)/%.o, $(SOURCE_FILES))
-include $(OBJ_FILES:.o=.d)

all: $(EXECUTABLE)

# Package: libgtk-4-dev
$(EXECUTABLE): $(OBJ_FILES)
	@$(CC) `pkg-config --cflags gtk4` $^ -o $@ -O2 -Lplugins/twenty-squares/static $(TS_LIB) `pkg-config --libs gtk4`

$(DIR_OBJ)/%.o: sources/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $^ -o $@

# Package: gcc-mingw-w64
.PHONY: win64
.PHONY: win32
win64:
	@$(MAKE) -s all \
	CC=x86_64-w64-mingw32-gcc \
	TS_LIB=-lts64 \
	DIR_OBJ=$(DIR_BUILD)/win64/objects \
	EXECUTABLE=$(DIR_BUILD)/win64/TreasureVenture-64bit.exe
win32:
	@$(MAKE) -s all \
	CC=i686-w64-mingw32-gcc \
	TS_LIB=-lts32 \
	DIR_OBJ=$(DIR_BUILD)/win32/objects \
	EXECUTABLE=$(DIR_BUILD)/win32/TreasureVenture-32bit.exe

.PHONY: clean
.PHONY: clean-unix
.PHONY: clean-win64
.PHONY: clean-win32
.PHONY: clean-obj
.PHONY: clean-obj-unix
.PHONY: clean-obj-win64
.PHONY: clean-obj-win32
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
clean-obj:
	@make -s clean-obj-unix
	@make -s clean-obj-win64
	@make -s clean-obj-win32
clean-obj-unix:
	@rm -rf builds/unix/objects/
clean-obj-win64:
	@rm -rf builds/win64/objects/
clean-obj-win32:
	@rm -rf builds/win32/objects/

