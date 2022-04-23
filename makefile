CC=g++
CFLAGS_CLI=-O3 -Os -Ofast -Og -s -march=native -flto
TARGET_CLI=./src/ui/cli/cli.cc
OUT_CLI=./todo

all:cli

cli:
	$(CC) $(CFLAGS_CLI) ${TARGET_CLI} -o ${OUT_CLI}

exp:
	sudo mv ./todo /usr/bin