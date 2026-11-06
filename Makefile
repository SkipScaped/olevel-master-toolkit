CC = nspire-gcc
LD = nspire-ld
GENZEHN = genzehn
MAKE_PRG = make-prg

APP = O-Level-Master-Toolkit
BUILD_DIR = .build
DIST_DIR = dist
SOURCES = src/main.c src/ui.c src/math_tools.c src/cs_tools.c
OBJECTS = $(patsubst src/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
ELF = $(BUILD_DIR)/$(APP).elf
ZEHN = $(BUILD_DIR)/$(APP).zehn
TNS = $(DIST_DIR)/$(APP).tns

CFLAGS = -Wall -Wextra -marm -Os
LDFLAGS = -Wl,--gc-sections
ZEHNFLAGS = --name "O-Level Master Toolkit" --author "O-Level Master Toolkit" --color-support 1 --clickpad-support 0 --touchpad-support 1

.PHONY: all build test clean

all: build

build: $(TNS)

$(BUILD_DIR):
	mkdir -p $@

$(DIST_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: src/%.c src/toolkit.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) -Isrc -c $< -o $@

$(ELF): $(OBJECTS)
	$(LD) $(OBJECTS) -o $@ $(LDFLAGS) -lm

$(ZEHN): $(ELF)
	$(GENZEHN) --input $< --output $@ $(ZEHNFLAGS)

$(TNS): $(ZEHN) | $(DIST_DIR)
	$(MAKE_PRG) $< $@

test: $(ZEHN) $(TNS)
	$(GENZEHN) --info --input $(ZEHN)
	test -s $(TNS)
	loader="$$(nspire-tools _zehn_loader_path)"; cmp -n "$$(wc -c < "$$loader")" "$$loader" "$(TNS)"

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)