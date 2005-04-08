CC = gcc
LD = g++
OBJ_DIR = build
OUTPUT_DIR = lib
TARGET = libcpaf_gui_gtk2d.so
INCLUDE_DIRS = -I include -I .
CXXFLAGS = -pipe `pkg-config --cflags gtk+-2.0` -ggdb -Wall -fvisibility-inlines-hidden
LD_FLAGS = -shared -fpic `pkg-config --libs gtk+-2.0`

SRC_OBJS = \
	$(OBJ_DIR)/gui/sizeable.o \
	$(OBJ_DIR)/gui/widget.o \
	$(OBJ_DIR)/gui/toplevel.o \
	$(OBJ_DIR)/gui/factory.o \
	$(OBJ_DIR)/gui/window.o \
	$(OBJ_DIR)/gtk2/factory.o \
	$(OBJ_DIR)/gtk2/window.o \
	$(OBJ_DIR)/gtk2/utils.o \
	$(OBJ_DIR)/api_factory_keys.o

define build_target
	@echo Creating library...
	$(LD) $(LD_FLAGS) -o "$(OUTPUT_DIR)/$(TARGET)" $(SRC_OBJS)
endef

define compile_source
	$(CC) $(CXXFLAGS) $(INCLUDE_DIRS) -c "$<" -o "$@"
endef

.PHONY: directories

$(TARGET): directories $(SRC_OBJS)
	$(build_target)

.PHONY: clean cleanall

install:
	@echo Installing not yet supported.

cleanall:
	@echo Deleting intermediate files.
	-@rm -rf "$(OBJ_DIR)"/*
	-@rm -rf "$(OUTPUT_DIR)/$(TARGET)"
	-@rmdir "$(OUTPUT_DIR)"

clean: cleanall

directories:
	-@if [ ! -d "$(OUTPUT_DIR)" ]; then mkdir "$(OUTPUT_DIR)"; fi
	-@if [ ! -d "$(OBJ_DIR)" ]; then mkdir "$(OBJ_DIR)"; fi
	-@if [ ! -d "$(OBJ_DIR)/gui" ]; then mkdir "$(OBJ_DIR)/gui"; fi
	-@if [ ! -d "$(OBJ_DIR)/gtk2" ]; then mkdir "$(OBJ_DIR)/gtk2"; fi

$(OBJ_DIR)/gui/sizeable.o: src/cpaf/gui/sizeable.cpp
	$(compile_source)

$(OBJ_DIR)/gui/widget.o: src/cpaf/gui/widget.cpp
	$(compile_source)

$(OBJ_DIR)/gui/toplevel.o: src/cpaf/gui/toplevel.cpp
	$(compile_source)

$(OBJ_DIR)/gui/factory.o: src/cpaf/gui/factory.cpp
	$(compile_source)

$(OBJ_DIR)/gui/window.o: src/cpaf/gui/window.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/factory.o: src/cpaf/gtk2/factory.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/window.o: src/cpaf/gtk2/window.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/utils.o: src/cpaf/gtk2/utils.cpp
	$(compile_source)

$(OBJ_DIR)/api_factory_keys.o: src/cpaf/api_factory_keys.cpp
	$(compile_source)
