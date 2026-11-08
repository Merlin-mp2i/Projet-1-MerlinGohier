#!/usr/bin/env sh
set -eu

gcc -Wall -Wextra -Werror -std=c11 \
  tests/test_filesystem.c src/dossier.c src/fichier.c src/filesysteme.c \
  -o tests/test_filesystem

./tests/test_filesystem
