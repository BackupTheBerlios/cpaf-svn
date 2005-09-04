CC = gcc
LD = g++
OBJ_DIR = build
OUTPUT_DIR = lib
TARGET = libcpaf_gui_gtk2d.so
INCLUDE_DIRS = -I include -I .
CXXFLAGS = -pipe -D_DEBUG -DCPAF_GTK2 -DCPAF_BUILDING -DCPAF_DLL `pkg-config --cflags gtk+-2.0` -ggdb -Wall #-fvisibility-inlines-hidden -fvisibility=hidden
LD_FLAGS = -shared -fpic -Wl,-O1 `pkg-config --libs gtk+-2.0`

SRC_OBJS =                      \
	$(OBJ_DIR)/gui/app.o        \
	$(OBJ_DIR)/gui/object.o     \
	$(OBJ_DIR)/gui/widget.o     \
	$(OBJ_DIR)/gui/toplevel.o   \
	$(OBJ_DIR)/gui/factory.o    \
	$(OBJ_DIR)/gui/gridbaglayout.o    \
	$(OBJ_DIR)/gui/layoutmanager.o    \
	$(OBJ_DIR)/gui/window.o     \
	$(OBJ_DIR)/gui/panel.o      \
	$(OBJ_DIR)/gui/button.o     \
	$(OBJ_DIR)/gui/textwidget.o \
	$(OBJ_DIR)/gui/entrybox.o   \
	$(OBJ_DIR)/gui/textbox.o    \
	$(OBJ_DIR)/gui/initializer/object.o     \
	$(OBJ_DIR)/gui/initializer/widget.o     \
	$(OBJ_DIR)/gui/initializer/window.o     \
	$(OBJ_DIR)/gui/initializer/panel.o      \
	$(OBJ_DIR)/gui/initializer/button.o     \
	$(OBJ_DIR)/gui/initializer/textwidget.o \
	$(OBJ_DIR)/gui/initializer/entrybox.o   \
	$(OBJ_DIR)/gui/initializer/textbox.o    \
	$(OBJ_DIR)/event/event.o    \
	$(OBJ_DIR)/event/id.o       \
	$(OBJ_DIR)/gtk2/app.o       \
	$(OBJ_DIR)/gtk2/factory.o   \
	$(OBJ_DIR)/gtk2/widget.o    \
	$(OBJ_DIR)/gtk2/window.o    \
	$(OBJ_DIR)/gtk2/panel.o     \
	$(OBJ_DIR)/gtk2/button.o    \
	$(OBJ_DIR)/gtk2/entrybox.o  \
	$(OBJ_DIR)/gtk2/textbox.o   \
	$(OBJ_DIR)/gtk2/utils.o     \
	$(OBJ_DIR)/types.o          \
	$(OBJ_DIR)/main.o           \
	$(OBJ_DIR)/exception.o      \
	$(OBJ_DIR)/app.o            \
	$(OBJ_DIR)/api.o

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
	-@if [ -d "$OUTPUT_DIR" ]; then rmdir "$(OUTPUT_DIR)"; fi

clean: cleanall

directories:
	-@if [ ! -d "$(OUTPUT_DIR)" ]; then mkdir "$(OUTPUT_DIR)"; fi
	-@if [ ! -d "$(OBJ_DIR)" ]; then mkdir "$(OBJ_DIR)"; fi
	-@if [ ! -d "$(OBJ_DIR)/gui" ]; then mkdir "$(OBJ_DIR)/gui"; fi
	-@if [ ! -d "$(OBJ_DIR)/gui/initializer" ]; then mkdir "$(OBJ_DIR)/gui/initializer"; fi
	-@if [ ! -d "$(OBJ_DIR)/event" ]; then mkdir "$(OBJ_DIR)/event"; fi
	-@if [ ! -d "$(OBJ_DIR)/gtk2" ]; then mkdir "$(OBJ_DIR)/gtk2"; fi

$(OBJ_DIR)/gui/app.o: src/cpaf/gui/app.cpp
	$(compile_source)

$(OBJ_DIR)/gui/object.o: src/cpaf/gui/object.cpp
	$(compile_source)

$(OBJ_DIR)/gui/widget.o: src/cpaf/gui/widget.cpp
	$(compile_source)

$(OBJ_DIR)/gui/toplevel.o: src/cpaf/gui/toplevel.cpp
	$(compile_source)

$(OBJ_DIR)/gui/factory.o: src/cpaf/gui/factory.cpp
	$(compile_source)

$(OBJ_DIR)/gui/gridbaglayout.o: src/cpaf/gui/gridbaglayout.cpp
	$(compile_source)

$(OBJ_DIR)/gui/layoutmanager.o: src/cpaf/gui/layoutmanager.cpp
	$(compile_source)

$(OBJ_DIR)/gui/window.o: src/cpaf/gui/window.cpp
	$(compile_source)

$(OBJ_DIR)/gui/panel.o: src/cpaf/gui/panel.cpp
	$(compile_source)

$(OBJ_DIR)/gui/button.o: src/cpaf/gui/button.cpp
	$(compile_source)

$(OBJ_DIR)/gui/textwidget.o: src/cpaf/gui/textwidget.cpp
	$(compile_source)

$(OBJ_DIR)/gui/entrybox.o: src/cpaf/gui/entrybox.cpp
	$(compile_source)

$(OBJ_DIR)/gui/textbox.o: src/cpaf/gui/textbox.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/object.o: src/cpaf/gui/initializer/object.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/widget.o: src/cpaf/gui/initializer/widget.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/toplevel.o: src/cpaf/gui/initializer/toplevel.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/factory.o: src/cpaf/gui/initializer/factory.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/window.o: src/cpaf/gui/initializer/window.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/panel.o: src/cpaf/gui/initializer/panel.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/button.o: src/cpaf/gui/initializer/button.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/textwidget.o: src/cpaf/gui/initializer/textwidget.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/entrybox.o: src/cpaf/gui/initializer/entrybox.cpp
	$(compile_source)

$(OBJ_DIR)/gui/initializer/textbox.o: src/cpaf/gui/initializer/textbox.cpp
	$(compile_source)

$(OBJ_DIR)/event/event.o: src/cpaf/event/event.cpp
	$(compile_source)

$(OBJ_DIR)/event/id.o: src/cpaf/event/id.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/app.o: src/cpaf/gtk2/app.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/factory.o: src/cpaf/gtk2/factory.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/widget.o: src/cpaf/gtk2/widget.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/window.o: src/cpaf/gtk2/window.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/panel.o: src/cpaf/gtk2/panel.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/button.o: src/cpaf/gtk2/button.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/entrybox.o: src/cpaf/gtk2/entrybox.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/textbox.o: src/cpaf/gtk2/textbox.cpp
	$(compile_source)

$(OBJ_DIR)/gtk2/utils.o: src/cpaf/gtk2/utils.cpp
	$(compile_source)

$(OBJ_DIR)/types.o: src/cpaf/types.cpp
	$(compile_source)

$(OBJ_DIR)/main.o: src/cpaf/main.cpp
	$(compile_source)

$(OBJ_DIR)/exception.o: src/cpaf/exception.cpp
	$(compile_source)

$(OBJ_DIR)/app.o: src/cpaf/app.cpp
	$(compile_source)

$(OBJ_DIR)/api.o: src/cpaf/api.cpp
	$(compile_source)
