CC=g++

CFLAGS_CLI=-O3 -DNDEBUG -Os -Ofast -Og -s -march=native -masm=att -mtune=native -fipa-pta -ftree-vectorize -flto=auto -funroll-all-loops -std=c++23
TARGET_CLI=./src/ui/cli/cli.cc
OUT_CLI=./bin/todo

OS := $(shell uname)
ifeq ($(OS), Windows_NT)
CFLAGS_GUI=-O3 -Os -Ofast -Og -s -march=native -masm=att -mtune=native -fipa-pta -ftree-vectorize -flto=auto -funroll-all-loops -std=c++23 `pkgconf --cflags --libs gtkmm-3.0` -mwindows
else
CFLAGS_GUI=-O3 -Os -Ofast -Og -s -march=native -masm=att -mtune=native -fipa-pta -ftree-vectorize -flto=auto -funroll-all-loops -std=c++23 `pkgconf --cflags --libs gtkmm-3.0`
endif

TARGET_GUI=./src/ui/gui/gui.cc
OUT_GUI=./bin/todo-gui

all:compile_all

cli:
	$(CC) $(CFLAGS_CLI) ${TARGET_CLI} -o ${OUT_CLI}

gui:
	$(CC) ${TARGET_GUI} $(CFLAGS_GUI) -o ${OUT_GUI}

compile_all:
	$(CC) $(CFLAGS_CLI) ${TARGET_CLI} -o ${OUT_CLI}
	$(CC) ${TARGET_GUI} $(CFLAGS_GUI) -o ${OUT_GUI}

install:
	$(CC) $(CFLAGS_CLI) ${TARGET_CLI} -o ${OUT_CLI}
	$(CC) ${TARGET_GUI} $(CFLAGS_GUI) -o ${OUT_GUI}
	sudo mv ./bin/todo ./bin/todo-gui /usr/bin/
	sudo cp ./todo_gui.desktop /usr/share/applications/