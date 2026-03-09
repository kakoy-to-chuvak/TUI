SRC_DIR=src
BUILD_DIR=build
TESTS_DIR=tests
INCLUDE_DIR=include

TUI_LIBS=TUI_Error TUI_Symbols TUI_Render
RES_LIB=liblogs.a

CC_FLAGS=-Wall -Wextra -Werror -Wno-alloc-size -Wpedantic





O_FILES=$(TUI_LIBS:%=%.o)
SRC_FILES=$(TUI_LIBS:TUI_%=$(SRC_DIR)/%/*.c)
SRCS=$(foreach _src,$(SRC_FILES),$(wildcard $(_src)))


all: $(BUILD_DIR)/$(RES_LIB)



$(BUILD_DIR)/$(RES_LIB): $(O_FILES)
	ar rcs $(BUILD_DIR)/$(RES_LIB) TUI_Error.o TUI_Symbols.o TUI_Render.o
	@echo Cleaning garbage...
	del $(O_FILES)


$(O_FILES): $(SRCS)
	@echo Compiling .o files...
	gcc -c $(SRCS) -I $(INCLUDE_DIR) $(CC_FLAGS)


tests: 
	gcc $(TESTS_DIR)/renderer.c -o $(BUILD_DIR)/tests/renderer -I $(INCLUDE_DIR) -L $(BUILD_DIR) -llogs
	gcc $(TESTS_DIR)/color.c -o $(BUILD_DIR)/tests/color -I $(INCLUDE_DIR) -L $(BUILD_DIR) -llogs


.PHONY: tests