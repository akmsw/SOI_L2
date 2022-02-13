# author: Bonino, Francisco Ignacio.
# version: 1.0
# since: 2021-08-20

CC = gcc
CFLAGS = -Wall -Werror -pedantic

all: build_folders
	$(CC) $(GCC) linked_list.c -o bin/linked_list

build_folders:
	mkdir -p ./bin

clean:
	rm -r ./bin