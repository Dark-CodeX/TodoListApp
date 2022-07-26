CC=g++

CFLAGS_CLI=-O3 -DNDEBUG -Os -Ofast -Og -s -march=native -masm=intel -flto=auto -funroll-all-loops -std=c++23
TARGET_CLI=./src/ui/cli/cli.cc
OUT_CLI=./todo

CFLAGS_GUI=-O3 -Os -Ofast -Og -s -march=native -masm=intel -flto=auto -funroll-all-loops -std=c++23 `pkgconf --cflags --libs gtkmm-3.0` -mwindows
TARGET_GUI=./src/ui/gui/gui.cc
OUT_GUI=./todo-gui

all:install

cli:
	$(CC) $(CFLAGS_CLI) ${TARGET_CLI} -o ${OUT_CLI}

gui:
	$(CC) ${TARGET_GUI} $(CFLAGS_GUI) -o ${OUT_GUI}

install:
	$(CC) $(CFLAGS_CLI) ${TARGET_CLI} -o ${OUT_CLI}
	$(CC) ${TARGET_GUI} $(CFLAGS_GUI) -o ${OUT_GUI}
	sudo mv ./todo ./todo-gui /usr/bin/
	sudo cp ./todo_gui.desktop /usr/share/applications/
