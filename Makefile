SRC_DIR=src
BUILD_DIR=build
TESTS_DIR=tests
INCLUDE_DIR=include

TUI_LIBS=TUI_Error TUI_Symbols TUI_Render
RES_LIB=libtui.a

CC=gcc
CC_FLAGS=-Wall -Wextra -Werror -Wno-alloc-size -Wpedantic

O_FILES=$(TUI_LIBS:%=$(BUILD_DIR)/%.o)

all: $(BUILD_DIR)/$(RES_LIB)

$(BUILD_DIR):
	mkdir -p $@

define BUILD_OBJECT
$(BUILD_DIR)/$(1).o: $(SRC_DIR)/$(patsubst TUI_%,%,$(1))/$(1).c | $(BUILD_DIR)
	$(CC) -c $$< -o $$@ -I $(INCLUDE_DIR) $(CC_FLAGS) -MMD -MP
endef

$(foreach _lib,$(TUI_LIBS),$(eval $(call BUILD_OBJECT,$(_lib))))

$(BUILD_DIR)/$(RES_LIB): $(O_FILES)
	ar rcs $@ $(O_FILES)

tests: $(BUILD_DIR)/$(RES_LIB)
	mkdir -p $(BUILD_DIR)/tests
	$(CC) $(TESTS_DIR)/renderer.c -o $(BUILD_DIR)/tests/renderer -I $(INCLUDE_DIR) -L $(BUILD_DIR) -ltui -lm
	$(CC) $(TESTS_DIR)/color.c -o $(BUILD_DIR)/tests/color -I $(INCLUDE_DIR) -L $(BUILD_DIR) -ltui -lm

clean:
	rm -rf $(BUILD_DIR)

-include $(O_FILES:.o=.d)

.PHONY: all tests clean