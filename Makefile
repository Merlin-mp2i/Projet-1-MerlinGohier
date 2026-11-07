# Compilation du systeme de fichiers simplifie
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
SOURCES = src/dossier.c src/fichier.c src/filesysteme.c

ifeq ($(OS),Windows_NT)
EXE = .exe
RUN = .\\
else
EXE =
RUN = ./
endif

.PHONY: all test clean

all: filesystem$(EXE)

filesystem$(EXE): main.c $(SOURCES) include/filesytem.h
	$(CC) $(CFLAGS) main.c $(SOURCES) -o $@

tests/test_unitaire$(EXE): tests/test_unitaire.c $(SOURCES) include/filesytem.h
	$(CC) $(CFLAGS) tests/test_unitaire.c $(SOURCES) -o $@

test: tests/test_unitaire$(EXE)
	$(RUN)tests/test_unitaire$(EXE)

clean:
	$(RM) filesystem filesystem.exe tests/test_unitaire tests/test_unitaire.exe
